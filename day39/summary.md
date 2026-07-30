## Day 39 Summary — From LLM Chunking to Vector Visualization

Today, I completed an end-to-end experiment with **LLM-based semantic chunking** for a RAG knowledge base.

Instead of using a standard LangChain text splitter, I used `qwen3:4-instruct` with Pydantic structured outputs to divide 76 documents into meaningful chunks containing a headline, summary, original text and source metadata.

The process took around **188 minutes** and involved timeouts, checkpointing, retries and a lot of patience 😭 Thankfully, all 76 documents were eventually processed successfully, producing **625 structured chunks**.

I then:

* Generated embeddings using `mixedbread-ai/mxbai-embed-large-v1`
* Stored the vectors and metadata in ChromaDB
* Used t-SNE to reduce the embeddings into 2D and 3D for visualization

From the 2D visualization, the embeddings appear to form several meaningful regions. The green points create a fairly distinct cluster, while the red and blue groups show both separation and overlap, which may indicate related topics sharing semantic information. The smaller orange region appears to connect or sit between larger groups.

Overall, the visualization looks healthy enough to continue. However, t-SNE is mainly a qualitative check—it shows that the embeddings contain structure, but retrieval evaluation will determine whether the chunks are actually useful.

The next step is to test the retriever using real questions and measure metrics such as **MRR, NDCG and keyword coverage**.
