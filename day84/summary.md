Day 84: Going Back to Strengthen the Foundations 🧠🔁

Today was one of those days where life happened first and AI came second. 😅

I was out for most of the day and only got back home a few minutes ago. But instead of calling it a missed day, I decided to spend some time revisiting concepts from earlier in my AI journey.

🔹 Chunking Strategies

I went back to the fundamentals of document chunking in RAG and why the way we split information can have a huge impact on retrieval quality.

I revised different approaches such as:

Fixed-size chunking

Chunking based on sentences or paragraphs

Recursive chunking

The importance of chunk size and overlap

How poor chunking can lead to incomplete or irrelevant context


It was a good reminder that RAG isn't simply "put documents into a vector database and search." The quality of what we retrieve starts much earlier — with how we prepare the data.

🔹 LangChain vs. Building RAG From Scratch

I also revisited something I've worked with from both sides: building RAG pipelines with LangChain and implementing the individual pieces without it.

Using frameworks like LangChain can make experimentation and development much faster, but understanding what happens underneath is equally important.

So I went back through the basic flow:

Documents → Chunking → Embeddings → Vector Store → Retrieval → Context → LLM → Response

Seeing the same pipeline both with abstractions and without them helped reinforce an important lesson:

> Frameworks should make you faster, not make you dependent on abstractions you don't understand.



🔹 LLM-as-a-Judge

Finally, I revised LLM-based evaluation, particularly the idea of using an LLM as a judge to evaluate generated responses.

Instead of only asking:

"Did my RAG pipeline produce an answer?"

we can ask much more useful questions:

Is the answer relevant?

Is it grounded in the retrieved context?

Is it factually consistent?

Did the model actually answer the question?

How does one response compare against another?


This is especially useful when traditional metrics don't fully capture the quality of generated text.

🧠 What Day 84 Reinforced

Today's session wasn't about adding another tool, framework, or flashy new concept to my toolkit.

It was about strengthening the foundations underneath the tools I've already learned.

After 84 days, I'm realizing that progress in AI isn't always about moving forward.

Sometimes, going back is exactly what helps you move forward faster. 🚀

84/100 days complete. 🔥
