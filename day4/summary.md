# 🚀 Day 4 – Transformers, Tokens, Context Windows, and LLM “Memory”

Day 4 was focused on understanding some of the most important ideas behind modern Large Language Models.

## 🧠 Transformers and Their Evolution

Today, I learned about the evolution of Transformer models and how their architecture became the foundation for many of today’s frontier AI systems. A major highlight was learning about the famous Google research paper **“Attention Is All You Need”**, which introduced the Transformer architecture and later became one of the biggest turning points in the development of modern LLMs.

## 🔢 Parameters in Frontier Models

I also explored how frontier models have grown massively over time, from models with millions of parameters to models with billions, and possibly even trillions of parameters. Understanding parameters helped me get a better sense of why larger models can often handle more complex patterns, reasoning, and language tasks, while also requiring more compute and resources.

## ✂️ Tokenization

Another important concept I learned today was **tokenization**. Instead of reading text exactly like humans do, LLMs break text into smaller pieces called tokens. These tokens can be full words, parts of words, punctuation, or even spaces depending on the tokenizer. I tried out tokenizer tools and also experimented with `tiktoken` to see how text gets converted into token IDs before being processed by a model.

## 🪟 Context Windows

This naturally led me to the concept of **context windows**. I learned that every LLM has a limit on how many tokens it can process at once. Different models support different context window sizes, and these limits directly affect how much conversation history, documents, or instructions can be passed to the model in a single request. I also explored how different models have different API costs depending on their token usage and context limits.

## 💬 Connecting It Back to Chatbot Memory

The biggest realization of the day came from connecting this concept back to my Day 2 chatbot with memory.

I understood that an LLM does not actually “remember” anything by default. Every call to an LLM is stateless. This means the model does not automatically know what was said before unless we pass the previous conversation again in the input.

So when we build a chatbot with memory, what we are really doing is sending the conversation history along with every new message. This creates the illusion of memory. The model looks at the full sequence of previous messages and predicts the most likely next tokens based on that context.

For example, if the conversation contains “My name is Ed” and later the user asks “What is my name?”, the model can answer “Ed” because that information exists in the provided context, not because the model permanently remembered it.

## 💸 Tokens, Cost, and Compute

This also explained why longer conversations can become more expensive when using LLM APIs. Since previous messages are repeatedly passed into the model, the input token count keeps increasing. More tokens mean more computation, and more computation means higher cost.

## ✅ Final Reflection

Today had less coding compared to earlier days, but experimenting with `tiktoken` helped me practically understand how text becomes tokens and how token count affects LLM behavior, memory, context, and cost.

Overall, Day 4 helped me understand one of the most important ideas in AI application development: LLM memory is usually not real memory by default. It is created by carefully managing and passing context.
