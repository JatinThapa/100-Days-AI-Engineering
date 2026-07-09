# 100 Days of AI – Day 19 Summary 🚀

Today was more of a revision and clarity day. I went back to my Day 17 learning and spent time understanding quantization and the lower-level Hugging Face Transformers API more deeply.

The first major concept I revised was **quantization**.

From what I understood better today, quantization is a smart optimization technique used to make large language models lighter and more memory-efficient. A more accurate way to say it is: quantization does not reduce the number of parameters in the model, but it reduces how much memory each parameter takes.

Normally, model weights may be stored in higher precision formats like **16-bit** or **32-bit floating point numbers**. With quantization, we store those same weights in lower precision formats like **8-bit** or even **4-bit**.

So the model keeps mostly the same structure, but the numbers inside it become cheaper to store and compute with.

Basically:

Large model 🧠
Same number of parameters
Lower precision numbers
Less memory usage
Faster and more efficient inference ⚡

One technique I learned about is **NF4**, which stands for **NormalFloat4**. It is a 4-bit quantization format designed to represent model weights efficiently, especially when the weight values follow a roughly normal distribution. Instead of simply chopping numbers down randomly, NF4 tries to store them in a way that still preserves useful information from the original model.

I also explored **bitsandbytes**, a package commonly used with Hugging Face Transformers for loading models in 8-bit or 4-bit precision. It helps make large models usable on limited hardware by replacing normal linear layers with optimized low-bit versions, such as `Linear4bit`.

The quantization configuration I worked with looked like this:

```python
quant_config = BitsAndBytesConfig(
    load_in_4bit=True,
    bnb_4bit_use_double_quant=True,
    bnb_4bit_compute_dtype=torch.bfloat16,
    bnb_4bit_quant_type="nf4"
)
```

This configuration means:

`load_in_4bit=True` loads the model weights in 4-bit precision.

`bnb_4bit_use_double_quant=True` applies an extra level of quantization to make the storage even more efficient.

`bnb_4bit_compute_dtype=torch.bfloat16` means calculations are still performed using `bfloat16`, which gives a good balance between speed and numerical stability.

`bnb_4bit_quant_type="nf4"` tells the model to use the NF4 quantization technique.

After that, I moved into the lower-level Hugging Face Transformers API.

Instead of only using high-level pipelines, I started working more directly with the tokenizer and model classes.

I created messages for a Llama model and passed them through `AutoTokenizer`. The tokenizer converted the text into token IDs, which are basically numbers the model can understand.

One interesting thing I noticed was:

```python
tokenizer.pad_token = tokenizer.eos_token
```

This means the tokenizer uses the end-of-sequence token as the padding token. This is common for some causal language models because they may not have a dedicated padding token by default.

After tokenization, the input matrix was ready to be passed into the model.

Then I loaded the model using:

```python
AutoModelForCausalLM
```

This is Hugging Face’s class for causal language models, also known as **autoregressive language models**. These are models that generate text by predicting the next token one step at a time.

I also passed the quantization config while loading the model, so the model was downloaded and loaded in 4-bit precision. The impressive part was that the model only took around **5.5 GB of memory**, which really showed how powerful quantization can be.

Then I printed the model architecture and saw the actual internal structure of Llama 3.1.

The model had:

An embedding layer
32 decoder layers
Attention blocks
MLP blocks
Layer normalization
Rotary embeddings
A final `lm_head` layer

The first layer was:

```python
Embedding(128256, 4096)
```

This means the model has a vocabulary size of **128,256 tokens**, and each token gets converted into a **4096-dimensional vector**.

In simpler terms, every token is transformed into a long list of numbers that represents its meaning in a way the model can work with. This is called a **vector embedding**.

So instead of the model understanding words like humans do, it understands tokens as numerical vectors.

I also saw that Llama uses **rotary embeddings**, which help the model understand the position of tokens in a sequence. Since transformers do not naturally understand order by themselves, positional information has to be added in some way. Rotary embeddings are one of the techniques used for that.

At the end of the model, there was the `lm_head` layer:

```python
Linear(in_features=4096, out_features=128256, bias=False)
```

This layer takes the final 4096-dimensional hidden representation and converts it into scores for all **128,256 possible tokens** in the vocabulary.

These scores help the model decide which token is most likely to come next.

So the overall flow looks something like this:

Text
➡️ Tokens
➡️ Token IDs
➡️ Embeddings
➡️ 32 transformer decoder layers
➡️ Final hidden representation
➡️ `lm_head`
➡️ Probability scores for the next token
➡️ Generated output

Today also made me realize that although I now understand the starting and ending parts of the model better, there is still a lot to learn about what happens inside the **32 decoder layers**.

Those middle layers are where the real magic happens.

They contain attention mechanisms, MLP layers, activation functions, normalization, and repeated transformations that help the model build deeper understanding from the input and predict the next token.

So Day 19 was not about learning something completely new, but about revisiting an important topic and making the mental picture much clearer.

The biggest takeaway:

Quantization makes large models practical on limited hardware, and Hugging Face’s lower-level API helps reveal that an LLM is not just a mysterious chatbot, but a huge PyTorch neural network made of embeddings, attention layers, MLPs, normalization, and a final prediction layer.

Still a long way to go, but today the black box became slightly less black. 🧠⚡
