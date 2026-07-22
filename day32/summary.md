# Day 32 Summary — Embeddings, ChromaDB and Vector Visualisation

Day 32 was a gritty but important step forward in my RAG journey. Yesterday, I understood the basic retrieval flow; today, I converted an actual knowledge base into numerical vectors and stored them inside a vector database.

I started by learning about **LangChain**, an open-source framework introduced in 2022. It provides a common abstraction layer for working with different LLMs, embedding models, document sources and application components. This can speed up the development of applications such as AI assistants, RAG systems and summarisation tools.

However, I also learned that LangChain comes with trade-offs. As modern LLM APIs have become simpler and more consistent—especially OpenAI-compatible endpoints—the need for a large unifying framework has reduced in some cases. LangChain has also grown into a substantial framework, so it can feel heavier than alternatives such as LiteLLM, and some older examples may rely on legacy APIs.

For the practical work, I built the first major stages of a RAG ingestion pipeline:

**Documents → Load → Split into chunks → Generate embeddings → Store in ChromaDB**

Using LangChain’s `DirectoryLoader` and `TextLoader`, I loaded **76 Markdown documents** from the fictional Insurellm knowledge base. Together, they contained approximately:

* **304,434 characters**
* **63,555 tokens**

I then used `RecursiveCharacterTextSplitter` with a chunk size of **1,000 characters** and an overlap of **200 characters**. This divided the documents into **413 chunks** while preserving useful context between neighbouring chunks.

Next, I experimented with several open-source Hugging Face embedding models:

* `all-MiniLM-L6-v2`
* `BAAI/bge-small-en-v1.5`
* `intfloat/e5-base-v2`
* `mixedbread-ai/mxbai-embed-large-v1`

The final run used `mxbai-embed-large-v1`, which converted all 413 chunks into **1,024-dimensional vectors**. These vectors were stored locally in **ChromaDB**, giving me a persistent vector store that can later be searched using semantic similarity.

Finally, I extracted the stored embeddings and used **t-SNE** to reduce them from 1,024 dimensions into both **2D and 3D representations**. With Plotly, I visualised how chunks from different document categories—products, employees, contracts and company information—were positioned in the embedding space.

The visualisation does not show the true high-dimensional space perfectly, but it helped me understand that semantically related text can form nearby groups even when the wording is different.

Today’s biggest takeaway was that a vector database does not store “meaning” directly. An embedding model converts text into coordinates representing semantic relationships, and ChromaDB stores those coordinates along with the original text and metadata. The next step is to search this vector store with a user query and retrieve the most relevant chunks—the actual retrieval part of RAG.
