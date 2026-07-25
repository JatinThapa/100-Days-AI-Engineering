# Day 35 – Building RAG Evaluations with JSONL, Pydantic and LLM Judges

Today I moved from learning the theory behind RAG evaluations to actually implementing them in code.

## Building the Golden Dataset with JSONL

The first thing I learned was that golden evaluation datasets are commonly stored using the **JSONL — JSON Lines — format**.

In a normal JSON file, multiple objects would usually be placed inside a list:

```json
[
  {"question": "..."},
  {"question": "..."}
]
```

In a JSONL file, every line is instead an independent valid JSON object:

```json
{"question": "Who won the IIOTY award in 2023?", "keywords": ["Maxine", "Thompson", "IIOTY"], "reference_answer": "Maxine Thompson won the Insurellm Innovator of the Year award in 2023.", "category": "direct_fact"}
{"question": "When was Insurellm founded?", "keywords": ["2015", "founded"], "reference_answer": "Insurellm was founded in 2015.", "category": "direct_fact"}
```

The complete file is not one valid JSON array. Instead, it is a sequence of separate JSON documents, one per line.

This format is useful for evaluation datasets because individual examples can be read, processed and appended without loading or rewriting the entire file.

## Representing the Dataset with Pydantic

I was also introduced to **Pydantic**, a Python library used to describe, validate and parse structured data using classes that inherit from `BaseModel`.

Each test question could therefore be represented using fields such as:

* Question
* Keywords
* Reference answer
* Category

Pydantic can validate the types of these properties and can also generate a JSON Schema describing the expected structure.

My golden dataset contained **150 questions** divided into seven categories:

* Direct fact: 70
* Temporal: 20
* Spanning: 20
* Comparative: 10
* Numerical: 10
* Relationship: 10
* Holistic: 10

I realised that **spanning** and **holistic** questions are often more difficult for a RAG system.

A direct factual question may be answered using a single chunk. A spanning question, however, may require connecting information from different documents or chunks. Holistic questions may require understanding information spread across a much larger portion of the knowledge base.

These questions expose weaknesses in chunking, retrieval, entity linking and multi-hop reasoning.

## Creating Structured Evaluation Results

Inside `eval.py`, I created two Pydantic models:

* `RetrievalEval` for retrieval metrics
* `AnswerEval` for LLM-generated answer scores

`RetrievalEval` stores MRR, nDCG, the number of keywords found, the total number of keywords and keyword coverage. `AnswerEval` stores written feedback along with accuracy, completeness and relevance scores.

This makes the evaluation results easier to inspect and process than receiving unstructured text from the evaluator.

## Evaluating Retrieval

The retrieval evaluation first calls the existing `fetch_context()` function using the test question. It then examines the retrieved chunks to determine where the expected keywords appear.

The implementation calculates:

### Mean Reciprocal Rank

For each keyword, the code searches through the retrieved documents.

If the keyword first appears at:

* Rank 1, the reciprocal rank is 1
* Rank 2, it is 1/2
* Rank 3, it is 1/3
* If it is never found, it is 0

The scores are then averaged across the keywords.

For the spanning question I tested, the retrieval result was:

```text
MRR: 0.1667
nDCG: 0.25
Keywords found: 2/4
Keyword coverage: 50%
```

This indicates that only two of the four expected keywords were found and that the matches appeared relatively low in the retrieved ranking.

That poor result was expected because answering the question required connecting information about the IIOTY award winner with separate information about that person’s work.

### nDCG

The code also calculates binary nDCG by assigning:

* `1` when a keyword appears in a retrieved chunk
* `0` when it does not

Matches near the top receive more weight because their contribution is divided by a logarithmic discount. The actual DCG is then divided by the ideal DCG, where the relevant chunks would appear first.

## Evaluating the Generated Answer

The second part of the file evaluates the final RAG answer.

The `evaluate_answer()` function:

1. Generates an answer through the existing RAG pipeline.
2. Creates an evaluator prompt containing the question, generated answer and reference answer.
3. Asks an LLM judge to evaluate accuracy, completeness and relevance.
4. Parses the result into an `AnswerEval` Pydantic object.

The judge is called through LiteLLM using:

```python
judge_response = completion(
    model=MODEL,
    api_base="http://localhost:11434",
    messages=judge_messages,
    response_format=AnswerEval
)
```

The file currently uses the local Ollama model:

```python
MODEL = "ollama_chat/qwen3:4b-instruct"
```

The important technique here was **structured output**.

Instead of allowing the judge to return arbitrary text, `response_format=AnswerEval` asks it to produce data matching the expected Pydantic structure. The returned JSON is then validated using:

```python
AnswerEval.model_validate_json(...)
```

Structured output improves the reliability and consistency of the response format. However, it does not guarantee that the evaluator’s reasoning or scores are correct—it only makes the output easier to validate and process.

## Important Corrections and Observations

### 1. The test question and reference answer do not match

The question was:

> What product does the IIOTY award winner work on?

But the reference answer stated:

> Maxine Thompson works as a Senior Data Engineer.

A job title is not a product.

This means the evaluation example itself is inconsistent. Either the question should be changed to:

> What role does the IIOTY award winner have?

Or the reference answer should identify the actual product that Maxine works on.

Because of this mismatch, the LLM judge’s criticism was not completely fair. It penalised the generated answer for failing to mention “Senior Data Engineer,” even though that does not directly answer the product question.

This demonstrates an important lesson: **the quality of an evaluation can never exceed the quality of its golden dataset**.

### 2. The current MRR implementation is a custom variation

Standard MRR calculates the reciprocal rank of the first relevant document for each query and then averages the result across multiple queries.

The current implementation calculates a reciprocal rank separately for every keyword and averages those keyword scores.

That is still a useful custom metric, but a more precise name might be:

> Mean Keyword Reciprocal Rank

A standard implementation would first label complete chunks as relevant or irrelevant and then identify the first relevant chunk for each question.

### 3. Keyword coverage is not exactly Recall@K

The current `keyword_coverage` value measures the percentage of expected keywords found in the retrieved results.

That is useful, but it is not standard Recall@K.

Standard Recall@K is:

[
Recall@K =
\frac{\text{Relevant documents retrieved in the top K}}
{\text{Total known relevant documents}}
]

Keyword coverage can act as a lightweight proxy when the dataset does not contain document-level relevance labels, but the two metrics should not be treated as identical.

### 4. The scores are described as 1–5 but not technically constrained

The Pydantic fields describe accuracy, completeness and relevance as values from 1 to 5, but the schema does not currently enforce those limits.

That likely explains why the judge returned a relevance score of `0.0`, even though the prompt requested a minimum score of 1.

The fields could later be constrained using:

```python
accuracy: float = Field(ge=1, le=5)
completeness: float = Field(ge=1, le=5)
relevance: float = Field(ge=1, le=5)
```

### 5. Retrieved context is not currently shown to the judge

Although the `AnswerEval` description mentions evaluating against the retrieved context, the judge prompt currently receives only:

* The question
* The generated answer
* The reference answer

It does not receive the retrieved chunks.

Therefore, it can evaluate agreement with the reference answer, but it cannot properly measure whether the answer is **faithful to the retrieved evidence**.

To evaluate faithfulness or groundedness, the retrieved context would also need to be included in the judge prompt.

## Main Takeaway

Today’s work helped me understand that evaluating RAG systems involves more than asking whether an answer looks correct.

A proper evaluation pipeline needs:

1. A carefully curated golden dataset
2. Relevant document or keyword labels
3. Retrieval metrics
4. Reference answers
5. Consistent answer-scoring criteria
6. Structured outputs for reliable processing
7. Continuous improvements to the evaluation dataset

The biggest lesson was that evaluation code alone is not enough. The questions, reference answers, relevance labels and scoring definitions must also be accurate.

Otherwise, even a powerful LLM judge can confidently produce a misleading evaluation.

Day 35 turned RAG evaluation from a theoretical concept into an actual working pipeline—and also showed me why evaluating the evaluator is just as important as evaluating the RAG system.
