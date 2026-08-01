# #100DaysOfAI – Day 41 🚀

Today, I tested the Gradio interface for my advanced RAG pipeline and finally saw the improvements come together.

Compared to my earlier RAG setup, the new pipeline produced answers that were noticeably more relevant, detailed, and accurate.

The pipeline now includes:

* Query rewriting
* Retrieval using Hugging Face embeddings
* LLM-based reranking
* Context-aware answer generation
* A Gradio interface for interaction

One interesting limitation appeared during follow-up questions.

For example:

> **“What is Jessica Lui’s educational background?”**

The system correctly answered that she studied at Manchester University.

But when I followed up with:

> **“What’s her salary?”**

The pipeline failed to understand that **“her” referred to Jessica Lui**, so it could not retrieve the correct information.

This showed me that conversation history should not only be passed to the final answering LLM. It should also be considered during query rewriting and retrieval.

I also started evaluating the system using 150 test questions, but the process quickly became impractical.

Qwen was extremely slow for reranking and evaluation, while OpenRouter repeatedly hit rate limits. After waiting around 1,000 seconds for only 10% progress, I decided to pause the evaluation instead of spending several more hours watching a progress bar crawl forward 🐌😭

For now, I’m wrapping up this phase of learning with a much stronger understanding of:

* Advanced chunking
* Embeddings and vector search
* Query rewriting
* Reranking
* Retrieval evaluation
* Conversational RAG limitations

The pipeline is not perfect yet, but it is clearly better than my earlier version.

My next goal is to apply these concepts inside **NomadNest** and build a RAG system around a real project and use case.

The evaluation scores can wait for another day 😭

#RAG #GenerativeAI #LLM #HuggingFace #ChromaDB #Gradio #AIEngineering #100DaysOfAI
