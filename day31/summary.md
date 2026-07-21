# Day 31 – Understanding RAG, Embeddings, and Vector Search

Today I learned the bigger idea behind **Retrieval-Augmented Generation**, or RAG.

The main problem RAG tries to solve is:

> How can an application perform a “fuzzy lookup” and retrieve information that is relevant to a user’s question, even when the wording is completely different?

Traditional keyword search mainly looks for exact or partially matching words. RAG systems can instead search according to **semantic meaning**, and this becomes possible through vectors and embeddings.

## Autoregressive Models vs Encoder Models

Until now, most of the language models I had explored were **autoregressive models**.

An autoregressive language model generates text by predicting the next plausible token based on the tokens that came before it.

For example:

> “The sky is…”

The model examines the previous tokens and predicts that the next token could be something like “blue.”

It then repeats this process one token at a time until the response is complete. Models used for chat and text generation generally follow this approach.

Today I learned about another important category: **encoder models**.

Instead of generating the next token, an encoder model examines the complete input and creates a numerical representation of it. This representation attempts to capture the input’s overall meaning and context.

Encoder-based architectures are commonly used for tasks such as:

* Text classification
* Sentiment analysis
* Semantic search
* Similarity comparison
* Information retrieval
* Creating embeddings for RAG systems

BERT is a well-known example of an encoder-based Transformer model. Embedding services and models, such as those provided through OpenAI’s embeddings API, are designed specifically to convert text into useful numerical representations.

## What Is a Vector Embedding?

When an embedding model receives a piece of text, it returns a list of numbers known as a **vector**.

The process of generating this numerical representation is called **embedding** or **vector embedding**.

A vector might look something like this:

```text
[0.021, -0.734, 0.182, 0.491, ...]
```

In real embedding models, these vectors commonly contain hundreds or thousands of dimensions.

Each individual number is not usually meaningful on its own. However, the complete arrangement of numbers represents certain patterns and features learned by the model.

A vector can represent:

* A token
* A word
* A sentence
* A paragraph
* An entire document
* An image
* A user or product
* Other abstract information

The important idea is that inputs with similar meanings generally receive vectors that are positioned close to one another in the embedding space.

For example, these two sentences use different words:

> “How can I reset my password?”

> “I forgot my login credentials.”

A keyword-based search might struggle if the stored document does not contain the exact words used in the query. However, an embedding model may place their vectors close together because both sentences express a similar idea.

My simple way of remembering this is:

> Similar vector positions usually represent similar concepts.

## Tokens and Vectors Are Not the Same

Today I also clarified the difference between **tokens** and **vectors**, which can easily become confusing.

Tokens are the smaller units into which text is divided before being processed by a language model. A token may represent a complete word, part of a word, punctuation, or another text fragment.

Each token is assigned a token ID from the tokenizer’s vocabulary.

For example, a tokenizer might convert some text into IDs such as:

```text
[52, 1847, 91, 306]
```

These IDs are identifiers, not direct representations of meaning. A token ID of 100 is not mathematically “more meaningful” than a token ID of 10.

Inside the neural network, each token ID is mapped to a learned **token embedding**, which is itself a vector. These vectors are then transformed and propagated through the model’s layers.

Therefore, a more accurate distinction is:

* **Tokens** are units of text.
* **Token IDs** are numerical labels assigned to those tokens.
* **Token embeddings** are vectors representing tokens inside the model.
* **Text embeddings** are vectors designed to represent the meaning of a larger input such as a sentence, paragraph, or document.

So vectors are not only final outputs. They are also used internally throughout neural networks to carry and transform information.

## From Word2Vec to Modern Embeddings

Before modern Transformer-based embedding models, techniques such as **Word2Vec** were used to create vector representations of individual words.

Word2Vec became famous because relationships between certain concepts could sometimes be observed through vector arithmetic.

A classic simplified example is:

```text
King - Man + Woman ≈ Queen
```

This showed that vectors could capture semantic relationships such as gender, royalty, and other patterns found in language.

However, Word2Vec generally assigns one fixed vector to each word. This means that a word such as “bank” would receive the same representation whether it referred to a financial institution or the side of a river.

Modern contextual models improve on this by considering the surrounding text. They can therefore create different representations depending on how a word is being used.

Modern embedding models can also represent complete sentences, paragraphs, and documents rather than only individual words.

## How Vector Similarity Works

Once two pieces of text have been converted into vectors, mathematical techniques can be used to measure how similar they are.

Common similarity methods include:

* Cosine similarity
* Dot product
* Euclidean distance

The exact numbers do not need to be translated manually. The system compares the positions or directions of the vectors and determines which stored vectors are closest to the user’s query vector.

This is what allows semantic or fuzzy retrieval to work.

## The Role of a Vector Database

A vector database stores embeddings along with the information connected to them.

For a RAG application, a document is usually divided into smaller sections called **chunks**. Each chunk is converted into an embedding and stored with:

* Its vector
* The original text
* Metadata such as the document name, page, heading, or source

When the user asks a question, the application embeds the question and searches the database for the most similar stored vectors.

The vector database does **not convert the vectors back into natural language**. Instead, it returns the original text chunks associated with the closest vectors.

## The RAG Pipeline

The RAG pipeline I understood today works roughly like this:

1. Documents are collected and divided into smaller chunks.
2. An embedding model converts every chunk into a vector.
3. The vectors are stored in a vector database alongside their original text and metadata.
4. The user sends a question.
5. The same embedding model converts the question into a query vector.
6. The application compares the query vector with the vectors stored in the database.
7. The most semantically similar text chunks are retrieved.
8. The application sends the user’s question and the retrieved context to a generative language model.
9. The language model uses that additional context to produce a grounded response.

In a simplified form:

```text
User question
      ↓
Embedding model
      ↓
Query vector
      ↓
Vector similarity search
      ↓
Relevant original text chunks
      ↓
Question + retrieved context
      ↓
Generative LLM
      ↓
Final answer
```

The generative model is not necessarily summarizing the retrieved information. Depending on the instructions, it may answer a question, explain something, compare information, extract details, or create a summary.

## Final Understanding

My biggest takeaway from today was that RAG connects two different capabilities:

* **Embedding models** help retrieve information according to meaning.
* **Generative models** use the retrieved information to create a natural-language answer.

The embedding model acts like the search system, while the generative model acts like the writer or reasoner.

RAG therefore allows an LLM to answer using information that may not exist in its original training data. Instead of retraining the complete model whenever new information is added, we can update the external knowledge base and retrieve the relevant information when it is needed.

Today’s lesson gave me the conceptual foundation behind semantic search, embeddings, vector databases, and the complete retrieval process that powers a RAG application.
