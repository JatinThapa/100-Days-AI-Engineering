## Day 40 Summary — Query Rewriting, Reranking, and Retrieval Limitations

Today, I worked on improving the retrieval stage of my RAG pipeline using two advanced techniques: **query rewriting** and **context reranking**.

Before searching the vector database, the user’s original question was rewritten by an LLM to make it clearer and more specific. After retrieving the initial chunks, I then reranked them so that the most relevant context could be moved closer to the top before answer generation.

However, I also discovered that these techniques do not always improve retrieval.

For the question:

> “Who attended the University of Manchester?”

the correct answer was Jessica Liu, but her relevant chunk did not appear among the top retrieved results. The chunk contained the Manchester information, but it also included performance history, compensation, skills, feedback, and professional development. This likely diluted the importance of the education detail inside the embedding.

I also noticed that query rewriting can sometimes work against the retriever. The LLM rewrote the question as:

> “Who in the InsureLLM company attended the University of Manchester?”

Although this version sounds clearer to a human, it produces a different query embedding. Adding unnecessary words such as the company name can shift the vector away from the language used in the relevant chunk and reduce retrieval quality.

For now, I decided to continue with the current pipeline instead of rebuilding everything because of one difficult query. However, I may later improve the knowledge base using a hybrid chunking strategy or manually divide overly broad chunks that hide important facts.

The next step is to run retrieval and answer evaluations using metrics such as MRR, NDCG, keyword coverage, and answer-quality scores. Based on those results, I can decide whether the full pipeline needs another refactor.

Today’s main takeaway was that advanced RAG techniques are not automatic improvements. Query rewriting, semantic chunking, and reranking all need proper evaluation because each one can sometimes help retrieval—and sometimes make it worse.
