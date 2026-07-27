# Day 37 of 100 Days of AI — Advanced RAG Techniques

Today was a lighter learning day focused on advanced techniques that can improve the performance of a RAG pipeline. I explored around ten approaches, including some that avoid LangChain completely and implement the pipeline natively.

The techniques included:

1. **Chunking R&D**
   Experimenting with different chunking strategies in an informed trial-and-error process.

2. **Encoding R&D**
   Selecting the best embedding model based on a test set and business requirements. For image-based knowledge, multimodal encoders can map images and text into the same vector space, but another practical method is to generate image captions with an LLM and embed the captions.

3. **Prompt improvement**
   Providing the model with better instructions, relevant context, conversation history and the current date.

4. **Document preprocessing**
   Using an LLM to rewrite documents into a format that is easier to query. This can also support semantic chunking, where documents are divided based on meaning rather than fixed character counts.

5. **Query rewriting**
   Using an LLM to transform the user’s natural-language question into a clearer query designed specifically for retrieval.

6. **Query expansion**
   Generating multiple retrieval queries from one user question to increase the chances of finding all relevant information.

7. **Reranking**
   Reordering the retrieved chunks based on how relevant they are to the user’s question and selecting only the strongest results.

8. **Hierarchical RAG**
   Creating summaries of the knowledge base at multiple levels, such as separate summaries for employees, products and contracts. The system first searches the summaries for coarse-grained information and then drills down into the detailed chunks.

9. **Graph RAG**
   Representing information as nodes and relationships using graph databases. While graph RAG is currently popular, many similar tasks can also be handled using metadata without requiring a dedicated graph database.

10. **Agentic RAG**
    Using agents to decide how information should be retrieved while combining retrieval with memory and tools such as SQL databases.

I also explored the idea that “RAG is dead” in 2026.

One argument is that modern LLMs have very large context windows, so the entire knowledge base could simply be placed inside the prompt. However, this may waste time and computation because the model still needs to process a large amount of irrelevant information. A good vector search can often remove most of that unnecessary data before the LLM is called.

The second argument is that agents have replaced traditional RAG pipelines because they can independently decide how to search, research and retrieve information. However, agentic retrieval is still fundamentally RAG—the system is simply giving the retrieval process more flexibility and decision-making ability.

The biggest takeaway from today was that RAG is not disappearing. It is evolving through better preprocessing, smarter retrieval, reranking, hierarchical search, graphs and agents.
