# Day 55 – Final Dataset Preparation Before Fine-Tuning 🧹📚

Today was all about giving the dataset one final polish before actually fine-tuning **Qwen3 8B**.

I started with the smaller **22,000-item dataset**, split into:

* **20,000** training samples
* **1,000** validation samples
* **1,000** test samples

The main goal was to decide how long each training sequence should be and then convert every product into a consistent **prompt + completion** format.

## 1. Analysing Token Lengths

First, I loaded the tokenizer for the same Qwen model I’ll be fine-tuning:

```python
BASE_MODEL = "Alibaba-NLP/LaSER-Qwen3-8B"

tokenizer = AutoTokenizer.from_pretrained(BASE_MODEL)
```

Sequence length matters a lot during fine-tuning because **longer sequences require more GPU memory and computation**.

If I simply choose the maximum sequence length in the dataset, shorter examples would need lots of padding, meaning the GPU would spend memory processing tokens that contain no useful information.

After tokenizing all the product summaries, I found:

> 📊 **Average:** 91 tokens
> 📈 **Maximum:** 266 tokens

Instead of supporting all 266 tokens, I decided to truncate summaries at:

```python
CUTOFF = 110
```

With this cutoff:

> ✂️ **2,844 items are truncated**
> 📊 Around **12.9% of the dataset**

This gives me a much more practical sequence length while still preserving most of each product description.

---

## 2. Creating the Training Prompts

Next, I wrote a `make_prompts()` function that:

1. Tokenizes the product summary
2. Truncates it if it exceeds the cutoff
3. Constructs the question for the model
4. Creates the expected price completion

The prompt follows this structure:

```text
What does this cost to the nearest dollar?

<Product Summary>

Price is $
```

And the model is trained to continue it with something like:

```text
79.00
```

So instead of treating price prediction like traditional regression, I’m training the LLM to **generate the price as text**.

---

## 3. Why I Rounded the Training Prices 💵

One particularly interesting decision was rounding the target prices to the **nearest dollar** during training.

For example:

```text
$74.63 → $75.00
```

The reason is that an LLM predicts **tokens**, not continuous numbers like a regression model.

If I force it to learn exact cents, the training loss can punish it for predicting the decimal portion incorrectly even when its overall price estimate is very good.

For this project, correctly estimating whether something costs around **$10, $100 or $1,000** matters much more than predicting whether it costs `$99.47` or `$99.62`.

So during training, I want the model concentrating on the meaningful part of the problem:

> 🎯 **Estimate the approximate dollar value correctly.**

The **test dataset still keeps the original prices including cents**, so I can later evaluate predictions against the actual values using absolute error.

---

## 4. Final Dataset Statistics

After converting everything into the final prompt format:

> 📊 **Average sequence length:** 107.4 tokens
> 📈 **Maximum:** 129 tokens

That gives me a much more compact and predictable dataset for fine-tuning.

Finally, I uploaded the processed dataset to Hugging Face as:

```text
items_prompts_lite
```

So the dataset is now cleaned, token-length controlled, formatted and ready to be loaded directly into the fine-tuning pipeline. 🚀

## 🧠 Today’s biggest takeaway

Preparing an LLM training dataset is not just about cleaning the text.

You also have to think about **token lengths, padding, truncation, GPU memory, prompt structure and even how the training objective interprets numbers**.

A small decision like removing cents from the target can help make sure the model learns the behaviour I actually care about instead of wasting capacity trying to predict unnecessary precision.

Next up: **finally getting Qwen3 ready to learn from this dataset.** 👀🔥

🎯 **Day 55 complete.**
