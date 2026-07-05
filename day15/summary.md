# Day 15 – Hugging Face Pipelines 🤗

Today I explored **Hugging Face pipelines**, which are the high-level APIs provided by the `transformers` library for quickly running open-source AI models.

The main idea is very simple:

```python
my_pipeline = pipeline("task-name")
result = my_pipeline(input)
```

And that is pretty much it.

Pipelines make it extremely easy to plug in a model and use it for common inference tasks without writing too much setup code.

## Training vs Inference

Today I also clarified the difference between **training** and **inference**.

### 1. Training

Training is when a model learns from data by updating its internal parameters or weights.

When we continue training an already trained model on a specific task or dataset, it is called **fine-tuning**.

### 2. Inference

Inference is when we use an already trained model to generate outputs on new inputs.

Most of the work I have done with GPT, Claude, Gemini, OpenRouter, and now Hugging Face pipelines falls under inference.

The **“P” in GPT** stands for **Pre-trained**, meaning the model has already been trained on a large amount of data.

## Pipelines I Tried Today

Today I experimented with several Hugging Face pipelines, including:

### Sentiment Analysis

I used:

```text
nlptown/bert-base-multilingual-uncased-sentiment
```

This model gave a sentiment rating from **1 to 5 stars**, depending on how positive the input text was.

### Named Entity Recognition

I tried Named Entity Recognition using the default model:

```text
dbmdz/bert-large-cased-finetuned-conll03-english
```

This helped detect entities such as names, places, and organizations from text.

### Question Answering with Context

I also tried a Question Answering pipeline where the model answers questions based on a given context.

This felt like a very simple version of **RAG**, because the model was not just answering randomly. It was using the provided context to generate the answer.

The pipeline also returned a confidence score for the answer.

### Text Generation

I experimented with text generation as well.

The funny part was that the default model did not perform very well and started hallucinating badly. It was a good reminder that not every model is suitable for every task.

### Other Pipelines

I also explored:

* Translation
* Text summarization
* Text classification
* Text-to-speech

These experiments showed how broad and beginner-friendly the Hugging Face pipeline API is.

## Transformers vs Diffusers

One important thing I noticed is that not all AI tasks use the same kind of pipeline.

For example, image generation models from **Diffusers** use pipelines like:

```python
AutoPipelineForText2Image
```

This is different from the regular `transformers` pipeline API.

## Final Takeaway

Overall, Day 15 was about understanding how Hugging Face makes model inference simple, fast, and beginner-friendly.

Instead of manually loading models, tokenizers, and writing extra logic, pipelines allow us to directly experiment with different AI tasks using just a few lines of code.

Today made Hugging Face feel less intimidating and more like a giant AI toolbox where you can quickly plug in models and test what they can do.
