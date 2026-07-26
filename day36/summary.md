# Day 36 of 100 Days of AI — Evaluating My RAG System

Today I built a Gradio dashboard to evaluate both the retrieval and answer quality of my RAG system.

For retrieval evaluation, I calculated:

* MRR
* nDCG
* Keyword coverage

For answer evaluation, I used `qwen3:4b-instruct` as an LLM judge with structured Pydantic outputs. It compared the generated answer with the reference answer and scored it on:

* Accuracy
* Completeness
* Relevance

I tested two retrieval strategies using the `mixedbread-ai/mxbai-embed-large-v1` embedding model.

### Strategy 1

* Chunk size: 500
* Top 100 chunks retrieved
* MRR: **0.8111**
* nDCG: **0.8120**
* Keyword coverage: **94.1%**
* Accuracy: **3.66/5**
* Completeness: **3.58/5**
* Relevance: **3.74/5**

### Strategy 2

* Chunk size: 250
* Top 20 chunks retrieved
* MRR: **0.8124**
* nDCG: **0.8120**
* Keyword coverage: **95.6%**
* Accuracy: **3.56/5**
* Completeness: **3.66/5**
* Relevance: **3.68/5**

Both strategies performed well during retrieval, with almost identical MRR and nDCG scores. The second strategy achieved slightly better keyword coverage while retrieving far fewer chunks.

However, the answer scores were only moderate. This showed me that retrieving the correct information does not automatically guarantee a strong final answer. The model must still identify, combine, and present the important information correctly.

The evaluation was also extremely slow because every question required one LLM call to generate the answer and another LLM call to judge it. Since the current loop processes questions sequentially, I limited the answer evaluation to 50 questions instead of running all 150.

My main takeaway from today was that RAG evaluation should measure retrieval and generation separately. My retriever is performing well, but the answer-generation stage still needs improvement through better prompting, less noisy context, reranking, or a stronger generation model.
