## Day 45 – A Five-Step Strategy for Applying LLMs to Business Problems

Today was a more theoretical learning day focused on a structured five-step strategy for selecting and applying large language models to real business problems.

### 1. Understand

The first step is to clearly understand the problem before jumping directly into building an AI solution.

This includes gathering business requirements, identifying the expected outcome, and deciding whether AI is genuinely the best approach. It is also important to define how success will be measured using both model-centric metrics, such as accuracy or latency, and business-centric metrics, such as revenue, productivity, customer satisfaction, or cost reduction.

The available data must also be examined carefully:

* Is it structured or unstructured?
* Is the quality sufficient?
* Is there enough data?
* Are there privacy or compliance concerns?

Finally, non-functional requirements such as cost, scalability, latency, development budget, and implementation timeline must be considered.

### 2. Prepare

The next step is to research existing solutions before building anything new.

This involves studying previous research, checking whether a simpler non-AI solution could solve the problem, and identifying useful baseline models.

Relevant LLMs can then be compared based on factors such as context-window size, price, speed, licensing, deployment options, and task-specific performance. Leaderboards, benchmarks, arenas, and specialist evaluations can help narrow down the options.

The data must then be curated by cleaning, preprocessing, filtering, and splitting it into suitable training, validation, and test sets. This is the stage I am currently working on for my product price-prediction project.

### 3. Select

After preparing the data and comparing possible models, the next step is experimentation.

Different models should be used to build small prototypes, and their outputs should be compared using the success criteria defined earlier. The most suitable models can then be trained or validated using the curated dataset.

The goal is not simply to choose the most powerful model, but to select the model that best satisfies the project’s accuracy, speed, cost, and deployment requirements.

### 4. Customize

Once a model has been selected, it can be adapted and optimized for the specific business task.

Some common techniques include:

* **Prompting:** Using clear instructions, structured prompts, and few-shot examples to produce more consistent outputs.
* **RAG:** Retrieving relevant information from a knowledge base and adding it to the model’s context.
* **Agents:** Dividing a workflow into multiple model or tool calls, with an agent coordinating the overall process.
* **Fine-tuning:** Updating a model using task-specific or proprietary data so that it becomes better adapted to a particular behaviour or domain.

Prompting, RAG, and agents mainly improve the system during inference, while fine-tuning modifies the model during training.

An interesting shift in modern AI development is that teams often begin with inference-time techniques because they are usually faster, cheaper, and easier to iterate on. Fine-tuning is considered when these approaches are not sufficient.

### 5. Productionize

The final step is turning the prototype into a reliable production system.

This includes designing the APIs between models and applications, choosing the hosting and deployment architecture, and addressing scalability, latency, monitoring, security, compliance, and observability.

The system must also be continuously evaluated using the business metrics defined during the first step. As data and requirements change, the model may need to be retrained, updated, or replaced.

Today’s biggest takeaway was that selecting an LLM is only one small part of building an AI solution. A successful system begins with understanding the business problem and continues through data preparation, experimentation, customization, deployment, monitoring, and continuous evaluation.
