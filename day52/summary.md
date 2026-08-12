**Day 52 – Understanding LoRA and QLoRA**

Today was a fairly theory-heavy day focused on getting a high-level understanding of QLoRA, one of the most useful techniques for fine-tuning large language models when GPU memory is limited.

Rather than jumping directly into implementation, I first tried to understand why QLoRA exists and what problem it solves.

The easiest way to understand QLoRA is to separate it into two ideas:

QLoRA = Quantization + LoRA

Why do we even need LoRA?

Even models that are considered relatively small by modern LLM standards are enormous compared with traditional neural networks.

For example, Llama 3.2 3B actually contains about 3.21 billion parameters. Meta specifically designed the 1B and 3B Llama 3.2 models for relatively resource-constrained and on-device applications, but training billions of parameters is still a completely different problem from merely running inference with them.

If those 3.21 billion parameters were stored as ordinary FP32 values, the weights alone would require roughly 13 GB of memory.

And full fine-tuning needs much more memory than simply storing the weights.

During training, we also have to deal with things such as:

Activations from the forward pass
Gradients from backpropagation
Optimizer states
Other temporary training tensors

So even though a small quantized LLM may run on relatively modest hardware, full fine-tuning all of its parameters can still require far more GPU memory.

This is where LoRA — Low-Rank Adaptation — comes in. The original LoRA method freezes the pretrained model weights and introduces much smaller trainable matrices instead.

Looking inside Llama

Llama is built from a stack of Transformer decoder blocks.

At a high level, these blocks contain components such as:

Self-attention, which helps the model determine which previous tokens are important when building the representation used to predict the next token.

MLP/feed-forward layers, which transform the hidden representations after attention.

SiLU-based gated activations, which introduce the nonlinear behavior necessary for the network to model complex relationships.

And RMSNorm, which Llama uses for normalization rather than the standard LayerNorm formulation.

These blocks contain many large linear projection matrices, and across the whole model they account for billions of learned parameters.

Normally, during full fine-tuning, gradients are calculated so that these pretrained weights themselves can be updated.

LoRA takes a different approach.

Freeze the original model

With LoRA, the huge pretrained weight matrices remain frozen.

Suppose one of the model's linear layers contains a weight matrix:

W

Instead of directly modifying W during training, LoRA learns a separate update:

ΔW

So conceptually the adapted model behaves like:

W' = W + ΔW

The clever part is how ΔW is represented.

Rather than learning another giant matrix with exactly the same number of parameters as W, LoRA represents the update using two much smaller low-rank matrices, usually called A and B.

The two smaller matrices are multiplied together:

ΔW = BA

Their dimensions are chosen so that multiplying them produces a matrix with the same dimensions as the original W.

That means:

large update matrix → represented by two small matrices

Instead of training millions of parameters for that particular weight matrix, we may only need to train a tiny fraction of them.

The pretrained W stays frozen while A and B are optimized through gradient descent. This dramatically reduces the number of trainable parameters.

Why is it called “low rank”?

The important hyperparameter here is r, or the rank.

Imagine the original weight matrix has dimensions something like:

4096 × 4096

LoRA could instead introduce matrices roughly shaped like:

4096 × 8

and

8 × 4096

Multiplying them produces a:

4096 × 4096

update matrix.

But instead of directly learning all ~16 million values of that update, we only train the parameters inside those two much smaller matrices.

That small intermediate dimension — in this example 8 — is the rank r.

This is the core reason LoRA is so parameter-efficient.

LoRA scaling with alpha

There is also another important hyperparameter:

alpha (α)

The LoRA update is normally scaled before being applied to the original weight matrix.

In the original/common LoRA formulation, this is approximately:

W' = W + (α / r)BA

So one correction to my initial understanding is that alpha does not usually multiply the LoRA matrices directly by itself — the traditional scaling factor is α/r. PEFT also supports newer scaling variants, but α/r is the basic version worth remembering first.

Alpha controls how strongly the learned LoRA update affects the frozen base model.

The three important LoRA settings

I focused on three major hyperparameters today.

1. r — Rank

This determines the size or capacity of the low-rank update.

Smaller ranks mean:

fewer parameters → less memory → faster training

Larger ranks give the adapter more capacity to learn changes in the model's behavior.

Values such as:

8 → 16 → 32

are sensible values to experiment with, increasing the rank if performance continues improving.

However, there is no universal best rank.

2. lora_alpha — Scaling

Alpha controls the scale of the LoRA update.

A commonly seen heuristic is to choose alpha relative to the rank—for example alpha = 2 × r—but this is not a fixed rule.

In fact, Hugging Face's own PEFT examples use different relationships between r and lora_alpha, so these values should ultimately be treated as hyperparameters to experiment with.

3. target_modules

LoRA does not necessarily need to modify every possible module.

Instead, we specify which linear projection modules should receive LoRA adapters.

For Llama-like models, common examples include:

q_proj
k_proj
v_proj
o_proj

These belong to the attention mechanism.

One correction here is that we are targeting projection modules/matrices, rather than literally targeting individual “attention heads.”

A lightweight LoRA configuration may target only some attention projections, while QLoRA-style training often places adapters on all linear layers. Hugging Face's current PEFT documentation specifically recommends target_modules="all-linear" for QLoRA-style training.

Then comes the Q in QLoRA

Once LoRA made sense, the Q became much easier to understand.

It stands for:

Quantization

Instead of keeping the billions of frozen parameters of the base model at FP32 or BF16 precision, QLoRA stores the base model using much lower precision—most famously 4-bit quantization.

The original QLoRA paper introduced a special 4-bit format called:

NF4 — 4-bit NormalFloat

NF4 is specifically designed for neural-network weights whose values tend to follow approximately zero-centered normal distributions. It performed better than ordinary 4-bit integer or FP4 representations in the QLoRA experiments.

So my earlier mental model of “the 4-bit number is basically a float following a normal distribution” was close but not quite precise.

A better description is:

NF4 defines 16 quantization values chosen to efficiently represent normally distributed neural-network weights.

The actual stored base-model weights are 4-bit, but calculations don't simply happen as ordinary 4-bit arithmetic.

When QLoRA needs those weights during computation, they are dequantized into a higher computation datatype, typically BF16, and matrix multiplication happens at that higher precision.

What gets quantized?

This distinction was especially important:

The frozen base model is quantized.

The trainable LoRA adapters are not reduced to 4-bit.

In the original QLoRA setup, the LoRA parameters use 16-bit BF16 computation, while the frozen pretrained weights are stored using 4-bit NF4.

So conceptually:

Huge base model → frozen + 4-bit

Tiny LoRA adapters → trainable + higher precision

That's what makes QLoRA so useful.

We get the memory savings of quantization while still training higher-precision adapter parameters.

QLoRA has a few more tricks

I mainly focused on the high-level idea today, but I also learned that QLoRA is technically more than simply:

4-bit model + LoRA

The original QLoRA method introduced three major memory-saving ideas:

NF4 quantization — efficient 4-bit representation for normally distributed model weights.

Double Quantization — even the constants used during quantization are themselves quantized to save additional memory.

Paged Optimizers — help handle temporary GPU-memory spikes during training.

I haven't gone deeply into these yet, but they're useful concepts to remember when I eventually implement QLoRA.

The mental model I want to remember

The easiest way for me to remember today's lesson is:

Full fine-tuning

Change billions of original model parameters.

LoRA

Freeze those billions of parameters and learn tiny low-rank updates instead.

QLoRA

Quantize those frozen billions of parameters to 4-bit and train the small LoRA adapters at higher precision.

Or even shorter:

QLoRA = frozen quantized base model + trainable low-rank adapters

That one sentence basically captures the entire idea.

Today's biggest takeaway

The cleverness of QLoRA isn't that it somehow makes a 3-billion-parameter model small.

It recognizes that we don't actually need to update all 3 billion parameters to adapt the model to a new task.

Instead, LoRA learns a much smaller set of low-rank changes, while quantization dramatically reduces the memory occupied by the frozen base model.

Together, they make fine-tuning LLMs possible on hardware that would be completely incapable of full-parameter training.

Quite a hefty theory day 😭, but this finally gave me the conceptual foundation for understanding what will actually happen when I start fine-tuning my price-prediction model.
