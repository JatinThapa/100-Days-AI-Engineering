# Day 58 – Finally Fine-Tuning with QLoRA 🚀

Today was finally the day I **stopped preparing to fine-tune and actually started fine-tuning** 😂

After several days of dataset preparation, model exploration, quantization and hyperparameter revision, I kicked off training **Llama 3.2 3B** on my 20,000-item price-prediction dataset.

## 1. Setting Up Training Tracking 📊

I first created a **Weights & Biases (W&B)** account and connected it to my Colab notebook so I could monitor the training progress, losses and evaluation metrics while the model trains.

This is especially useful since the training is expected to take around **2 hours**.

---

## 2. Overall Training Configuration ⚙️

I started by defining the main training parameters:

```python
EPOCHS = 1 if LITE_MODE else 3
BATCH_SIZE = 32 if LITE_MODE else 256
MAX_SEQUENCE_LENGTH = 128
GRADIENT_ACCUMULATION_STEPS = 1
```

For the current experiment:

* 📚 Dataset: **20,000 items**
* 🔄 Epochs: **1**
* 📦 Batch size: **32**
* 📏 Maximum sequence length: **128**
* ➕ Gradient accumulation: **1**

I chose **128 tokens** as the maximum sequence length to keep memory usage manageable and because powers of two are convenient when working with GPU memory.

For now, I’m also not using gradient accumulation.

---

## 3. Setting Up the QLoRA Parameters 🧩

I then configured the LoRA adapters:

```python
QUANT_4_BIT = True
LORA_R = 32
LORA_ALPHA = LORA_R * 2
LORA_DROPOUT = 0.1
```

For this smaller experiment, I targeted the attention layers:

```text
q_proj
k_proj
v_proj
o_proj
```

The larger experiment can eventually include the MLP layers as well:

```text
gate_proj
up_proj
down_proj
```

So the idea remains:

> 🧊 Frozen + 4-bit quantized base model
> 🧩 Small trainable LoRA adapters
> 🎯 Update only the adapter parameters

---

## 4. Learning Rate & Optimization 📈

I also configured the main optimization parameters:

```python
LEARNING_RATE = 1e-4
WARMUP_RATIO = 0.01
LR_SCHEDULER_TYPE = "cosine"
WEIGHT_DECAY = 0.001
OPTIMIZER = "paged_adamw_32bit"
```

I’m using **AdamW** rather than basic SGD, along with a **cosine learning-rate scheduler**.

I also added a small warmup period so the learning rate doesn't immediately jump to its maximum value at the beginning of training.

---

## 5. Evaluation & Checkpointing 💾

I configured the training process to evaluate the model periodically:

```python
VAL_SIZE = 500
LOG_STEPS = 5
SAVE_STEPS = 100
```

The model will be evaluated every **100 training steps**, alongside checkpoint saving.

I also set:

```python
save_total_limit = 10
```

so I don't end up filling the Colab environment with dozens of model checkpoints and eventually running into memory/storage problems 😭

---

## 6. Starting the Actual Fine-Tuning 🔥

After quantizing the base model and creating the `LoraConfig`, I used **TRL's `SFTTrainer`** to combine:

* The quantized Llama model
* Training dataset
* Validation dataset
* LoRA configuration
* Training configuration

And finally...

```python
fine_tuning.train()
```

**IT ACTUALLY STARTED.** 😂🔥

Once training finishes, I’m also pushing the resulting fine-tuned model to Hugging Face so I can reuse it later.

The current training run is expected to take roughly **2 hours**.

---

## 🧠 Today's Biggest Takeaway

Today was the point where all the theory from the last few days finally came together:

**Quantization + LoRA + Token limits + Learning rate + Scheduler + Optimizer + Evaluation + Checkpointing**

all working together inside one actual fine-tuning pipeline.

After spending so many days preparing for this, seeing the training process finally start was honestly pretty satisfying 😂

Tomorrow, the important part begins:

> **Evaluate the fine-tuned model on the completely unseen test dataset and see whether LoRA actually improved that terrible $120.84 MAE baseline.** 👀📊

🎯 **Day 58 complete.**
