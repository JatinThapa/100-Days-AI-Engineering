# Day 6 Summary – LLM APIs, Prompt Caching & Multi-LLM Conversations

Today I explored some important practical concepts in AI application development.

I started by understanding the difference between **`chat.completions.create()`**, **LiteLLM**, and **LangChain**. The raw chat completion API is useful for direct model calls, LiteLLM helps create a common interface across multiple providers, and LangChain is better suited for building larger LLM workflows involving chains, tools, agents, memory, and RAG.

I also learned about **prompt caching** and how it can reduce repeated processing costs when the same prompt prefix is reused. A key takeaway was that cache hits only work when the beginning of the prompt matches exactly. This means static content like system instructions, examples, tools, and images should be placed at the beginning, while dynamic user-specific content should go near the end.

Another interesting point was how different providers price cached inputs differently. OpenAI offers cheaper cached input tokens, while Claude requires an upfront cost to prime the cache but gives much cheaper cached usage afterward.

Finally, I experimented with making two or more LLMs talk to each other. First, I learned the more manual method of maintaining separate message lists and appending the latest response, such as using `gpt_messages[-1]`. Then I learned a cleaner approach: maintaining one shared conversation transcript and dynamically passing it into each model with a system prompt and user prompt.

Overall, today helped me understand not just how to call LLMs, but how to structure conversations, manage prompts, and think more clearly about building multi-model AI workflows.
