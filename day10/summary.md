# Day 10 – Learning Tool Calling in LLMs 🛠️🤖

Today I learned one of the most important foundations of **agentic AI**: **tool calling**.

I understood that LLMs do not directly execute tools by themselves. Instead, we define tools as normal functions inside our program and describe them to the LLM using a **JSON schema**. The LLM then decides when a tool is needed and responds with a tool call request.

After that, it is our code that reads the tool call, executes the actual function, gets the result, and sends that result back to the LLM so it can continue reasoning or generate the final answer.

This helped me realize that agents are not magic ✨  
They are built using a loop where the LLM can:

- Think about the user’s request 🧠
- Decide if a tool is needed 🛠️
- Request a tool call
- Receive the tool result
- Decide whether another tool is needed
- Finally summarize everything into a useful response ✅

I also built a mini **Airline AI Flight Assistant** where the LLM could call a `get_ticket_price` tool to fetch flight prices.

At first, I handled only one tool call at a time. But then I realized that if a user asks for multiple ticket prices in a single prompt, the system needs to process all of them. So I improved the logic to support **multiple tool calls** in one response.

Later, I made the system even better by replacing a simple `if` condition with a `while` loop. This allowed the LLM to keep calling tools until it had enough information to answer properly 🔁

Finally, I learned a bit about **SQLite3** and used it to store hardcoded flight prices in a database instead of keeping everything directly inside the code. This made the project feel more realistic and closer to how actual AI applications interact with external data sources.

Overall, Day 10 helped me understand how LLMs move from simple chatbots to actual **software agents** that can use tools, interact with data, and solve tasks step by step 🚀
