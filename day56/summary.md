# Day 56 – Baseline Evaluation, a Qwen Failure & Switching to Llama 3.2 🦙📉

Today did **not** go according to yesterday’s plan 😭

I was supposed to start fine-tuning, but before changing the model I wanted to establish a proper **zero-shot baseline** and see how well the quantized model could predict product prices using only its existing knowledge.

## 1. Qwen3 decided every product costs $0 💀

I started by evaluating the **4-bit quantized Qwen model** on the test dataset.

The idea was simple:

> Product description → model → predicted price

Unfortunately, Qwen had other plans.

For some reason, it repeatedly predicted:

> **$0**

for basically every item.

I spent around an hour trying different things and rerunning the inference, but nothing fixed the behaviour.

So rather than losing the entire day debugging the same issue, I switched models.

---

## 2. Moving to Llama 3.2 3B 🦙

I switched to **Llama 3.2 3B**, which required getting access permission from Meta first.

One interesting thing I noticed while looking at its tokenizer was that its handling of many **three-digit numbers** is particularly convenient for this project.

Since a large portion of the products fall somewhere around the sub-$1000 range, having prices represented compactly in tokens should make the price-generation task a little more natural than unnecessarily splitting every number into many pieces.

---

## 3. Building the inference function

Before evaluating the entire test set, I wrote a small prediction function:

```python
def model_predict(item):

    inputs = tokenizer(
        item["prompt"],
        return_tensors="pt"
    ).to("cuda")

    with torch.no_grad():
        output_ids = base_model.generate(
            **inputs,
            max_new_tokens=8
        )

    prompt_len = inputs["input_ids"].shape[1]
    generated_ids = output_ids[0, prompt_len:]

    return tokenizer.decode(generated_ids)
```

The important part here was:

```python
with torch.no_grad():
```

because I’m only doing **inference**, not training yet. There is no reason to calculate or store gradients.

I tested it on a distortion/modulation pedal with a true price of:

> **$219**

The model predicted:

> **$129.99**

…and then started writing an explanation before my `max_new_tokens=8` politely chopped it off 😂

So at least Llama was actually attempting the task.

---

## 4. Zero-shot evaluation results 📊

I then ran Llama 3.2 3B across the evaluation set.

The results were:

> 💵 **Mean absolute error: ~$120.84**
> 📉 **R²: -246.1%**

So... definitely not great 😭

The untuned model performed **worse than my human baseline** and only somewhat better than some of the very weak baseline approaches I tested earlier.

But that is actually useful information.

This gives me a clear **before fine-tuning benchmark**.

If LoRA training works, I’ll be able to compare the fine-tuned model against exactly the same evaluation and see whether it genuinely learned something rather than just assuming it improved.

## 🧠 Today’s biggest takeaway

Today was a good reminder that the experiment before training matters just as much as training itself.

Qwen refusing to cooperate was frustrating, but switching to Llama gave me something more valuable:

> **a measurable zero-shot baseline before LoRA.**

Right now:

**Llama 3.2 3B → MAE ~$120.84 → R² -246.1%**

Tomorrow, the plan is to finally attach the **LoRA adapters**, train them on the price dataset, and see whether those numbers can actually move in the right direction. 👀🔥

🎯 **Day 56 complete.**
