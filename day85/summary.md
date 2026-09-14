# Day 85 — Building an Autonomous Planning Agent from First Principles 🤖🛠️

Today was another deep dive into **Agentic AI**, but this time I went back to the fundamentals and built the core of an autonomous planning agent **from scratch**, without relying on high-level agent frameworks to hide the implementation details.

The focus was on understanding what actually happens when an LLM needs to **decide which tools to use, execute them, observe their results, and continue working toward a goal**.

### 🔧 Building the Tools

I started by creating three mock tools representing the capabilities my agent would eventually need:

🔎 **`scan_internet_for_deals`** → Simulates searching the web and returns serialized JSON deal information.

💰 **`estimate_true_value`** → Takes a product description and returns an estimated market value.

📩 **`notify_user_of_deal`** → Takes the deal price, estimated true value, and URL, and triggers a notification.

These tools are intentionally simple, but they represent the building blocks an autonomous deal-finding agent could use in the real system.

### 📋 Manually Defining Tool Schemas

Rather than letting an agent framework automatically generate the tool definitions, I manually created the **JSON Schema** for each function.

For every tool, I specified things like:

* Function name
* Description
* Parameters
* Parameter types
* Required fields

I then combined these definitions into the API's `tools` array.

This gave me a much clearer understanding of how an LLM actually gets informed about the tools available to it. The model isn't magically aware of Python functions—it receives a structured description of **what tools exist and what arguments they expect**.

### 🧠 Dynamic Tool Execution with `globals()`

The next challenge was figuring out how to execute whichever tool the LLM requested.

Instead of writing a huge chain of `if/else` statements for every possible tool, I used Python's **`globals()`** registry.

The basic idea is:

**LLM returns tool name → find matching Python function → execute it**

So if the model asks for `estimate_true_value`, the runtime can dynamically find that function and execute it.

This makes the architecture much more extensible because adding another tool doesn't necessarily mean rewriting the entire execution router.

### 🔄 Building the Agentic Loop

The most important part of today's work was putting everything into an **iterative message loop**.

The basic flow now looks like:

**User Goal**
↓
**LLM decides what to do**
↓
**LLM requests a tool**
↓
**Python executes the tool**
↓
**Tool result is added back to the conversation**
↓
**LLM observes the result**
↓
**LLM decides the next action**
↓
**Repeat until the goal is completed**

I implemented this using **GPT-4.1**, feeding the tool execution results back into the message history using the `tool` role.

This is the part that really made the concept of an autonomous agent click for me.

The model isn't simply generating one answer. It's participating in a **reason → act → observe → reason again** loop.

### 💡 Today's Takeaway

Today's experiment helped me understand that an agent isn't necessarily some mysterious new type of AI.

At its core, it's an **LLM connected to tools through a feedback loop**, where the model can decide what action to take based on the information it receives.

Frameworks can make this incredibly convenient, but building the core mechanics myself made the underlying architecture much easier to understand.

And seeing the flow work from **tool schemas → tool calls → dynamic execution → tool results → another LLM decision** was probably the most valuable part of today's session. 🧠🔗

🎯 **Day 85 complete.**
