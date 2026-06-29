## Day 9 Summary – Building LLM Chatbots with Gradio

Today I explored Gradio’s `ChatInterface()` and used it to build a simple chatbot powered by a free LLM from OpenRouter. What surprised me the most was how easily Gradio created a clean, flexible, Markdown-supported chat interface with very minimal code.

I learned that the callback function inside `gradio.ChatInterface()` can receive two important parameters: `message` and `history`. The `message` contains the latest user input, while `history` stores the previous conversation automatically. This made it much easier to pass the full conversation as context to the LLM without manually managing all the chat memory from scratch.

I also experimented with system prompts by creating a simple sales assistant. The assistant was instructed to tell customers about items on sale and gently encourage them to consider hats whenever they were unsure what to buy.

Later, I got my first look at conditional prompting by dynamically changing the system prompt before calling the LLM. For example, when a customer mentioned a specific product like shoes or belts, the assistant could respond with special instructions about whether that item was available or part of the sale.

Overall, Day 9 helped me understand how simple UI tools like Gradio can quickly turn an LLM script into an interactive chatbot, while system prompts and conditional prompting can make the assistant’s behavior more controlled and practical.
