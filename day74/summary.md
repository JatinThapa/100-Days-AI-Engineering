# Day 74 — Building the Ensemble Pricing Model 🤖💰

Today was a relatively light day in terms of coding, but it was an important step for my **price estimation project**.

After building and testing the individual pricing approaches, I finally started putting together the **Ensemble Model**—an approach that combines predictions from multiple models instead of relying on just one.

The idea is pretty straightforward: each model has different strengths, so rather than asking one model to do everything, I'll let all three contribute to the final prediction.

The current weighting is:

🔬 **80% → Proprietary Fine-Tuned Model**
🌐 **10% → OpenRouter LLM + RAG**
🧠 **10% → Deep Neural Network**

So the final prediction is essentially a **weighted average** of the three estimates:

**Final Price = 0.8 × Proprietary Model + 0.1 × RAG Model + 0.1 × Neural Network**

The proprietary model gets the majority of the weight because it has been specifically fine-tuned for this pricing task, while the other two models act as additional perspectives that can potentially correct some of its mistakes.

### 🧪 And the Results Were Surprisingly Good

I ran the ensemble against my **200 test products**, and the results were the best I've seen so far in terms of prediction error:

📉 **Mean Error: $40.71**

That's an improvement over the **$43.38 error** I got from my RAG-based approach.

Interestingly, however, the **R² score dropped to 65.8%**.

At first, that might seem contradictory—how can the error improve while R² gets worse?

The reason is that **Mean Error and R² measure different things**.

Mean Error looks at how far the predictions are from the actual prices on average, while **R² measures how well the model explains the variation in the target values**.

So it's possible for the ensemble to make predictions that are **closer to the actual prices overall**, while being slightly less effective at capturing the broader variation between cheaper and more expensive products.

For example, an ensemble that produces more conservative predictions closer to the average price can reduce absolute error, but may struggle to predict the extreme high- or low-priced items accurately. That can improve the average error while hurting R².

### 💡 Today's Takeaway

Today showed me something important about ensemble models:

**The best model isn't always the one with the highest score on every metric.**

Different evaluation metrics tell us different things, so looking at just one number can give a misleading picture of performance.

For now, the ensemble has given me my **lowest prediction error yet—$40.71**, which is a pretty encouraging result. 🚀

And the best part is that this was only the first version of the ensemble. There is still plenty of room to experiment with the weights, model combinations, and potentially even more intelligent ways of combining the predictions.

After spending so much time building the individual components, it's satisfying to finally see them **working together as one system.** 🧠🤝

🎯 **Day 74 complete.**
