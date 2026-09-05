# Day 76 — Turning My Price Predictor into an Agentic System 🤖💰

Today was a pretty exciting milestone in my **#100DaysOfAI** journey. After spending the last few days building and testing the individual components of my price estimation system, I finally started turning the whole thing into a proper **agentic architecture**.

The goal is no longer just to have three different models making predictions. I want to have multiple specialized agents, each responsible for a particular task, working together to produce a final price estimate.

### 🎨 Setting Up Agent Logging

I started by setting up a centralized logger so I could clearly track what each agent is doing during execution.

```python
root = logging.getLogger()
root.setLevel(logging.INFO)
```

I also structured the logs so that the different agents can be distinguished more easily, including through different colors. This might seem like a small thing, but once multiple agents start calling each other, being able to follow the execution flow becomes extremely useful.

### 🌐 Agentizing the Frontier Model

The first component I converted into an agent was my **Frontier Agent**.

This agent combines:

**Product → Embedding → ChromaDB → 5 Similar Products → RAG Context → MiniMax M3**

I tested it with a HyperX Quadcast microphone, and the logs showed the complete flow:

* Initialize the Frontier Agent
* Load the embedding model
* Search ChromaDB for similar products
* Retrieve 5 relevant products
* Pass those products and their prices to MiniMax M3
* Return the final prediction

The model predicted **$149.99** for the microphone.

This was useful because I could now see the entire RAG workflow happening through a clearly defined agent rather than just having a collection of independent functions.

### 🧠 Building the Neural Network Agent

I then did something similar with my **Deep Neural Network**.

The Neural Network Agent is responsible for loading the trained weights and making a prediction whenever it is called.

For one of my test products, it predicted:

💰 **$162.39**

The important part here wasn't just the prediction itself—it was getting another component of my pricing architecture working as an independent agent.

### 🔬 Bringing Back the Specialist Agent

I already had my **Specialist Agent** from Day 68, which connects to my remotely deployed fine-tuned pricing model.

So at this point, I had three separate pricing specialists:

🔬 **Specialist Agent** → Fine-tuned proprietary model
🌐 **Frontier Agent** → General LLM + RAG
🧠 **Neural Network Agent** → Traditional deep learning model

And now came the interesting part: putting all three behind a single **Ensemble Agent**.

### 🧹 Adding a Preprocessing Agent

Before combining everything, I added one more important step.

I used **Llama 3.2 3B through Ollama** as a preprocessing model to rewrite the incoming product description into a cleaner and more consistent format.

The idea is that my fine-tuned model was trained on a particular style of product descriptions, so normalizing new inputs before sending them through the pricing pipeline should hopefully make the predictions more consistent.

Since I'm running this model locally and for free, the rewriting isn't exactly world-class 😂, but it's good enough for now.

### 🏆 The Ensemble Agent

Finally, I created the Ensemble Agent:

```python
from agents.ensemble_agent import EnsembleAgent

agent = EnsembleAgent(collection)
```

Then I tested the entire pipeline with a **Shure MV7+ professional microphone**, whose actual price was **$290**.

The logs showed the complete agentic workflow:

**Input Product**
↓
**Preprocessing with Llama 3.2 3B**
↓
**Specialist Agent** → $299.00
**Frontier Agent + RAG** → $249.00
**Neural Network Agent** → $361.76
↓
**Ensemble Agent** → **$265.28**

The final prediction was **$265.28**, compared to the actual price of **$290**.

That's a difference of roughly **$25**, which honestly isn't too bad considering that essentially the entire pipeline is being built and run using free or very low-cost resources. 😂

### 💡 Today's Takeaway

Today felt like an important transition in the project.

Until now, I had mostly been building **individual models and individual components**.

Today, I started connecting those components into a system where **different agents have different responsibilities and work together toward one goal**.

The architecture is now starting to look much closer to what I originally envisioned:

**User → Preprocessing Agent → Specialist Agents → Ensemble Agent → Final Price**

And this is only the beginning.

From tomorrow, I'm moving on to another major component: the **Scanner Agent**, which will be responsible for scanning the internet for potential deals and feeding useful products into the system.

The price predictor can estimate whether something is a good deal.

Now I want to build something that can **actually find those deals.** 👀🔎

🎯 **Day 76 complete.**
