# Day Summary 🚀

Today was not heavily focused on learning completely new concepts, but it was a solid practice day. I rebuilt my LLM-calling programs from scratch and wrote every piece of code myself, which helped me understand the flow much better. The main project of the day was creating an **MCQ Generator** that scrapes webpage content and uses an LLM to generate multiple-choice questions from it. 🧠✨

One of the most interesting things I explored today was **training-time vs inference-time scaling**. I learned how models can behave very differently depending on how much reasoning effort they are allowed to use. Parameters like `reasoning_effort` — whether set to minimal, low, medium, or high — can drastically affect how carefully a model thinks, reasons, and arrives at the correct answer. ⚙️🤖

I also experimented with different free models through the **OpenRouter API**, including `openai/gpt-oss-120b:free`, `openrouter/owl-alpha`, and `google/gemma-4-31b-it:free`. After testing them, Gemma felt the best to me overall. Since I was a bit tired of constantly using Ollama locally, trying cloud-based free models was a refreshing change. 😄☁️

To compare the models, I tested them using tricky reasoning questions like the **bookworm page-gnawing puzzle** and the **prisoner’s dilemma**. It was surprising to see how differently each model responded. Some models were more competitive, some were more cautious, and some preferred safer answers depending on how their developers tuned their behavior. 🧩

Overall, today was more about strengthening fundamentals than chasing new topics. I got hands-on practice with LLM API calls, built a useful MCQ generator, and understood more deeply how reasoning behavior changes across different models and inference settings. ✅
