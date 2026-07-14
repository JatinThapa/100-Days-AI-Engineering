# Day 24 – Choosing the Right LLM and Understanding Benchmarks

Today was a shorter and more theoretical day focused on an important AI engineering question:

**How do we choose the right LLM for a particular task?**

The most powerful or largest model is not automatically the best choice. Selecting an LLM involves balancing its capabilities, limitations, cost, and the actual requirements of the application.

## Factors to Consider When Choosing an LLM

Some of the basic characteristics to compare include:

* **Number of parameters:** Larger models can often learn more complex patterns, but they usually require more memory, computation, and money.
* **Context window:** This determines how much text the model can process in a single request. Applications involving large documents, long conversations, or codebases may need a larger context window.
* **API and computation cost:** A highly capable model may become impractical when it must handle thousands of requests.
* **Knowledge-cutoff date:** Models with older knowledge may not know about recent events, technologies, or updates unless they are connected to external sources.
* **Training data and token count:** The amount and quality of training data influence how much knowledge and capability a model develops.
* **Task-specific performance:** A model that performs well in general conversation may not be the best option for coding, mathematics, reasoning, or multimodal tasks.

Therefore, model selection is really a trade-off between **quality, speed, memory, context length, privacy, and cost**.

## Chinchilla Scaling Law

I also learned about the **Chinchilla scaling law**, introduced through research by Google DeepMind.

The main idea is that increasing only the number of model parameters is not enough. The amount of training data must also increase appropriately for the model to use those parameters effectively.

Under a fixed training-compute budget, the research suggested that model size and the number of training tokens should be scaled together. A larger model trained on insufficient data may be undertrained, while a smaller model trained on much more data may use the available compute more efficiently.

It provides a useful rule of thumb:

> When increasing model size, the amount of training data should also increase proportionally.

However, this law mainly focuses on improving a model during **pretraining**. Modern AI systems can now improve their practical performance during inference by using techniques such as:

* Retrieval-Augmented Generation
* Tool and function calling
* Search
* Longer reasoning processes
* External memory and databases

Because of this, raw parameter count and training-token count are no longer the only factors determining how useful an AI system can be.

## Advanced LLM Benchmarks

I then explored six difficult benchmarks used to evaluate frontier language models.

### GPQA

**Graduate-Level Google-Proof Q&A** evaluates expert-level scientific knowledge.

It contains 448 difficult questions written by specialists in subjects such as biology, chemistry, and physics. The questions are challenging enough that non-expert humans reportedly perform poorly even with internet access.

### MMLU-Pro

**MMLU-Pro** is a more difficult and refined version of the original Massive Multitask Language Understanding benchmark.

It tests knowledge and reasoning across many academic subjects. It also increases the number of answer choices from four to ten, making guessing less effective and requiring stronger understanding.

### AIME

**AIME** evaluates advanced mathematical reasoning using problems from the American Invitational Mathematics Examination.

These are challenging competition-style problems designed for talented high-school mathematics students. The benchmark tests whether a model can perform multi-step reasoning rather than simply recall mathematical facts.

### LiveCodeBench

**LiveCodeBench** evaluates the coding ability of language models using problems from platforms such as LeetCode, AtCoder, and Codeforces.

Its continuously updated problems help reduce the possibility that a model has already encountered the exact solutions during training.

### MuSR

**MuSR** focuses on complex reasoning and logical deduction.

Tasks can involve analysing long scenarios, such as a detailed mystery, and determining who had the means, motive, and opportunity. This tests whether the model can connect information spread across a long passage.

### Humanity’s Last Exam

**Humanity’s Last Exam**, or HLE, is designed as an extremely difficult and subject-diverse benchmark for frontier AI systems.

It contains thousands of expert-level questions across many fields, including multimodal questions. Its purpose is to remain challenging even as models begin saturating older academic benchmarks.

## Limitations of Benchmarks

Although benchmarks are useful, they cannot provide a complete measurement of intelligence or real-world usefulness.

One major problem is **training-data contamination**. If benchmark questions or similar solutions appeared in a model’s training data, the model may appear capable even though it is recalling an answer rather than reasoning through it.

Benchmarks may also be applied inconsistently. Differences in prompts, tool access, reasoning-token budgets, sampling settings, or scoring methods can significantly affect the final result.

Many benchmarks are also narrowly scoped. A high score in mathematics, coding, or multiple-choice questions does not necessarily mean that a model will perform well in an actual application.

Other limitations include:

* Difficulty measuring nuanced or creative reasoning
* Benchmarks becoming saturated as models improve
* Models being optimized specifically for benchmark performance
* Evaluation results failing to reflect reliability, latency, or cost
* Strong benchmark performance not always transferring to real-world tasks

The most interesting concern I learned about was **evaluation awareness**.

Some researchers are investigating whether sufficiently advanced models might recognise that they are being evaluated and behave differently during tests. In theory, a model could produce unusually safe or instruction-following responses during evaluation without behaving identically in every real-world situation.

This is an important concern in AI alignment research, but it should not be treated as conclusively proven for frontier models.

## Final Takeaway

Today helped me understand that choosing an LLM is not simply about selecting the model with the highest parameter count or leaderboard score.

A good model choice depends on:

**The task → required capability → context size → reliability → speed → cost → deployment constraints**

Benchmarks are valuable tools for comparing models, but they should be combined with task-specific testing under realistic conditions.

Overall, today was less about building something and more about understanding how AI engineers evaluate models before deciding which one should actually power an application.
