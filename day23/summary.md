# Day 23 – Revising Llama Decoder Layers and Quantization

Today was a lighter revision day after yesterday’s hackathon rush 😭

I revisited how Llama’s decoder layers work. Each layer mainly contains:

* Self-attention, which uses Query, Key, Value, and Output projections to decide which information from the context matters
* An MLP block, where `up_proj` expands the hidden representation, `gate_proj` filters useful information, and `down_proj` reduces it back to its original size
* Layer normalization, which helps keep the activations stable

I also revised why neural networks need non-linearity. Without activation functions, stacking multiple linear layers would behave like one large linear transformation. Activations introduce distortion between layers, allowing each layer to learn more complex patterns.

While ReLU sets negative values to zero, Llama commonly uses SiLU-based gated activations.

Finally, I revised Hugging Face’s lower-level model APIs and how quantization reduces model-weight precision, such as from 16-bit to 8-bit or 4-bit, allowing larger models to run with less memory.
