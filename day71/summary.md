## Day 71 — Visualizing My ChromaDB Vector Store 📊

Today was another relatively light day in my **#100DaysOfAI** journey. I'm still recovering from the fever 🤒, so I continued working on the RAG pipeline I started on Day 69.

I had left my **800K product dataset** running for vectorization, but after around **5 hours**, it still showed **22 hours remaining**. 😂

So I switched to my **lite dataset of 20K products**, which finished much faster and allowed me to continue experimenting.

Today, instead of building a new feature, I focused on **visualizing the embeddings stored in ChromaDB**.

My embeddings have **384 dimensions**, which obviously isn't something we can visualize directly. So I used **t-SNE** to reduce the dimensionality:

🔹 **384D → 2D**
🔹 **384D → 3D**

For the visualization, I limited the data to **10,000 points** so the plots wouldn't become overly crowded.

I also grouped the products into 8 categories and assigned different colors to each category, making it easier to see how different types of products are distributed within the vector space.

Finally, I used **Plotly** to create interactive scatter plots where I could hover over individual points and see their category and product description.

### 💡 Today's Takeaway

Today gave me a more visual understanding of something that normally feels very abstract—**embeddings and vector spaces**.

Instead of just storing thousands of numerical vectors inside ChromaDB, I could actually see how the products are distributed and potentially identify clusters and patterns.

And today's biggest lesson:

> **Sometimes 20K useful data points are better than waiting 27 hours for 800K.** 😂

🎯 **Day 71 complete.** 🚀
