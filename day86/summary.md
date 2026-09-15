# Day 86 — Connecting the Agents into a Fully Autonomous Deal Finder 🤖🔗

Today was one of the most exciting days of my **#100DaysOfAI** journey because I finally saw the individual agents I had been building start working together as a **single autonomous system**.

The main focus today was understanding how an LLM-based **planning agent** can coordinate other specialized agents through tool calling and an iterative execution loop.

### 🧠 From Mock Tools to Real Agents

Previously, I built a planning agent using simple mock functions such as:

🔎 `scan_internet_for_deals`
💰 `estimate_true_value`
📩 `notify_user_of_deal`

Today, the idea was to replace those fake functions with the **actual agents** I had already developed.

The important realization was that the planning LLM doesn't really care what happens *inside* a tool.

From its perspective, it simply has a set of tools available and needs to decide:

**Which tool should I call next?**

The implementation of that tool can then call another agent, another model, a database, or anything else we want.

### 🔄 The Agentic Loop

The core system works as an iterative loop:

**Goal → LLM decides → Tool Call → Execute → Return Result → LLM decides again**

The loop continues until the planner decides there are **no more tools to call**, at which point it returns the final response.

This was an important distinction for me: the planning agent isn't following a hard-coded sequence like:

> Scanner → Ensemble → Messenger

Instead, it has the tools available and **autonomously decides what actions are necessary to complete the goal**.

### 🧩 Replacing the Mock Tools

I then connected the real agents behind those tool interfaces.

The architecture now looks roughly like:

**Planning Agent**
↓
🔎 **Scanner Agent** → Fetches deals from RSS feeds and uses structured outputs to select promising ones
↓
💰 **Ensemble Agent** → Evaluates the true value using my pricing models
↓
📩 **Messaging Agent** → Sends the notification when a deal qualifies

Inside the Ensemble Agent, the existing pricing agents are still doing their own work, including the **Specialist, Frontier/RAG, and Neural Network agents**.

So I've now got multiple layers of agents rather than just a single LLM call.

### 🔧 A Small but Important Engineering Improvement

I also improved the tool execution logic.

Instead of relying on Python's `globals()` to dynamically find functions, I moved toward an explicit **mapping between tool names and the functions they should execute**.

That makes the system cleaner, safer, and easier to extend as the number of tools grows.

### 🚀 Watching the Whole System Run

The most satisfying part was actually running the complete framework.

The Planning Agent initialized the Scanner, Ensemble, and Messaging agents, and I could see the different components operating through the logs.

The planner first called the **Scanner Agent**, which collected around **30 deals** from the RSS feeds and used structured outputs to reduce them to the best five.

It then passed those results back to the planner, which decided that the next step was to evaluate their true values.

The Ensemble Agent kicked in and ran its preprocessing and multiple pricing models to estimate the value of the products.

Finally, the planner determined that a notification was necessary, called the **Messaging Agent**, and the deal alert was actually pushed to my phone. 📱🔥

That moment was probably the highlight of today's session.

What started as a bunch of individual components had now become a complete workflow:

**Find deals → Evaluate value → Identify the opportunity → Notify the user**

And the really cool part?

The planning agent was making those tool calls **autonomously**.

### 💡 Today's Takeaway

Today made the concept of **agentic AI** much more concrete for me.

The individual models aren't the most interesting part anymore. The real power comes from having an LLM **orchestrate tools and specialized agents dynamically** to accomplish a larger goal.

What started as:

**“I built a Scanner Agent.”**

then became:

**“I built an Ensemble Agent.”**

and now:

**“I have a planning agent that can make them work together.”** 🤖🔗

Seeing an actual deal notification reach my phone at the end of the workflow was a pretty satisfying proof that the whole architecture is starting to come together.

🎯 **Day 86 complete.**
