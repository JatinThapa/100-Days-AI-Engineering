## Day 46 – Learning LLM Batch Processing for Dataset Preparation

Today’s goal was to use an LLM to transform long and messy product descriptions into concise, consistent summaries that would be more suitable for training a price-prediction model.

The processed dataset contains around **22,000 products**, and each product needs a rewritten description containing its most useful information. I originally planned to generate these summaries using Groq’s Batch API with `openai/gpt-oss-20b`. However, batch processing required enabling billing, so instead of running the complete job, I studied and tested the full workflow to understand how it works.

Batch processing allows thousands of requests to be placed into files and submitted as asynchronous jobs. Unlike normal API calls, the program does not wait for every response immediately. The provider processes the requests within a specified completion window, after which the results can be downloaded. Groq’s Batch API currently costs 50% less than its equivalent synchronous API calls, making it useful for large dataset-processing tasks that do not require immediate responses.

The first step was assigning a unique ID to every product:

```python
for index, item in enumerate(items):
    item.id = index
```

These IDs are important because batch results are not guaranteed to return in their original order. Each ID allows the generated summary to be matched with the correct product later.

I then created a concise system prompt instructing the LLM to rewrite each product using a consistent structure:

* Title
* Category
* Brand
* One-sentence description
* One-sentence feature summary

I tested the prompt using Groq’s `openai/gpt-oss-20b`. The result was detailed and mostly well structured, using **446 input tokens and 97 output tokens** at a cost of approximately **0.006 cents**.

However, the output still included the product’s part numbers in its title despite the prompt explicitly asking the model not to include them. This showed that even strong models may not follow every instruction perfectly, so the generated summaries should still be validated or cleaned after generation.

I also tested a local Qwen 3 4B instruct model through Ollama. It produced a shorter result at no API cost, but its quality was slightly lower. Most noticeably, it incorrectly classified the door-hardware product as **Electronics**. This demonstrated why comparing models on real examples is important before processing an entire dataset.

Next, I learned how to convert every product into a batch-compatible JSONL request. Each line contained:

* A unique `custom_id`
* The `POST` request method
* The `/v1/chat/completions` endpoint
* The selected model
* The system prompt
* The product’s complete description
* A low reasoning-effort setting

Each JSONL line represents one independent API request. I then created a function that writes a selected range of product requests into a `.jsonl` file, allowing the 22,000 products to be divided into smaller batches such as 1,000 products per file.

The complete batch workflow was:

1. Generate the JSONL request file.
2. Upload it to Groq with the purpose set to `batch`.
3. Create a batch job using the uploaded file ID.
4. Check the job’s status using its batch ID.
5. Download the output JSONL file after completion.
6. Read each result and use its `custom_id` to locate the original product.
7. Store the generated description inside the product’s `summary` field.

Groq officially recommends splitting very large workloads into smaller batches because shorter files have a better chance of completing within the selected processing window.

Since I could not run the full paid batch today, I plan to download the already-processed dataset from Hugging Face, containing the 22,000 products and their rewritten summaries, and continue toward training the price-prediction model.

Today’s biggest takeaway was that preparing a large dataset with an LLM involves much more than simply looping through API calls. A reliable pipeline needs structured prompts, unique request IDs, JSONL generation, batch submission, status tracking, result retrieval, error handling, output validation, and careful mapping back to the original data.
