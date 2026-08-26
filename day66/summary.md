### Day 66 – Deploying My Fine-Tuned Llama Model with Modal & Model Caching ☁️⚡

Today was the day I finally deployed my fine-tuned Llama pricing model to the cloud. After spending the last few weeks training, evaluating, and testing it locally, it was exciting to expose it as an actual cloud service that could handle requests remotely.

The deployment itself turned out to be surprisingly simple—but optimizing it for real-world use taught me an important lesson about cold starts and model caching.

### 🚀 Deploying the Model to Modal

The deployment command was literally a single line:

Bash

```
uv run modal deploy -m pricer_service
```

Modal packaged my code into a Linux container, provisioned a GPU instance, and deployed it as a remote service. I could even watch requests being executed inside the Modal dashboard.

The core of the service was a `price()` function decorated with `@app.function`, which Modal runs remotely on a T4 GPU.

Inside that function, the workflow was:

* Receive a product description.

* Build a prompt in the format the model was trained on.

* Load the tokenizer and the 4-bit quantized Llama model.

* Attach my LoRA adapters using PEFT.

* Generate the predicted price.

* Extract the numeric value using a regex and return it as a float.

It was a complete inference pipeline running entirely in the cloud.

### 💸 First Deployment... and the Cold Start Problem

I sent my first request from Cursor.

The prediction worked... but it took about 1.5 minutes.

That immediately made sense after looking at what the function was doing. Every request was:

* Downloading or loading model weights.

* Initializing the tokenizer.

* Loading the quantized base model.

* Loading the LoRA adapters.

In other words, every function invocation was paying the full startup cost.

I also noticed something interesting about Modal's execution model:

> Every time the function is invoked, Modal charges a small amount for that GPU execution.

So reducing startup time isn't just about speed—it's also about making the deployment more efficient.

### ⚡ Version 2: Persistent Model Caching

To solve the cold start issue, I created a second deployment file called `pricer_service2`.

Instead of exposing a standalone function, I converted the service into a class-based Modal app using `@app.cls`.

This version introduced a persistent Hugging Face cache:

Python

Run

```
@app.cls(
    image=image.env({"HF_HUB_CACHE": CACHE_DIR}),
    volumes={CACHE_DIR: hf_cache_volume},
    ...
)
```

The important addition was a persistent volume mounted inside the container. This allows Hugging Face model files to remain cached instead of being downloaded and initialized from scratch every time.

### 🧠 Loading the Model Once with `@modal.enter`

Inside the `Pricer` class, I added a `setup()` method decorated with `@modal.enter()`.

This method runs once when the container starts.

During setup, the container:

* Loads the tokenizer.

* Loads the 4-bit quantized Llama base model.

* Attaches the fine-tuned LoRA weights.

* Stores everything as instance variables (`self.tokenizer`, `self.base_model`, `self.fine_tuned_model`).

That means subsequent requests reuse the already-loaded model instead of rebuilding it every time.

It felt much cleaner from an OOP perspective too—the model becomes part of the service's state rather than something recreated inside every function call.

### 📊 The Performance Difference

The results were immediately noticeable.

<table class="_6IUVGW_Table" data-d-column-sizing="equal" data-d-dividers="" style="table-layout: fixed;"><tbody><tr data-d-component="table-row"><td data-d-component="table-cell" data-d-valign="start"><p class="w6asjq_TextBase _85PZeG_Text" data-d-component="text"><span class="w6asjq_TextBase _85PZeG_Text" data-d-component="text" data-d-default-strong="" data-d-inline="">First deployment (<code class="er4J8W_Code" data-d-component="code">@app.function</code>)</span></p></td><td data-d-component="table-cell" data-d-valign="start"><p class="w6asjq_TextBase _85PZeG_Text" data-d-component="text"><span class="w6asjq_TextBase _85PZeG_Text" data-d-component="text" data-d-default-strong="" data-d-inline="">Cached deployment (<code class="er4J8W_Code" data-d-component="code">@app.cls</code>)</span></p></td></tr><tr data-d-component="table-row"><td data-d-component="table-cell" data-d-valign="start">Every request loads model weights.</td><td data-d-component="table-cell" data-d-valign="start">Model loads once during container startup.</td></tr><tr data-d-component="table-row"><td data-d-component="table-cell" data-d-valign="start">First request: ~1.5 minutes.</td><td data-d-component="table-cell" data-d-valign="start">First request: ~1 minute (container warm-up).</td></tr><tr data-d-component="table-row"><td data-d-component="table-cell" data-d-valign="start">Every following request also pays startup cost.</td><td data-d-component="table-cell" data-d-valign="start"><p class="w6asjq_TextBase _85PZeG_Text" data-d-component="text">Following requests: <span class="w6asjq_TextBase _85PZeG_Text" data-d-component="text" data-d-default-strong="" data-d-inline="">around 1 second</span>.</p></td></tr></tbody></table>

This was probably the biggest takeaway of the day: warm containers are dramatically faster than cold containers.

### 🎯 What I Learned Today

Today wasn't about improving model accuracy—it was about serving an AI model efficiently.

I learned:

* How to deploy a fine-tuned Hugging Face model on Modal with a single command.

* How Modal runs GPU-powered functions inside Linux containers.

* The difference between cold starts and warm containers.

* How persistent volumes cache Hugging Face model weights.

* How `@modal.enter()` initializes expensive resources only once.

* Why class-based deployments are useful for stateful inference services.

This felt like an important step from training models to building production-ready AI services.

### 🚀 Day 66 Takeaway

A trained model isn't truly useful until people can call it efficiently.

Today I learned that deployment isn't just "putting a model online"—it's about optimizing startup time, caching model weights, and keeping inference fast enough for real applications.
