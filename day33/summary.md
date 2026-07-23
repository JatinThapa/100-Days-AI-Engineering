# Day 33 Summary — Building a Complete Conversational RAG Pipeline

Day 33 was about connecting all the pieces from the previous two days and building a complete RAG pipeline using **LangChain, ChromaDB, Ollama, and Gradio**.

Since the knowledge-base ingestion process was already complete, today’s focus was the **retrieval and answer-generation stage**:

**User question → Retrieve relevant chunks → Add them to the prompt → Generate an answer with the LLM**

I explored two useful LangChain abstractions that made the pipeline more organized:

* **LLM abstraction:** A common interface for interacting with models from providers such as OpenAI, Anthropic, or Ollama.
* **Retriever abstraction:** An interface built around the vector store and embedding model that retrieves documents relevant to a query.

Both components could be called using `.invoke()`, which made the workflow more consistent and reduced the amount of manual code required.

I started by importing `ChatOllama`, `Chroma`, `SystemMessage`, and `HumanMessage`. I then reopened the existing Chroma vector database and passed it the **same embedding model used during ingestion**, since changing the embedding model would make the stored and query vectors incompatible.

From the vector store, I created a retriever and connected it to an Ollama-based LLM. I also prepared a system prompt containing a placeholder for the retrieved context.

The main RAG function followed these steps:

1. Retrieve relevant document chunks from Chroma.
2. Combine the chunks into a clean context string.
3. Insert that context into the system prompt.
4. Send the system prompt and user question to the LLM.
5. Display the response through a Gradio chat interface.

The basic pipeline worked, but testing revealed an important limitation: the model calls were initially **stateless** because the previous conversation history was not being passed into the messages.

Even after adding history, follow-up questions such as:

> “Who is Avery?”
> “What did she do before?”

could still fail during retrieval. The LLM might understand that “she” refers to Avery, but the retriever only sees the latest ambiguous question and may not retrieve any Avery-related documents.

To improve this, I separated the application into three files:

* `ingest.py` for loading, chunking, embedding, and storing documents
* `answer.py` for retrieval and response generation
* `app.py` for the Gradio interface

I also created a function that combined previous user messages with the latest question before sending the text to the retriever. This helped follow-up questions retain more conversational context.

However, this solution introduced another problem. Combining the entire conversation can cause **topic contamination**. After discussing Avery Lancaster, a new question such as “Who won the IIOTY award?” may still be interpreted through the earlier Avery-related context, causing the retriever to search in the wrong semantic direction.

I also noticed a chunking-related problem. One chunk might state that “Maxine” won the IIOTY award, while another part of the document contains her complete name, “Maxine Thompson.” If only the first chunk is retrieved, the LLM may not confidently connect both references.

Today showed me that creating a basic RAG pipeline is relatively straightforward, but building a reliable **conversational RAG system** is much harder. Conversation history, pronoun resolution, topic changes, chunk boundaries, and incomplete context can all affect retrieval quality.

The next challenge is to make follow-up questions understandable without allowing unrelated previous messages to interfere with new queries.
