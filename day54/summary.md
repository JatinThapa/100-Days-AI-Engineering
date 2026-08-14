# Day 54 – Quantizing Qwen3 & Understanding LoRA Parameter Size ⚙️🧠

Today, I continued preparing the **Qwen3 8B model** for fine-tuning. After exploring the model architecture yesterday, today’s focus was on **quantization** and understanding how much additional memory the LoRA adapters would require.

## 1. Quantizing Qwen3 to 8-bit

Yesterday, loading the original Qwen3 8B model gave me a memory footprint of roughly:

> **16.4 GB**

Today, I used Hugging Face’s `BitsAndBytesConfig` to load the model in **8-bit precision**:

```python
quant_config = BitsAndBytesConfig(load_in_8bit=True)

base_model = AutoModelForCausalLM.from_pretrained(
    BASE_MODEL,
    quantization_config=quant_config,
    device_map="auto",
)
```

After quantization, the memory footprint dropped to:

> **9.4 GB**

So just by reducing the precision of the model weights, I went from approximately:

**16.4 GB → 9.4 GB** 📉

That was a pretty clear practical demonstration of why quantization is so useful when working with large language models.

An important thing I noticed was that the **architecture itself did not suddenly change**. The model still contained the same major components:

* 36 Transformer decoder layers
* Q, K, V and output projections
* MLP `gate_proj`, `up_proj` and `down_proj`
* RMSNorm layers
* Rotary embeddings
* Token embeddings
* Final LM head

Quantization mainly changes **how the model weights are represented in memory**, rather than redesigning the Transformer architecture.

---

## 2. Taking it further with 4-bit quantization

Next, I tried loading the same model using **4-bit quantization**:

```python
quant_config = BitsAndBytesConfig(
    load_in_4bit=True,
    bnb_4bit_use_double_quant=True,
    bnb_4bit_compute_dtype=torch.bfloat16,
    bnb_4bit_quant_type="nf4"
)
```

Here I used:

* `load_in_4bit=True` → stores the model weights using 4-bit quantization
* `bnb_4bit_quant_type="nf4"` → uses **NF4 (NormalFloat4)** quantization
* `bnb_4bit_use_double_quant=True` → further quantizes some of the quantization metadata
* `bnb_4bit_compute_dtype=torch.bfloat16` → calculations can still happen using `bfloat16`

After loading the model again, its memory footprint dropped further to:

> **5.96 GB** 🤯

So my experiment today basically looked like:

**Original model:** 16.4 GB
⬇️
**8-bit:** 9.4 GB
⬇️
**4-bit NF4:** 5.96 GB

This made yesterday’s QLoRA theory feel much more concrete. Instead of keeping an 8B model at full precision, I can keep the large pretrained model **frozen and heavily quantized**, while only training a much smaller collection of LoRA parameters.

---

## 3. Calculating the size of the LoRA adapters

I then wanted to understand just how small the trainable portion of the model would actually be.

For the experiment, I considered a LoRA rank of:

```python
r = 32
```

For each target module, LoRA introduces two low-rank matrices.

I calculated their parameter counts for the four attention projections:

```text
q_proj
k_proj
v_proj
o_proj
```

Because Qwen3 uses different dimensions for some of these projections, their LoRA parameter counts are also different.

For example:

```python
lora_q_proj = 4096 * r + 4096 * r
lora_k_proj = 4096 * r + 1024 * r
lora_v_proj = 4096 * r + 1024 * r
lora_o_proj = 4096 * r + 4096 * r
```

I added them together to get the LoRA parameters for one decoder layer:

```python
lora_layer = (
    lora_q_proj
    + lora_k_proj
    + lora_v_proj
    + lora_o_proj
)
```

Since Qwen3 8B contains **36 decoder layers**:

```python
params = lora_layer * 36
```

The result was:

> **30,670,848 trainable LoRA parameters**

That is around **30.7 million parameters**.

Assuming **4 bytes per parameter**, the calculated storage requirement was:

> **≈ 122.7 MB**

The exact memory used during training can differ depending on the adapter datatype, gradients, optimizer states and activations, but this calculation gave me a much better intuition for the scale.

An **8-billion-parameter base model** can therefore be adapted by training only around **30 million parameters** for these selected attention modules. 🤯

---

## 🧠 Today’s biggest takeaway

Today connected the two halves of **QLoRA** really nicely.

### Quantization

Reduce the memory required to hold the massive pretrained base model:

**16.4 GB → 9.4 GB → 5.96 GB**

### LoRA

Instead of updating billions of base-model parameters, introduce relatively small trainable adapter matrices.

In my current configuration:

**Qwen3 8B base model** → frozen + 4-bit quantized
**LoRA adapters** → ~30.7M trainable parameters across the selected attention modules

So the idea behind QLoRA is becoming much clearer in practice:

> **Keep the huge model compressed and frozen, then teach it new behaviour by training only a tiny fraction of additional parameters.**

Tomorrow, I’ll finally move from preparing the model to **actually attaching and fine-tuning the LoRA adapters on the target modules**. 👀🔥

🎯 **Day 54 complete.**
