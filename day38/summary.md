## Day 38 Summary - LLM-Powered Document Chunking with Structured Outputs

Today, I experimented with **LLM-based document chunking** using `qwen3:4-instruct` instead of LangChain’s traditional text splitters.

I used Pydantic structured outputs to make every chunk contain a headline, summary, original text, and source metadata. I then loaded all Markdown documents from the knowledge base, created a detailed chunking prompt, and processed each document through the LLM.

The results from the first test document were surprisingly good and felt more meaningful than regular fixed-size chunking. I have now started processing all 76 documents, although local LLM inference is taking a very long time.

Tomorrow, I plan to finish generating the chunks, store them in ChromaDB, and visualize the embeddings using t-SNE.
