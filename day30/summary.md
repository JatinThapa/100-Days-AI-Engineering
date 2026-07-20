# Day 30 Summary — Introduction to RAG with a Simple Knowledge Base

Today marked my first practical introduction to **Retrieval-Augmented Generation**, commonly known as **RAG**.

At first, RAG sounded like it might be a very complicated architecture. However, the central idea turned out to be quite simple.

Until now, I had explored several ways of helping an LLM produce better answers, such as:

* Writing clearer system prompts
* Providing additional context
* Using one-shot and multi-shot prompting
* Giving the model access to tools
* Including previous conversation messages

RAG takes the idea of providing context one step further.

Instead of expecting the LLM to already know everything about a company or relying on a huge prompt containing all available information, we create a collection of trusted, domain-specific information called a **knowledge base**.

Whenever a user asks a question, the application:

1. Searches the knowledge base for relevant information.
2. Retrieves the information that may help answer the question.
3. Adds that information to the model’s prompt.
4. Sends the augmented prompt to the LLM.
5. Generates an answer grounded in the retrieved company data.

This creates the three main stages behind RAG:

* **Retrieval:** Find relevant information.
* **Augmentation:** Add that information to the prompt.
* **Generation:** Ask the LLM to generate the final answer.

The basic idea is therefore not to make the model magically know more, but to **equip it with the right information at the moment it needs to answer a question**.

---

## The Business Scenario

To test this concept, I worked with a fictional insurance technology company called **Insurellm**.

The goal was to build an internal **AI knowledge worker** that could answer questions from company employees.

The company had a shared knowledge base containing information about:

* Employees
* Job roles
* Career histories
* Salaries and compensation
* Performance records
* Company products
* Product descriptions and specifications

Instead of requiring employees to manually search through several files, the AI assistant would retrieve the relevant documents and answer questions about the company.

Examples of possible questions included:

* Who is Avery Lancaster?
* What is Carllm?
* What position does a particular employee hold?
* What products does Insurellm offer?
* What is an employee’s career history?

The desired assistant needed to be accurate, inexpensive to operate, and capable of saying that it did not know the answer when the required information was unavailable.

---

## Building the Knowledge Base

The employee and product documents were stored inside two directories:

```text
knowledge-base/employees/
knowledge-base/products/
```

Python’s `glob` module was used to locate the files, while `Path` was used to extract information from their filenames.

The contents of each file were read and stored inside a Python dictionary named `knowledge`.

For employee files, the employee’s surname was used as the dictionary key:

```python
name = Path(filename).stem.split(" ")[-1]
knowledge[name.lower()] = f.read()
```

Product documents were stored using the product name as the key:

```python
name = Path(filename).stem
knowledge[name.lower()] = f.read()
```

This produced keys such as:

```text
lancaster
chen
sharma
carllm
healthllm
homellm
claimllm
```

At this stage, the Python dictionary acted as a very small and simple knowledge database.

---

## Retrieving Relevant Information

The retrieval system used a basic keyword-matching function.

The user’s message was first cleaned so that only letters and spaces remained. It was then converted to lowercase and split into individual words.

Each word was checked against the keys in the knowledge dictionary:

```python
def get_relevant_context(message):
    text = "".join(
        ch for ch in message
        if ch.isalpha() or ch.isspace()
    )

    words = text.lower().split()

    return [
        knowledge[word]
        for word in words
        if word in knowledge
    ]
```

For example, the question:

```text
Who is Lancaster?
```

contained the word `lancaster`, which matched a key in the knowledge base.

The application therefore retrieved Avery Lancaster’s employee document.

The retrieval function could also return multiple documents. A question such as:

```text
Who is Lancaster and what is Carllm?
```

matched both:

```text
lancaster
carllm
```

The system could then provide both documents to the LLM as additional context.

---

## Augmenting the Prompt

A system prompt instructed the model to behave as an expert on Insurellm, its employees, and its products.

It also told the model to:

* Give brief and accurate answers
* Use the supplied company context
* Admit when the answer was unknown

The retrieved documents were added beneath a section called:

```text
Relevant context:
```

If no matching information was found, the prompt instead stated that no relevant additional context was available.

This meant the LLM did not receive the entire knowledge base for every question. It only received the documents selected by the retrieval function.

That is the key improvement offered by RAG: the model receives **relevant context rather than all possible context**.

---

## Connecting the Retriever to the LLM

The final chat function followed this pipeline:

```text
User question
      ↓
Keyword extraction
      ↓
Knowledge-base lookup
      ↓
Relevant documents retrieved
      ↓
Documents added to system prompt
      ↓
Prompt and conversation history sent to LLM
      ↓
Grounded answer generated
```

The application used the OpenAI-compatible OpenRouter client to send messages to the selected model.

The message list contained:

1. The system prompt with retrieved context
2. The existing chat history
3. The user’s latest message

Finally, the assistant was placed inside a Gradio `ChatInterface`, providing a simple browser-based chat application for testing the knowledge worker.

---

# Important Problem 1 — Duplicate Surnames

One major limitation appeared when testing employees named **Priya Sharma** and **Neha Sharma**.

The employee documents were indexed using only the final word of each filename:

```python
Path(filename).stem.split(" ")[-1]
```

For both employees, this produced the same dictionary key:

```text
sharma
```

A Python dictionary cannot contain two independent values under the same key. When the second Sharma document was loaded, it replaced the document that had previously been stored under `sharma`.

Conceptually, the result became:

```python
knowledge["sharma"] = priya_document
knowledge["sharma"] = neha_document
```

After the second assignment, only one of those documents remained accessible through that key.

This explains why questions about Priya Sharma and Neha Sharma could return the same information. The retriever was not distinguishing between the two people—it was retrieving whichever document currently occupied the shared `sharma` key.

This also revealed a broader weakness of exact keyword retrieval:

* First names were not necessarily indexed.
* Duplicate surnames caused collisions.
* Misspellings would not match.
* Synonyms would not match.
* Related concepts would not match unless they used the exact stored keyword.

A better basic approach would use unique keys such as:

```text
priya sharma
neha sharma
```

The system could also maintain separate indexes for:

* Full names
* First names
* Surnames
* Employee IDs
* Product names

However, even that would still be based mainly on exact words rather than meaning.

---

# Important Insight 2 — Conversation History Behaved Like Memory

Another interesting observation happened while asking about **Avery Lancaster**.

When the question was initially:

```text
Who is Avery?
```

the retriever could not find anything.

This happened because the knowledge-base key was:

```text
lancaster
```

and not:

```text
avery
```

The question contained no word that matched a dictionary key, so Avery Lancaster’s document was not retrieved.

After changing the question to:

```text
Who is Lancaster?
```

the correct employee document was found and included in the prompt.

The surprising part came afterwards. When the assistant was asked about Avery again using only her first name, it could now answer correctly.

The retriever had not suddenly learned that `avery` and `lancaster` represented the same person. Instead, the chat function was also sending the complete conversation history to the model:

```python
messages = [
    {"role": "system", "content": system_message}
] + history + [
    {"role": "user", "content": message}
]
```

The previous conversation already contained information connecting Avery with Lancaster. Therefore, the LLM could answer the follow-up question using the chat history.

This demonstrated the difference between two types of context:

### Retrieved context

Information selected from the external knowledge base for the current question.

### Conversational context

Information already present in previous user and assistant messages.

The successful second answer about Avery did not mean the retrieval function had improved. It meant the model could resolve the reference using the preceding conversation.

This was an important realization because conversational memory can sometimes hide weaknesses in the retrieval system. A system may appear to retrieve information correctly when the answer is actually coming from the chat history.

---

## Limitations of This First RAG Approach

This implementation successfully demonstrated the RAG workflow, but its retrieval method was intentionally basic.

Its current limitations include:

* It only supports exact keyword matches.
* It does not understand semantic similarity.
* It does not recognize synonyms or related phrases.
* It cannot reliably handle spelling errors.
* First names may fail when only surnames are indexed.
* Duplicate surnames can overwrite one another.
* Entire documents are inserted instead of smaller relevant sections.
* Large documents may waste context-window space.
* It has no ranking mechanism when several documents match.
* It may retrieve a document because of a matching word even when the document is not truly relevant.
* Conversation history may make retrieval failures less obvious.
* It uses a Python dictionary rather than a scalable search system or vector database.

For example, a future semantic retriever should ideally understand that:

```text
Who runs Insurellm?
```

may be related to a document describing the company’s CEO, even if the question does not contain the words `Avery` or `Lancaster`.

The current keyword system cannot make that connection unless one of the words exactly matches a stored key.

---

## How This Can Be Improved

Future versions of the project can gradually replace the simple keyword lookup with a more realistic RAG pipeline.

Possible improvements include:

### Better document identifiers

Store employees using their complete names or unique employee IDs instead of surnames alone.

### Metadata

Attach structured metadata to documents, such as:

* Employee name
* Department
* Job title
* Document type
* Product category

### Document chunking

Split large documents into smaller sections so only the most relevant passage is added to the prompt.

For example, an employee document could be divided into:

* Personal summary
* Career progression
* Performance history
* Compensation
* Other HR notes

A salary question would then retrieve only the compensation section rather than the entire employee record.

### Embeddings

Convert the user’s question and knowledge-base chunks into vector representations that capture semantic meaning.

### Vector database

Store and search those embeddings using a vector database.

### Similarity search

Retrieve the chunks whose meanings are most similar to the user’s question rather than relying only on exact matching words.

### Ranking and filtering

Rank retrieved documents by relevance and filter results using metadata.

### Source citations

Display which company files or passages were used to generate each answer.

### Evaluation

Create a collection of test questions and expected answers to measure:

* Retrieval accuracy
* Answer correctness
* Hallucination rate
* Response relevance
* Cost and speed

---

## Main Learning

The biggest takeaway from today was that RAG is built around a small but powerful idea:

> Do not ask the LLM to answer with only its existing knowledge. Retrieve trustworthy information related to the question and provide it as context before generating the answer.

Today’s implementation was deliberately trivial, using a Python dictionary and exact keyword matching rather than embeddings or a vector database.

However, it successfully demonstrated the complete foundation:

```text
Knowledge base → Retrieval → Prompt augmentation → LLM generation
```

It also showed that building a reliable RAG system is not only about connecting documents to an LLM.

The quality of the final answer depends heavily on:

* How documents are stored
* How they are indexed
* How user questions are interpreted
* How relevant passages are selected
* How duplicate or ambiguous entities are handled
* How conversation history is managed
* How much context is passed to the model

Today was only the simplest version of the AI knowledge worker, but it established the core workflow that can later be extended using document chunking, embeddings, vector databases, semantic search, metadata filtering, reranking, and source-grounded answers.

**Day 30 was not about building an advanced RAG system—it was about understanding the small idea that makes advanced RAG systems possible.**
