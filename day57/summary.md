# Day 57 – Understanding the Fine-Tuning Configuration 🧠⚙️

Today was supposed to be another **fine-tuning day**...

But apparently, I’m getting really good at preparing to fine-tune without actually fine-tuning 😂

Instead of jumping straight into training **Llama 3.2 3B**, I spent the day understanding the different **hyperparameters, constraints and training mechanics** that I’ll have to deal with when I finally start QLoRA training.

## 1. Revising the QLoRA Hyperparameters

I started by revisiting the five important parameters that control the LoRA/QLoRA setup.

### 🎯 Target Modules

These determine **which layers receive the LoRA adapters**.

For my current experiment, I’m focusing on the attention projections:

* `q_proj`
* `k_proj`
* `v_proj`
* `o_proj`

If I eventually have access to a much more powerful GPU, I could experiment with including the **MLP layers** as well, especially when working with the full 800,000-item dataset.

### 📐 Rank (`r`)

`r` stands for **rank** and determines the dimensions of the low-rank LoRA matrices.

A larger `r` means:

> More trainable parameters → more capacity → potentially more expressive adapters → more memory.

### ⚖️ Alpha

`alpha` controls the **scaling of the LoRA update** before it is added to the original weights.

A common starting point is:

> **alpha ≈ 2 × r**

So it acts as another knob controlling how strongly the LoRA adapters influence the original model.

### 📉 Quantization

Quantization reduces the precision used to represent the frozen base-model weights.

The basic tradeoff is:

> **Slightly less numerical precision → significantly less memory usage**

This gives us more room to actually train the model and its adapters on limited GPU hardware.

### 🧹 Dropout

This was a new one for me today.

LoRA dropout randomly drops parts of the **LoRA branch during training**, helping prevent the adapters from overfitting to a relatively small fine-tuning dataset.

For my experiment, I’m planning to use the common:

> **Dropout = 0.1**

So roughly 10% of the LoRA activations are randomly dropped during training.

---

# 2. Understanding the Main Training Hyperparameters

I then moved beyond LoRA itself and revised the parameters controlling the overall training process.

### 🔄 Epochs

An epoch represents one complete pass through the training dataset.

During each pass, the model repeatedly goes through:

**Forward pass → Loss → Backward pass → Optimization**

More epochs give the model more opportunities to learn, but too many can also increase the risk of overfitting.

### 📦 Batch Size

Batch size determines how many training examples are processed together before calculating the update.

Ideally, we want the largest batch that our GPU can comfortably handle.

And when working with GPU memory, powers of two such as **2, 4, 8, 16...** are commonly convenient choices.

### 📈 Learning Rate

The learning rate controls **how large each parameter update should be**.

If it's too large, we can overshoot the minimum of the loss landscape:

> 🚀 Big steps → potentially jump right over the minimum.

If it's too small:

> 🐢 Tiny steps → training can become extremely slow and may get stuck around a local minimum.

For this experiment, I’m planning to use a **cosine learning-rate scheduler**.

The idea is to start with a relatively larger learning rate and gradually reduce it during training, allowing the model to make larger adjustments early on and finer adjustments later.

### ➕ Gradient Accumulation

Gradient accumulation is basically a way of simulating a larger batch size when GPU memory is limited.

Instead of immediately updating the model after every batch:

**Forward → Loss → Backward → Update**

we can do:

**Forward → Loss → Backward**
**Forward → Loss → Backward**
**Forward → Loss → Backward**
⬇️
**Accumulate gradients → Update**

This lets us effectively use a larger batch without having to fit the entire batch into GPU memory at once.

### ⚙️ Optimizer

The optimizer determines **how the model parameters should actually be updated** using the calculated gradients.

I revised the basic idea behind **SGD** and then looked at **Adam**, which I’m planning to use for this experiment.

Adam maintains running estimates related to the gradients and their magnitude, helping make parameter updates more adaptive and stable than simply taking a basic fixed-size step in the gradient direction.

---

# 3. Revisiting the Four-Step Training Loop 🔁

Finally, I went back to the fundamental training loop that all these hyperparameters are ultimately controlling:

### 1️⃣ Forward Pass

The model receives the input and generates a prediction.

### 2️⃣ Loss Calculation

The prediction is compared against the ground truth to determine **how wrong the model was**.

### 3️⃣ Backward Pass

The loss is propagated backwards to calculate **gradients** — essentially indicating how the trainable parameters should change to reduce the loss.

In my QLoRA setup, these updates are focused on the **LoRA adapter parameters**, while the quantized base model remains frozen.

### 4️⃣ Optimizer Step

The optimizer uses those gradients to make a small update to the trainable parameters.

Then the process repeats:

> **Forward → Loss → Backward → Optimizer → Repeat 🔁**

---

## 🧠 Today's Biggest Takeaway

Today helped me realize that fine-tuning isn't just:

> `model.train()` → wait → hopefully good model 😂

There are a lot of decisions hiding underneath it:

**What to train → how much to train → how fast to train → how much data to process at once → how to manage memory → how to prevent overfitting.**

Understanding these settings beforehand should make it much easier to interpret what happens once I finally start training.

And yes...

**Tomorrow I am ACTUALLY fine-tuning.** 👀

Hopefully. 😭🔥

🎯 **Day 57 complete.**
