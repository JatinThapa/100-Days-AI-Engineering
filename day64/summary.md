# 100 Days of AI – Day 64 🚀

## Revisiting the Foundations: Gradio and Tool Calling 🔄

Today wasn't really about learning something completely new.

Instead, I decided to take a step back and **revise some of the concepts I learned during the earlier part of my 100 Days of AI journey**, especially **Gradio and tool calling**.

With the agentic AI project I’m now planning, I realized that some of those “basic” concepts from the early days are actually becoming much more important again.

### 🛠️ Revisiting Tool Calling

One of the main things I revised was **how LLM tool calling actually works**.

When I first learned this, one of my biggest realizations was that an LLM doesn't directly execute a function or access a tool by itself.

The workflow is more like:

**User Request → LLM → Tool Call → Our Code Executes Tool → Tool Result → LLM → Final Response**

The LLM decides **which tool should be used and what arguments it needs**, but the actual execution is handled by our application.

I also revisited how this can be extended beyond a single tool call.

A more capable agent can:

**Call a tool → Receive the result → Think again → Call another tool → Repeat until the goal is achieved.**

That loop is one of the concepts that now feels especially relevant after learning about Agentic AI.

I also went back to the small **flight assistant** I built earlier, where I used tool calling to retrieve flight prices and SQLite to store the data instead of hardcoding everything.

Looking back at that project now, it feels much less like an isolated experiment and much more like a simple version of the agentic workflows I'm planning to build now.

### 🖥️ Revisiting Gradio

I also refreshed my understanding of **Gradio**.

Earlier in the journey, I used Gradio to turn my AI scripts into interactive applications without having to build a complete frontend from scratch.

I revised concepts such as:

🖥️ Creating simple input/output interfaces
🌐 Sharing applications with temporary public URLs
🚀 Launching interfaces directly in the browser
🔐 Adding basic authentication
🤖 Connecting Gradio interfaces to LLM APIs
💬 Streaming responses using Python's `yield`

I especially revisited how `yield` can be useful when building LLM applications.

Instead of waiting for the entire response to be generated before displaying anything, a generator can produce output gradually, which makes the interface feel much more responsive.

### 🔗 Connecting the Pieces Again

What was interesting about today's revision is that these topics no longer feel disconnected.

Earlier in the journey, I learned:

**Gradio → Build an interface**

and

**Tool Calling → Let an LLM interact with functions**

Now that I'm learning about Agentic AI, those concepts naturally start fitting together:

**Gradio → User Interface**
**LLM → Decision Maker**
**Tools → Actions**
**Loop → Continuous Reasoning and Execution**

And that is very close to the architecture I started designing yesterday for my deal-finding agent.

### 🎯 Today's Takeaway

Sometimes going back to older concepts is just as useful as learning something new.

The things I learned during the early days of this journey — especially **tool calling and Gradio** — are starting to make much more sense now that I have a larger picture of where I'm heading.

Instead of learning isolated technologies, I'm starting to see how they can work together to build a complete AI application.

So today wasn't really about adding another technology to the list.

It was about **strengthening the foundations for what comes next.** 🤖

🎯 **Day 64 complete.**
