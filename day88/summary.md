# Day 88 — Seeing the Bigger Picture Behind the Agentic System 🤖🔗

Today’s lesson was less about writing new code and more about **understanding the complexity of the system we had built and seeing how all the pieces were working together**.

After running the complete agentic deal-finding workflow, the instructor broke down what was actually happening behind the scenes.

The entire process involved roughly **34 model calls** in total:

🧠 **29 LLM calls**
🧮 **5 neural network calls**

And these calls were spread across several different models and components, including the **fine-tuned Specialist model**, the **embedding model (`all-MiniLM-L6-v2`)**, an **open-source preprocessing model**, the Ensemble Agent's different pricing models, and the planning/agent loop itself.

What initially looks like a simple:

**“Find a deal → Check its value → Notify me”**

is actually a fairly involved chain of models and tools cooperating to accomplish one goal.

### 🔄 The Bigger Agentic Workflow

The planning agent acts as the coordinator while the specialized components handle individual tasks.

The overall process involves:

**Planning → Deal Scanning → Structured Outputs → Value Estimation → Multiple Pricing Models → Decision → Notification**

The important point is that each component doesn't need to know the internal implementation of the others. They simply expose capabilities that the planner can invoke when necessary.

This showed me how an agentic system can scale from a single LLM call into a workflow where **multiple models, tools, and inference steps cooperate dynamically**.

### 🧩 Complexity Doesn't Have to Mean Mystery

One of the most interesting parts of today's lesson was the realization that a system with **six or seven different models and dozens of calls** can still be built from relatively understandable building blocks.

There's no single magical “agent” doing everything.

It's essentially:

**Models + Tools + State + Loops + Good Interfaces**

When those pieces are connected properly, they can produce surprisingly complex behavior.

The instructor also emphasized that the system can be simplified when necessary. If all the moving parts are too much, individual components such as the ensemble can be reduced to a single model.

That was a useful engineering lesson: **complexity should serve the problem, not exist just because we can build it.**

### 🚀 One Final Step

The current system is already capable of finding deals, estimating their value, and sending notifications, but the journey isn't quite over yet.

The next and final step is to make the agentic workflow more complete by adding things such as **memory and persistent state**.

That would move the system beyond simply completing one workflow and toward an agent that can **remember what happened, maintain context, and operate more autonomously over time**.

### 💡 Today's Takeaway

Today's biggest takeaway was getting a sense of the **architecture behind the architecture**.

What I built isn't just one model making one prediction. It's a collection of specialized components working together across many model calls to achieve a single goal.

And seeing that a system involving **34 model calls** can still be understandable when broken into smaller pieces made Agentic AI feel much less intimidating.

There is now **only one day left** in the challenge. 🏁

The final step will be bringing everything together with memory and completing the Agentic AI workflow. 🤖🔗
