## Day 50 – Zero-Shot Price Prediction with Local LLMs

Today, I experimented with using pretrained Ollama models directly for product price prediction.

The goal was not to fine-tune them yet, but simply to test how well their existing knowledge could estimate product prices from the available product information.

I tested three relatively small local models:

### 1. Qwen3 4B Instruct

Qwen3 performed reasonably well, but still slightly worse than the vanilla neural network I trained earlier.

Results:

* **Mean error:** $78.02
* **R²:** 11.4%

The model was able to make somewhat sensible estimates, but the low R² score showed that its predictions still explained only a small portion of the actual price variation in the dataset.

### 2. Llama 3.2 3B

Llama 3.2 performed significantly worse than the other models.

Results:

* **Mean error:** $95.20
* **R²:** -85.8%

The negative R² was especially interesting because it means the model performed worse than simply predicting the average product price for every sample.

Its predictions were quite inconsistent, showing that general pretrained knowledge alone was not enough for this particular pricing task.

### 3. Gemma 3 4B

Gemma 3 produced the best results among the three models.

Results:

* **Mean error:** $75.93
* **R²:** 31.0%

This was the strongest zero-shot performance of the day. However, the predictions still contained several large outliers, which increased the overall error and showed that the model could occasionally produce unrealistic price estimates.

### Overall Results

Among the three models:

**Gemma 3 4B > Qwen3 4B Instruct > Llama 3.2 3B**

Gemma achieved the lowest error and highest R² score, while Llama 3.2 struggled considerably.

The main takeaway from today's experiment is that pretrained LLMs do contain enough general product and market knowledge to make rough price estimates, but they are still not naturally optimized for a regression task like price prediction.

Unlike a traditional ML model trained directly on the dataset, these LLMs currently have no knowledge of the specific relationships and price distribution inside my training data.

That makes today's experiment a useful baseline.

Tomorrow, I plan to fine-tune one of these models using my product training data and compare its performance against today's zero-shot results.

The interesting question now is:

**How much can fine-tuning improve an LLM that currently relies only on its pretrained knowledge?**
