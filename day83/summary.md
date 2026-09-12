## Day 83: Demystifying Agentic AI from First Principles ## 🤖🚀

Today was all about peeling back the layers of Agentic AI. Frame-works like LangChain or AutoGen are great for spinning up agentic systems quickly, but true mastery comes from understanding what’s happening under the hood. So, for Day 83, I skipped the high-level abstractions and built an agentic planning framework completely from scratch!

**Key Takeaways & Technical Insights**

* **Defining "Agentic" AI:** Stripped down to its core, an agentic system is simply an LLM equipped with tools operating in an iterative loop to achieve a specific goal.
* **Problem Decomposition over the "Agentic Trap":** It's easy to fall into the trap of assigning superficial human roles (e.g., "Researcher Agent", "Writer Agent") just for the sake of it. The real goal is breaking down a complex problem into smaller, logical steps executed via dedicated LLM calls.
* **Tools & Structured Outputs are Twins:** I realized that structured outputs and tool calling are deeply connected. In fact, most providers implement structured outputs under the hood as tool calls that enforce specific schema limits.
* **The Architecture of our System:**
* **Scanner Agent:** Extracts web/RSS data and formats it into structured deal objects.
* **Ensemble Agent:** Evaluates item value using a mix of RAG (chroma vector search + GPT) and a custom deep neural network (from Week 6).
* **Messaging Agent:** Generates output using Claude 3.5 Sonnet and pushes real-time notifications via Pushover.


* **Building the Planning Agent:** Today's main event was writing the central orchestrator in Cursor. To the planning agent, all complex sub-agents (RAG, neural nets, scanners) are abstracted away as standard callable tools. It doesn't need to know *how* they work—just *when* to invoke them.
* **Autonomy & State:** Beyond chat windows, real agentic value comes from background execution, persistent memory, and proactive communication.

Only 17 days left in the challenge! 🏁
