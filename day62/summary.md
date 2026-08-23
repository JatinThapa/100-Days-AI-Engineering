# 100 Days of AI – Day 62 🚀

## From LLMs to Agentic AI: Designing My First Agentic System 🤖

Today marked the beginning of a new phase in my AI journey.

After spending the last several weeks working through **RAG, machine learning, LLM evaluation, quantization, LoRA, QLoRA and fine-tuning**, I finally started exploring **Agentic AI** and thinking about how I could bring everything I've learned so far into one system.

I started by learning about three different ways Agentic AI has been defined over time.

### 1️⃣ Sam Altman's Definition

One of the simpler definitions describes agentic AI as:

> **“AI systems that can do work for you independently.”**

The key idea here is **independence**.

Instead of an AI simply answering a question, an agent should be capable of taking actions on our behalf and getting something done.

### 2️⃣ The Early 2025 Definition

A broader definition that became common in the early 2025 discussions around agents was:

> **“An AI system where an LLM controls the workflow.”**

This shifted the focus from simply generating text to using the LLM as the **decision-making component** that determines what should happen next.

### 3️⃣ The More Recent Definition

The definition that really stood out to me was:

> **“Agentic AI is where an agent runs tools in a loop to achieve a goal.”**

This captures what I currently find most interesting about agents.

Instead of:

**Input → LLM → Output**

we start thinking more like:

**Goal → Think → Choose Tool → Observe Result → Think Again → Choose Another Tool → … → Goal Achieved**

The model isn't just generating an answer. It is **iteratively deciding what action to take next**.

---

## 🏗️ Designing My Own Agentic AI System

After understanding the basic idea, I started planning an architecture that combines many of the things I've learned throughout this 100-day journey.

The idea is a **deal-finding agent** that continuously looks for interesting product deals, estimates whether the price is actually good, and notifies the user when it finds a bargain.

The rough architecture looks like this:

### 🖥️ UI

For the user interface, I want to use **Gradio**, mainly because it's something I've already worked with during my earlier AI projects.

### 🧠 Agentic Framework

This would act as the foundation of the system, handling things like **agent coordination, memory and logging**.

### 🧭 Planning Agent

The planning agent would coordinate the overall workflow and decide what needs to happen next.

### 🔎 Scanner Agent

This agent would scan **RSS feeds and deal sources** to identify potentially interesting products and offers.

### 💰 Ensemble Agent

Instead of relying on a single prediction model, this component would use **multiple models** to estimate what a product is actually worth and determine whether a deal is genuinely attractive.

### 📱 Messaging Agent

Once a bargain is identified, this agent would be responsible for **notifying the user** through push notifications or another messaging channel.

The overall idea is something like:

**RSS Feeds → Scanner → Price Estimation → Deal Evaluation → User Notification**

And with agents coordinating the individual steps, the system could continuously work toward the goal without requiring the user to manually trigger every action.

---

## ☁️ Learning About Modal

While thinking about how to deploy this system, I also discovered **Modal**, a serverless cloud platform designed for running compute-heavy workloads.

What caught my attention is that it seems particularly well suited for AI applications because it can handle things like:

⚡ **On-demand GPU access**
📉 **Scale-to-zero when idle**
🐍 **Python-native infrastructure configuration**
🌐 **Web endpoints and scheduled jobs**
🧠 **GPU-backed inference and batch workloads**

Instead of managing servers or setting up complicated infrastructure manually, much of the deployment can be defined directly in Python.

The **scale-to-zero** capability especially caught my attention for an agentic project like this.

A deal-scanning agent doesn't necessarily need to run continuously on an expensive GPU. It could wake up on a schedule, perform its work, send notifications when necessary, and then shut itself back down.

That makes Modal an interesting option for the deployment side of this project.

### 🎯 Today's Takeaway

The biggest thing I learned today is that **Agentic AI is less about making an LLM smarter and more about giving it the ability to reason, use tools, make decisions and continue working toward a goal.**

And for the first time in this journey, I'm not just learning individual AI concepts.

I'm starting to think about **how all of them can fit together into one real system.**

From RAG and LLMs to ML models, fine-tuning, agents, tools, memory and deployment — the next part of the journey is going to be about putting those pieces together.

🎯 **Day 62 complete.**
