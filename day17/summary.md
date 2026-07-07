## Day 17 – Quantization, Transformer Internals & Running Open-Source LLMs

Today was one of the grittier AI days, and honestly, a lot of it felt heavier than usual.

The main topic was quantization in transformer models. I learned that models usually store their weights in higher precision formats like 32-bit floating point, but with quantization, those weights can be stored in much lower precision, like 8-bit or even 4-bit.

At first, this sounded similar to reducing the number of parameters in a model, but it is actually different.

Reducing parameters means making the model smaller by changing the architecture or removing parts of it.
Quantization keeps the model structure mostly the same, but stores each weight using fewer bits. This makes the model much lighter in memory while still trying to preserve as much performance as possible.

So instead of the model becoming “less intelligent” by simply removing neurons or layers, quantization compresses the way the model’s existing weights are represented. This helps larger models fit into limited GPU memory and makes it possible to run open-source LLMs on smaller hardware.

I also went deeper into the transformer architecture, including parts like:

Token embeddings, where input text is converted into numerical representations
Decoder layers, which process tokens step by step in decoder-only LLMs
Attention layers, which help the model figure out which tokens are important in relation to each other
MLP layers, which further transform the hidden representations
Non-linearity, which is important because without it, neural networks would mostly behave like simple linear functions and would not be able to learn complex patterns properly

This part went a little above my head for the first time, so I definitely need to revisit the videos and revise it again.

On the practical side, I worked with the low-level Hugging Face Transformers API instead of only using high-level pipelines. I got a better idea that the “model” part of a transformer is where the actual neural network architecture and weights live, and quantization is applied while loading or configuring that model.

I also looked at PyTorch model architecture outputs and saw how transformer models are structured internally, including embeddings, decoder layers, attention blocks, and MLP components.

Finally, I experimented with running open-source LLMs from Hugging Face using quantization. I tried models from families like:

Phi
Gemma
Qwen
DeepSeek

One interesting thing I noticed was that not every model supports quantization smoothly. Some smaller models or certain architectures may not support the same quantized loading options.

### Main takeaway

Today made me realize that using LLMs is one thing, but understanding how they are actually built and optimized is a completely different level.

Quantization is not just a random compression trick. It is one of the reasons why large language models can be run more efficiently on limited hardware.

The theory was heavy, the transformer internals were confusing, and I probably need a second round with the videos, but this felt like an important step toward understanding what is really happening under the hood of modern LLMs.

Basically, today was less “I mastered transformers” and more “I saw the transformer architecture and survived.”
