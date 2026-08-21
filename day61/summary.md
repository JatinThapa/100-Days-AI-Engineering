# 100 Days of AI – Day 61 🚀

## Finally Testing the Fine-Tuned Llama 3.2 3B Model 🧪

Today was finally **test day**.

After spending the last several days preparing the dataset, quantizing Llama 3.2 3B, configuring LoRA, fine-tuning the model, monitoring the training process with Weights & Biases, and understanding how the loss calculation works, I finally tested the fine-tuned model on **completely unseen test data**.

The first step was loading the model back from **Hugging Face**, where I had saved the final checkpoint after training.

I loaded the tokenizer and the quantized base model, and then used **PEFT's `PeftModel`** to attach the trained LoRA adapters back onto the base model.

One thing I really liked about this step was actually printing the architecture and seeing the LoRA layers inside the model.

For example, the attention projections were now showing structures like:

`q_proj → lora.Linear4bit`

with separate **LoRA A and LoRA B matrices** sitting on top of the quantized base layer.

So instead of just trusting that fine-tuning had happened, I could actually see the adapter matrices being applied to the attention layers. That made the whole QLoRA process feel much more tangible. 🧠

Then came the part I had been waiting for:

**200 completely unseen test questions.**

And honestly… the results weren't as dramatic as I expected, but they were still pretty encouraging.

### 📊 Fine-Tuned Llama 3.2 3B Results

💵 **Mean Error: $64.68**
📈 **R²: 40.0%**

For comparison, my earlier zero-shot baseline was:

💵 **Mean Error: $120.84**
📉 **R²: -246.1%**

So the fine-tuning definitely made a significant difference.

The model went from an R² of **-246.1% to +40%**, while cutting the average prediction error almost in half.

That was a pretty satisfying result considering I was working with a relatively small **3B parameter open-source model**, limited compute, a relatively small training dataset, and QLoRA rather than full fine-tuning.

However, it still wasn't the best model I had seen during this project.

I also tested a different model that had been trained on the much larger **800,000-item dataset** using an **A100 with 80 GB of VRAM** for around **17 hours**.

And that model achieved:

💵 **Mean Error: $42.67**
📈 **R²: 71.8%**

That model clearly performed better than my own fine-tuned model.

But there is an important distinction here.

The larger model was trained with significantly more data and much more compute, and the prediction task itself was deliberately constrained to a specific business range of **$0–$999** to make the problem more precise.

So I'm not disappointed by the comparison.

Actually, I'm pretty happy with what this experiment demonstrated.

With relatively limited resources, I was able to take an open-source **Llama 3.2 3B** model, quantize it, apply LoRA adapters, fine-tune it on a custom price-prediction dataset, and get a model that meaningfully improved its performance on unseen data.

And I was able to do all of that without access to the kind of expensive compute that was used for the 800K-item experiment.

### 🎯 What I Learned

This experiment taught me that fine-tuning isn't about magically turning a small LLM into the best possible model.

It's about **adapting a general-purpose model to a specific task efficiently**.

The results also reinforced something I've been learning throughout this project:

**Data, compute, model architecture, training strategy and task design all matter.**

More compute and more training data can make a huge difference, but even with constrained resources, techniques like **QLoRA and PEFT** make it possible to adapt relatively large models without having to fine-tune every parameter.

And now that I've finally gone through the complete process — from dataset preparation → quantization → LoRA → training → evaluation → testing — I think it's time to move on from this experiment.

### 🚀 What's Next?

The next step is to take everything I've learned from this project and apply it to something much closer to what I've been wanting to build:

**an agentic AI system.** 🤖

So after weeks of working with RAG, vector databases, evaluation, machine learning and LLM fine-tuning, I'm finally moving toward **AI agents and agentic workflows**.

🎯 Day 61 complete.
