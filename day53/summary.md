### Day 53 – Loading & Exploring Qwen3 🧠⚙️

Today, I started preparing a **Qwen3 8B model in Google Colab** as the next step toward fine-tuning for price prediction.

I set up the required Hugging Face, Transformers, PEFT, and PyTorch libraries, defined the model and dataset configuration, and loaded the base model using `AutoModelForCausalLM`.

The model had a memory footprint of around **16.4 GB**, which also showed why quantization will be important before fine-tuning larger models efficiently.

I also explored the Qwen3 architecture and revised the main Transformer components:
🔹 Token embeddings
🔹 36 decoder layers
🔹 Q, K, V and output projections
🔹 RMSNorm
🔹 MLP layers with gate/up/down projections
🔹 SiLU activation
🔹 Rotary positional embeddings
🔹 Final language-model head

It was a nice revision of Transformer internals before moving deeper into **quantization, LoRA/QLoRA, and fine-tuning**.

🎯 **Day 53 complete.**
