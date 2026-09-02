# Day 73 — My RAG Pipeline Finally Came Together 🤖📚

Today was finally a **proper building day** after several days of revision and lighter work. I managed to put together a working **RAG pipeline** for my price estimation project using the vectorized knowledge base I created earlier.

The first part was building the retrieval step. The idea was simple: given a product, find the **most similar products** from my ChromaDB vector store and use their prices as additional context for the LLM.

I created a function that encodes the product summary and retrieves the **top 5 similar items**:

```python
def vector(item):
    return encoder.encode(item.summary)

def find_similars(item):
    vec = vector(item)
    results = collection.query(
        query_embeddings=vec.astype(float).tolist(),
        n_results=5
    )
    documents = results['documents'][0][:]
    prices = [m['price'] for m in results['metadatas'][0][:]]
    return documents, prices
```

This was an important step because now a general-purpose LLM doesn't have to guess a price from its own knowledge alone. Instead, I can provide it with **real examples of similar products and their actual prices**.

I then created another function to turn those retrieved products into a clean, structured context message:

```python
def make_context(similars, prices):
    message = "For context, here are some other items that might be similar to the item you need to estimate.\n\n"

    for similar, price in zip(similars, prices):
        message += f"Potentially related product:\n{similar}\nPrice is ${price:.2f}\n\n"

    return message
```

### 🧪 Putting the RAG System to the Test

Once the retrieval and context generation were ready, it was time to see whether this actually worked.

For the first test, I used **MiniMax M3 through OpenRouter**, mainly because it was a free model with enough context capacity for the retrieved examples.

The test product was a **distortion pedal priced at $219**.

After receiving the additional context from RAG, the model predicted:

💰 **Predicted price: $199**

That's only a **$20 difference**, which honestly wasn't bad at all. 😂

But testing a single example isn't enough, so I ran the complete RAG pipeline against **200 unseen test products**.

The inference took around **5 minutes**, which wasn't too surprising considering I was using a free model. But the final numbers were what really caught my attention:

📉 **Mean Error: $43.38**
📈 **R² Score: 73.3%**

And this was honestly a huge confidence boost.

The results came surprisingly close to the performance of my **fine-tuned pricing model**, which had been trained on a much larger dataset.

What's especially interesting is that this model itself wasn't specifically fine-tuned for my pricing task. Instead, I simply gave it **relevant information at inference time through retrieval**.

### 💡 Today's Takeaway

Today really showed me why RAG can be so powerful.

Instead of trying to teach a model everything through fine-tuning, I can retrieve the **right information at the right time** and let a general-purpose model reason over it.

So the pipeline is now essentially:

**Product → Embedding → Similar Products → Prices → Context → LLM → Estimated Price** 🔗

After being sick and having a few slower days, seeing a **73.3% R²** from this first proper RAG implementation definitely made me happy. 😂

And now I'm even more excited for tomorrow.

The next step is to build the **Ensemble Agent**, where I'll combine predictions from multiple approaches and hopefully find an even more reliable **sweet spot for the final price estimate**. 🤖🤝💰

🎯 **Day 73 complete.**
