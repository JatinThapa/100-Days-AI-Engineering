# Day 69 – Designing the Price Estimation Ensemble & Building an 800K-Item RAG Knowledge Base 🚀🧠

Today was a pretty exciting day because I moved beyond building individual components and started thinking about **how all of them will work together as a complete price estimation system**.

The main idea is to build an **Ensemble Agent** that doesn't rely on a single model to predict the price of a product. Instead, it will collect estimates from multiple specialized approaches and use them together to arrive at a more reliable final price.

## 🤖 Planning the Price Estimation Agent

At the moment, I already have my **Specialist Agent**, which connects to my fine-tuned pricing model running remotely on Modal.

That model was trained on my own proprietary product dataset, so it represents one completely independent way of estimating a price.

But rather than trusting a single model, I want the system to get **three different price estimates**.

### 1. 🔬 Specialist Agent

This is the component I built earlier.

It sends the product description to my **fine-tuned Llama pricing model running on Modal** and gets back a predicted price.

This gives the ensemble a prediction from a model specifically trained for this pricing task.

### 2. 🌐 Frontier Agent

The second approach will be a **frontier model-based agent**.

Instead of relying on my fine-tuned model, this agent will use a more capable general-purpose model and provide it with **relevant information about similar products** before asking it to estimate the price.

This is where the RAG system I've been revisiting over the last couple of days becomes really important.

The idea is essentially:

**Product → Retrieve similar products → Give them to frontier model → Estimate price**

I'm still figuring out how to make this part work within my budget, but I'm definitely going to experiment with it.

### 3. 🧠 Neural Network Agent

The third component will be a **neural-network-based pricing model**.

I'll be modifying a baseline multi-layer neural network so that it can independently learn the relationship between product information and price and return its own estimate.

This gives the system a completely different modelling approach from both the fine-tuned LLM and the frontier model.

## 🏆 The Ensemble Agent

Finally, all three agents will report their predictions to the **Ensemble Agent**.

The rough architecture I'm imagining is:

**Specialist Agent** → 💰 Price
**Frontier Agent** → 💰 Price
**Neural Network Agent** → 💰 Price
⬇️
**Ensemble Agent**
⬇️
🎯 **Final Price Estimate**

The ensemble will then determine what it considers to be the best overall estimate from the three predictions.

The interesting part here is that each model approaches the problem differently, so hopefully their combination will be more robust than relying on just one model.

---

# 📚 Starting the RAG Pipeline

Alongside planning the agents, I also started implementing the **RAG system** today.

And this is where things got a little ridiculous. 😂

Remember the **800,000-item training dataset** I prepared earlier?

Yep.

**That's going to be my RAG knowledge base.** 😭

Rather than using a relatively small collection of documents, I'm essentially turning my entire product training dataset into a searchable knowledge base containing **800K product records**.

I loaded the dataset from Hugging Face and started setting up the vector database using **ChromaDB**:

```python
client = chromadb.PersistentClient(path=DB)
```

I then created a `products` collection to store the information.

## 🔢 Generating Embeddings

For the embeddings, I'm currently experimenting with the **all-mini-v6-l2** embedding model from Hugging Face.

The plan is to convert each product summary into a vector representation and store those vectors inside ChromaDB.

I processed the dataset in batches of 1,000 items at a time:

```python
for i in tqdm(range(0, len(train), 1000)):
    documents = [item.summary for item in train[i:i+1000]]
    vectors = encoder.encode(documents).astype(float).tolist()

    metadatas = [
        {"category": item.category, "price": item.price}
        for item in train[i:i+1000]
    ]

    collection.add(
        ids=ids,
        documents=documents,
        embeddings=vectors,
        metadatas=metadatas
    )
```

Each product gets:

🔹 Its original summary
🔹 An embedding vector
🔹 Its category
🔹 Its actual price
🔹 A unique document ID

This should eventually allow me to query the database for products that are **semantically similar** to a new product.

For example, when the system receives a new microphone, instead of asking a model to guess blindly, the RAG system could retrieve similar microphones from the 800K-product knowledge base and provide those examples as context.

That could give the frontier agent some very useful real-world reference points.

## 🔥 And Then Came the GPU

Of course, there's one tiny problem.

Encoding **800,000 products** isn't exactly instant.

My current estimate is that the embedding process could take roughly **2–3 hours of GPU computation**. So for now, I'm basically letting my GPU suffer while it turns 800K products into vectors. 😂🔥

But once the embeddings are generated and stored, I'll finally have a massive searchable product knowledge base ready for the next stage.

## 🚀 What's Next?

Tomorrow I'll start looking at the generated vectors and the resulting ChromaDB collection.

I'll also investigate how well the retrieval actually works and whether it makes sense to introduce **LLM-based chunking or restructuring** for the product information.

At some point, the RAG system should become the bridge between the huge product dataset and the agents that need that information.

### 💡 Today's Takeaway

Today's biggest takeaway was that building an AI system is becoming less about **one model doing everything** and more about **multiple specialized components working together**.

My architecture is starting to look something like:

**RAG Knowledge Base**
⬇️
**Specialist Agent + Frontier Agent + Neural Network Agent**
⬇️
**Ensemble Agent**
⬇️
🎯 **Final Price Estimate**

It's still very much a work in progress, but today I finally started turning the individual experiments from the past few weeks into the beginnings of an actual **multi-agent price estimation system**.

And apparently, my RAG knowledge base has decided that **800,000 products wasn't enough of a challenge.** 😂

**Day 69 complete.** ✅
