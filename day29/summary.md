# Day 29 – Revising the Foundations Before Starting RAG

Today was another no-code day, but it was still an important part of my 100 Days of AI journey.

Instead of learning a completely new concept, I spent the day revising several topics from the previous weeks. Tomorrow, I will begin learning about Retrieval-Augmented Generation, or RAG, so I wanted to make sure that the concepts underneath it were clear before moving forward.

## Tokenizers and How LLMs Process Text

I revised how language models do not directly understand words, sentences or Python dictionaries. Before any text reaches the model, it must first be processed by a tokenizer.

The general flow is:

User messages → chat template → tokens → token IDs → model

A chat conversation may initially look like this:

```python
[
    {"role": "user", "content": "Explain transformers"}
]
```

However, the model does not receive this dictionary directly. The tokenizer uses the model’s chat template to convert the messages into a specially formatted string containing role markers and special tokens.

While exploring the Llama 3.1 tokenizer, I encountered tokens such as:

```text
<|begin_of_text|>
<|start_header_id|>
<|end_header_id|>
<|eot_id|>
```

These tokens help the model identify where the conversation begins, which role is speaking and where each turn ends.

The formatted text is then divided into smaller tokens. Each token is converted into a numerical token ID because, ultimately, the LLM processes numbers rather than raw text.

I also revised how different tokenizers may split the same text differently. Code-oriented models such as Qwen Coder may divide code into meaningful fragments such as function names, keywords, punctuation and variable-name components. This can help the model work more efficiently with programming languages.

The most important realization was:

> An LLM receives a sequence of token IDs and repeatedly predicts the most likely next token ID.

## Chat Completions and Conversation History

I revised how chat-completion APIs work and how conversation memory is maintained.

A call such as:

```python
chat.completions.create(...)
```

does not automatically remember previous requests. Every API call is stateless unless the application sends the earlier conversation again.

This means the application must maintain a message history containing roles such as:

* `system`
* `user`
* `assistant`

Whenever a new message is sent, the previous messages are included in the next request. This creates the appearance of memory, even though the model itself is simply processing the full conversation again.

I had previously explored this through an experiment where two different LLMs communicated with one another. Python acted as the middleman and maintained a separate message history for each model.

When one model produced a response, that response was inserted into the other model’s history as a user message. The roles had to be reversed correctly so that each model continued seeing itself as the assistant.

This helped me understand that models do not literally communicate directly. The surrounding application controls the conversation flow, message roles and context supplied to each model.

I also revised the difference between using a raw chat-completions API and using frameworks such as LangChain.

Direct API calls are useful for understanding the underlying workflow and building simple applications. LangChain provides higher-level abstractions for more complex systems involving RAG, tools, agents, memory and chains.

## Gradio User Interfaces

I revised how Gradio can be used to convert Python AI programs into interactive web interfaces without requiring a complete frontend framework.

I previously explored both:

```python
gr.Interface(...)
```

and:

```python
gr.ChatInterface(...)
```

`gr.Interface` is useful for applications with clearly defined inputs and outputs, while `gr.ChatInterface` is designed specifically for chatbot-style conversations.

I also worked with Gradio Blocks, which provides more control over layouts, components, events and multimodal workflows.

Some of the features I previously implemented included:

* Model-selection dropdowns
* Chatbot interfaces
* Streaming responses using `yield`
* Dynamic system prompts
* Text inputs and chat history
* Image-generation outputs
* Text-to-speech audio
* Multimodal assistant layouts

I revised how streaming works by returning partial responses through a generator. Instead of waiting for the entire answer, Gradio updates the interface as new text is generated.

I also remembered that many Gradio problems are not necessarily model problems. They can be caused by mismatched component formats, incorrect return values or outputs being returned in the wrong order.

Important lessons included:

* The number and order of returned values must match the output components.
* Chat history must use the format expected by the installed Gradio version.
* A response may sometimes be `None`, so the application should handle it safely.
* Audio bytes may need to be written to a temporary audio file before being returned.
* UI wiring and data formats are just as important as the AI logic.

## Quantization

I revised quantization, which is a technique used to reduce the memory required to store and run large models.

Model weights are commonly stored using formats such as 32-bit or 16-bit floating-point numbers. Quantization stores these weights using lower-precision formats such as 8-bit or 4-bit.

One important distinction I revised was that quantization is not the same as reducing the number of parameters.

Reducing parameters changes the model’s architecture or size. Quantization keeps approximately the same model structure and number of parameters but represents the weights using fewer bits.

In simple terms:

Same model structure
Lower numerical precision
Less memory usage
Potentially faster inference

This makes it possible to run larger open-source models on hardware with limited GPU memory.

I also revised the use of Hugging Face’s `BitsAndBytesConfig` for loading models in 4-bit precision, including settings such as:

```python
load_in_4bit=True
bnb_4bit_use_double_quant=True
bnb_4bit_compute_dtype=torch.bfloat16
bnb_4bit_quant_type="nf4"
```

NF4, or NormalFloat 4, is designed for neural-network weights that approximately follow a normal distribution.

Double quantization further reduces memory usage by also quantizing some of the values used during the first quantization process.

I previously tested quantized versions of models from families such as:

* Phi
* Gemma
* Qwen
* DeepSeek

I also learned that not every model architecture or hardware setup supports quantization equally well. Smaller models do not always benefit dramatically, and compatibility between the model, GPU, PyTorch, CUDA and the quantization library can affect whether the model loads successfully.

## Hugging Face Pipelines

I revised Hugging Face’s high-level Pipeline API.

The pipeline abstraction allows developers to perform inference using a task name without manually handling every tokenizer and model step.

For example:

```python
pipeline("sentiment-analysis")
```

can automatically load the required tokenizer, model and preprocessing logic.

I previously explored pipelines for tasks including:

* Sentiment analysis
* Text classification
* Named-entity recognition
* Question answering
* Translation
* Summarization
* Text generation
* Text-to-speech
* Automatic speech recognition

Some of the models I experimented with included:

* `nlptown/bert-base-multilingual-uncased-sentiment`
* `dbmdz/bert-large-cased-finetuned-conll03-english`
* `openai/whisper-medium.en`

I also used Whisper inside an audio-to-meeting-minutes workflow.

The process was:

Audio file → speech recognition → transcript → LLM processing → structured Markdown meeting minutes

This demonstrated how different AI models can be combined into a pipeline instead of relying on one model to perform every task.

I also revised the difference between training and inference.

Training changes a model’s weights using data, while inference uses an already-trained model to produce predictions. Fine-tuning continues training an existing model on a smaller, specialised dataset.

## Hugging Face’s Lower-Level Transformers API

Alongside pipelines, I revised the lower-level Hugging Face Transformers API.

Instead of allowing `pipeline()` to handle everything automatically, the lower-level API gives more direct control through classes such as:

```python
AutoTokenizer
AutoModelForCausalLM
```

The basic workflow is:

1. Load the tokenizer.
2. Format the conversation using the chat template.
3. Convert the text into token IDs.
4. Send those token IDs into the model.
5. Generate new token IDs.
6. Decode the output back into readable text.

This helped connect the tokenizer concepts with actual model inference.

I also previously inspected parts of a transformer model, including:

* Token embeddings
* Attention layers
* Query, key and value projections
* Output projections
* MLP layers
* Up projections
* Gating and nonlinear activation functions
* Down projections
* RMS normalization
* Rotary positional embeddings
* Decoder layers
* The final language-model head

Understanding the lower-level API made the model feel less like a single mysterious function and more like a sequence of understandable processing steps.

## Hugging Face as an AI Ecosystem

I also revised that Hugging Face is not simply a website for downloading LLMs.

Its ecosystem includes:

* Open-source models
* Datasets
* The Transformers library
* The Diffusers library
* Tokenizers
* Model documentation
* Hosted Spaces
* Inference tools
* Community repositories

Hugging Face Spaces allow developers to host interactive AI applications, commonly using Gradio.

I previously used Google Colab alongside Hugging Face because it provides access to remote compute resources, including free GPU runtimes. However, Colab environments can reset, lose installed dependencies and require the setup cells to be run again.

This taught me that working with AI is not only about selecting a model. It also involves understanding environments, dependencies, GPU memory and deployment platforms.

## AI Leaderboards and Model Selection

Finally, I revised the AI leaderboards I explored recently, including:

* Artificial Analysis
* Hugging Face leaderboards
* Vellum
* SEAL
* LiveBench

These platforms compare models using benchmarks related to reasoning, coding, scientific knowledge, agentic tasks, domain-specific problem solving, speed and cost.

Artificial Analysis stood out because its Intelligence Index combines results from multiple evaluations rather than relying on a single benchmark.

I also explored graphs showing frontier-model intelligence improving across different generations.

However, the most useful comparison was intelligence versus cost per task.

It showed that the most intelligent model is not automatically the best model for every application. A slightly less capable model may be faster, cheaper and still completely sufficient for the required task.

Choosing an LLM should therefore involve comparing:

* Intelligence
* Task-specific performance
* Cost
* Speed
* Context-window size
* Reliability
* Knowledge cutoff
* Hardware requirements
* API availability
* Privacy requirements

The correct model depends on the problem being solved, not simply on which model is ranked first.

## Preparing for RAG

Today’s revision helped connect many topics that will be useful when I begin learning RAG.

A RAG system still depends on tokenizers because retrieved text must fit inside the model’s context window.

It uses chat-completion concepts because the retrieved information is inserted into the messages or prompt supplied to the LLM.

It may use Hugging Face models and APIs for embeddings, retrieval or text generation.

Quantization can make it possible to run the generation or embedding model locally with limited hardware.

Gradio can provide the user interface through which someone asks questions and views the generated answers.

Leaderboards and model evaluation can help identify which embedding model or generation model is most suitable for the application.

So, even though today involved no coding, it was not an empty day. It was a consolidation day.

Instead of immediately jumping into RAG with half-remembered concepts, I reviewed the major building blocks first. Tomorrow, I can begin learning how external information is retrieved, added to an LLM’s context and used to produce more grounded answers.
