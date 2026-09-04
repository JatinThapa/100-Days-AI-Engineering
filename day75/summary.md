# Day 75 — Revisiting QLoRA & Parameter-Efficient Fine-Tuning 🧠⚙️

Today was another **revision-focused day** in my #100DaysOfAI journey. Rather than learning a completely new concept, I went back to **Day 52 and 53** to revisit one of the most important topics from my LLM fine-tuning work: **LoRA and QLoRA**.

After working with fine-tuned models for my price prediction project, I wanted to refresh the concepts behind *why* QLoRA was necessary in the first place and how it allows large language models to be fine-tuned with much more manageable resource requirements.

### 🔄 Revisiting LoRA

The core idea behind **LoRA (Low-Rank Adaptation)** is surprisingly simple.

Instead of modifying billions of parameters in a pretrained model during fine-tuning, we:

🔹 Freeze the original model weights
🔹 Add small trainable adapter matrices
🔹 Train only those adapters
🔹 Keep the original model unchanged

The important part is that the weight update is represented using two much smaller matrices, dramatically reducing the number of parameters that actually need to be trained.

I also revisited the main LoRA hyperparameters:

**`r`** → controls the rank and therefore the capacity of the adapter
**`alpha`** → controls the scaling of the LoRA update
**`target_modules`** → determines which parts of the model receive the adapters

### 🧩 And Then Comes the “Q” in QLoRA

QLoRA takes this a step further by combining **Quantization + LoRA**.

The base model is kept **frozen and quantized**, typically to **4-bit precision**, which significantly reduces its memory footprint.

The LoRA adapters, meanwhile, remain trainable at higher precision.

So my mental model after revisiting it is:

**Full Fine-Tuning → Update the entire model**
**LoRA → Freeze the model + train small adapters**
**QLoRA → Quantize the frozen model + train small adapters**

I also revisited why this matters so much when working with models like **Qwen3 8B**. During my earlier experiment, loading the full model already required around **16.4 GB of memory** before even getting into the actual fine-tuning process. That number alone made the motivation behind QLoRA pretty obvious. 😂

### 💡 Today's Takeaway

Revisiting QLoRA reminded me that **fine-tuning an LLM doesn't necessarily mean retraining the entire model**.

Parameter-efficient fine-tuning is really about finding a smarter way to specialize a huge pretrained model without requiring the memory and compute needed to update every single parameter.

And honestly, after actually using QLoRA in my earlier price-prediction experiment, going back to the theory made much more sense this time. The concepts that initially looked like a collection of complicated terms now feel much more intuitive because I've seen them work in practice. 🧠🔗

🎯 **Day 75 complete.**
