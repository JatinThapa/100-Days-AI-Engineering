# Day 65 – Taking My Fine-Tuned Model to the Cloud ☁️🤖

Today was all about **running my fine-tuned Llama model in the cloud** and, more importantly, seeing how it behaves outside my local environment.

I started by setting up a **Hugging Face secret in Modal**, giving my Modal environment access to the Hugging Face token required to load my model. I then created a lightweight Linux container with PyTorch, Transformers, and Accelerate, and configured it to run on a **T4 GPU**.

I first tested the basic Llama 3.2 3B model with a simple generation function. And of course, I had to test it with:

> “Never gonna give you up, never gonna…”

The model completed it perfectly:

`Never gonna give you up, never gonna let you down...`

😂 Even in the cloud, I managed to get myself Rick Rolled.

### 💰 Testing My Fine-Tuned Price Predictor

After confirming that the cloud setup was working, I moved on to my actual fine-tuned pricing model.

I gave it a simple description of a **HyperX QuadCast condenser microphone**, which costs around **$139 on Amazon**.

The model predicted:

**$90**

Not exactly an impressive prediction considering all the training that went into it. 😅

But this test made me realize something important: **the way I was prompting the model wasn't really fair.**

During fine-tuning, the model had been trained on structured product information rather than just a raw sentence describing a product.

### 🧹 Adding a Preprocessing Step

To make the inference input more consistent with the training data, I introduced a small preprocessing pipeline using **GPT-OSS-20B through Groq/OpenAI**.

The raw description:

> “Quadcast HyperX condenser mic, connects via USB-C to your computer for crystal clear audio”

was transformed into something much closer to the structure my model had seen during training:

* **Title:** HyperX QuadCast USB Condenser Microphone
* **Category:** Electronics
* **Brand:** HyperX
* **Description:** Crystal-clear audio for streaming and recording
* **Details:** USB-C connectivity, mute button, adjustable gain, and more

I then passed this structured version to my fine-tuned model.

And the result?

**Still $90. 😂**

Apparently, my model has decided that $90 is the answer to everything.

This was actually a useful result, though. It showed me that simply making the inference prompt resemble the training data isn't necessarily enough. There could be deeper issues with the fine-tuning process, dataset distribution, inference setup, or how the model learned the pricing task.

### 🚀 What's Next?

The biggest takeaway from today was that **getting a model to train successfully is only one part of the process**.

Today I managed to:

🔹 Set up a Modal Linux container
🔹 Connect Modal to Hugging Face using secrets
🔹 Run Llama 3.2 3B on a T4 GPU
🔹 Run my fine-tuned model remotely
🔹 Test real-world price prediction
🔹 Experiment with preprocessing before inference
🔹 Identify potential weaknesses in my fine-tuning/inference pipeline

Tomorrow, I'll take the next step: **actually deploying my fine-tuned model** and seeing how far I can take this setup.

One more day of experimenting, debugging, and occasionally getting Rick Rolled. 😄
