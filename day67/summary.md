# Day 67 – Revisiting RAG & Advanced RAG Techniques 🔄🧠

Today was a **revision day** in my #100DaysOfAI journey. Instead of learning a completely new concept, I decided to go back to one of the most important topics I've worked with so far: **Retrieval-Augmented Generation (RAG)**.

After working on different AI projects over the past few weeks, I felt it was a good time to revisit the fundamentals and make sure I still had a strong understanding of *why* each component of a RAG system exists.

## 📚 Revisiting the RAG Fundamentals

I went through the complete RAG pipeline again, starting from the very beginning:

### 1. Document Ingestion

The first step is collecting and loading information from different sources such as documents, PDFs, websites, or databases.

The goal is to convert these sources into information that can be processed by the retrieval pipeline.

### 2. Chunking

Large documents can't simply be passed to an LLM as they are, so they need to be broken down into smaller pieces called **chunks**.

I revisited why chunk size, overlap, and the way documents are split can have a significant impact on retrieval quality.

### 3. Embeddings

Each chunk is converted into a numerical representation called an **embedding**.

These embeddings capture the semantic meaning of the text, allowing the system to find information that is conceptually similar to a user's query rather than relying only on exact keyword matches.

### 4. Vector Databases

The generated embeddings are stored in a vector database, which makes it possible to efficiently search through a large collection of information.

This is where the system can retrieve the chunks that are most relevant to a particular query.

### 5. Retrieval

When a user asks a question, the query is converted into an embedding and compared against the stored vectors.

The most relevant chunks are then retrieved and passed to the LLM as additional context.

### 6. Generation

Finally, the LLM uses the retrieved information along with the user's question to generate a response.

The overall idea is simple:

**Retrieve relevant knowledge → provide it as context → generate a grounded answer.**

## 🔬 Revisiting Advanced RAG

I also went beyond the basic pipeline and revised several **Advanced RAG techniques** that can improve retrieval quality.

Some of the techniques I revisited were:

🔹 **Better chunking strategies** – improving how documents are split so that retrieved chunks contain more useful context.

🔹 **Query transformation** – rewriting, expanding, or decomposing a user's query to make retrieval more effective.

🔹 **Hybrid search** – combining semantic/vector search with traditional keyword-based search.

🔹 **Re-ranking** – retrieving a larger set of potentially relevant documents and then using a more sophisticated model to rank the most useful ones.

🔹 **Filtering** – removing irrelevant or low-quality results before they reach the LLM.

🔹 **Multi-step retrieval** – performing retrieval iteratively when answering more complex questions requires information from multiple sources.

## 💡 Why Today's Revision Was Important

One thing that stood out to me today is that **RAG itself is relatively simple to understand, but building a good RAG system is much more complicated.**

A basic pipeline might work perfectly in a small demo, but real-world applications can struggle with:

* Poorly chosen chunks
* Irrelevant retrievals
* Ambiguous queries
* Too much retrieved context
* Missing information
* Incorrect ranking of results

That's where advanced retrieval techniques become important.

Instead of immediately blaming the LLM when a RAG system produces a poor answer, it's important to ask:

**Did we retrieve the right information in the first place?**

## 🎯 Today's Takeaway

Today's biggest takeaway was that **revision is just as important as learning something new**.

With AI concepts building on top of each other so quickly, it's easy to keep moving forward without fully reinforcing the foundations. Going back to RAG today helped me connect the basic pipeline with the more advanced techniques I've encountered throughout this journey.

No new model.
No new project.
No fancy experiment.

Just a day of **revising, connecting concepts, and strengthening the foundation.** 💪📚

And sometimes, that's exactly what you need before moving on to the next thing. 🚀

**Day 67 complete.** ✅
