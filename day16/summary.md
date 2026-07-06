# Day 16 Summary – Understanding Tokenizers in LLMs 🚀

Today I explored **tokenizers** used by different LLMs and finally understood one of the most important missing pieces behind how models actually process input.

I started with Meta’s **Llama 3.1 model** on Hugging Face:

```text
meta-llama/Meta-Llama-3.1-8B
```

One funny thing I noticed was that the model is gated, so I had to agree to share my contact information before accessing it 😄

While exploring Llama’s tokenizer, I learned about **special tokens** like:

```text
<|begin_of_text|>
<|start_header_id|>
<|end_header_id|>
<|eot_id|>
```

These tokens help structure conversations by marking where the text begins, where the system/user/assistant messages start, and where a turn ends.

The important realization was that these special tokens are **not built into the transformer architecture itself**. They are part of the tokenizer and chat formatting system, and the model learns their meaning through training.

## The Big Aha Moment 💡

I used to think that when we pass messages like this:

```python
messages = [
    {"role": "system", "content": "You are a helpful assistant"},
    {"role": "user", "content": "Tell a light-hearted joke for a room of Data Scientists"}
]
```

the LLM somehow directly receives these Python dictionaries.

But that is not what happens.

An LLM is just a model that takes a **sequence of numbers** and predicts the probability of the next number.

So the actual flow looks like this:

```text
Messages
➡️ Chat template with special tags
➡️ Text
➡️ Tokens
➡️ Token IDs
➡️ LLM input
```

The input to an LLM is not Python objects, not dictionaries, and not raw text.

It is a sequence of **token IDs**.

The output is a probability distribution over the next token ID.

That one idea made the whole chat-completion process much clearer.

## Exploring Other Tokenizers 🤖

I also tried tokenizers from other models like:

* **Phi-4** by Microsoft
* **DeepSeek 3.1** by DeepSeek AI
* **Qwen2.5-Coder-7B-Instruct** by Alibaba Cloud

This helped me see that different models can tokenize the same text differently.

One interesting example was Qwen Coder, where code was tokenized into meaningful fragments:

```text
750   = def
23811 = hello
31792 = _world
29766 = (person
982   = ):

1173  = print
9707  = Hello
1697  = person
```

This showed me that coding models often tokenize code in a way that preserves useful programming patterns, instead of simply breaking everything character by character.

## Key Takeaways 🧠

Today I learned that:

* LLMs do not directly understand Python dictionaries.
* Chat messages are converted into model-specific text formats.
* Special tokens separate system, user, and assistant messages.
* Tokenizers convert text into tokens.
* Tokens are converted into token IDs.
* The transformer processes only numbers.
* The model predicts the next token ID, one step at a time.
* Different models use different tokenizers.
* Coding models can tokenize code in a more code-friendly way.

## Final Thought 🎯

Behind all the fancy APIs and chatbot interfaces, the core idea is surprisingly simple:

```text
Text becomes tokens.
Tokens become numbers.
The model predicts the next number.
Numbers become text again.
```

And somehow, from that repeated next-token prediction process, we get chatbots, coding assistants, agents, and AI applications.

Pretty wild 😄
