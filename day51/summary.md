## Day 51 – Revisiting RAG Evaluation

Today was more of a revision day than a new learning day.

I went back to some of the concepts I covered during Days 34 and 35, particularly around **evaluating RAG systems**, because these ideas are important enough to revisit before moving further into more advanced AI engineering topics.

The main thing I revised was why evaluation is so important in a RAG pipeline.

When building RAG systems, it is easy to keep changing things like chunk size, embedding models, retrieval settings, rerankers, prompts, or the number of retrieved documents and simply judge whether the results “feel better.”

Proper evaluation helps replace that trial-and-error approach with measurable results.

### Golden Dataset

The foundation of a RAG evaluation pipeline is a **golden dataset**.

A golden dataset contains carefully designed examples such as:

* User questions
* Reference answers
* Relevant keywords or facts
* Expected supporting context
* Question categories

This dataset acts as a benchmark that can be reused whenever the RAG pipeline changes.

It should also evolve over time as new failure cases are discovered through testing or real user queries.

I also revisited the fact that the quality of the golden dataset itself is extremely important.

If the reference answer, question, or expected context is incorrect, even a powerful evaluator can produce misleading scores.

So evaluation data needs validation just like the system being evaluated.

### Retrieval Evaluation

The first major part of RAG evaluation is measuring whether the retriever is finding the correct information.

I revised several important retrieval metrics.

**MRR – Mean Reciprocal Rank**

MRR measures how high the first relevant result appears in the retrieved ranking.

If the first relevant result appears:

* At rank 1 → score = 1
* At rank 2 → score = 1/2
* At rank 3 → score = 1/3

So the higher the correct chunk appears, the better the score.

**nDCG – Normalized Discounted Cumulative Gain**

Unlike MRR, which mainly focuses on the first relevant result, nDCG considers the entire ranking.

It rewards retrieval systems that place highly relevant chunks near the top while penalizing relevant information that appears further down.

**Recall@K**

Recall measures how much of the relevant information was successfully retrieved within the top K results.

High recall is important when the answer requires information from multiple chunks.

**Precision@K**

Precision measures how many of the retrieved chunks are actually useful or relevant.

This matters because retrieving too much irrelevant information wastes context-window space and can potentially confuse the answering LLM.

I also revisited **keyword coverage**, which provides a simple way of checking whether important facts or terms expected for a question appear in the retrieved content.

### Different Types of Questions

Another important concept I revised was that not all questions are equally difficult for a RAG system.

The golden dataset I worked with previously contained around 150 questions across categories such as:

* Direct fact
* Temporal
* Comparative
* Numerical
* Spanning
* Holistic

Direct factual questions are usually easier because the answer may exist inside a single chunk.

Spanning and holistic questions are harder because the system may need to retrieve and combine information from multiple chunks or even multiple documents.

This is where retrieval quality becomes especially important.

### Answer Evaluation

Retrieving the correct context is only half of the pipeline.

The generated answer itself also needs to be evaluated.

Simple keyword matching is often unreliable because two answers can express the same information using completely different wording.

Instead, an **LLM can be used as a judge** to evaluate characteristics such as:

* Accuracy
* Completeness
* Relevance
* Faithfulness to the retrieved context

This gives a better indication of the actual quality of the answer from a user's perspective.

### Structured Outputs with Pydantic

I also revised how I implemented these evaluations programmatically.

Using **Pydantic's BaseModel**, I created structured evaluation objects such as:

**RetrievalEval**

* MRR
* nDCG
* Keyword coverage

**AnswerEval**

* Accuracy
* Completeness
* Relevance

Using structured outputs with LiteLLM allowed the evaluator model to return predictable and validated data instead of unstructured natural-language responses.

This made it much easier to store results, compare experiments, and calculate average scores across the evaluation dataset.

### Today's Main Takeaway

The biggest takeaway from today's revision was that **evaluation is what turns RAG experimentation into engineering**.

Without evaluation, changing embeddings, chunking strategies, prompts, reranking techniques, or retrieval parameters becomes mostly guesswork.

A reliable RAG evaluation system requires three things working together:

**A trustworthy golden dataset + meaningful retrieval metrics + reliable answer evaluation**

And even then, the evaluation pipeline itself must be checked carefully because incorrect benchmark data can make good systems look bad—or bad systems look good.

Today was mainly about reinforcing these foundations before continuing further.

🎯 **Day 51 complete.**
