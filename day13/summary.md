# Day 13 – Hugging Face and Google Colab 🤗⚡

Today was more of a theory-focused day in my 100 Days of AI journey.

I got introduced to Hugging Face, which is one of the most important open-source platforms in the AI ecosystem. I learned that Hugging Face provides access to free and open-source LLMs, datasets, libraries, model hubs, and Spaces. Spaces are especially interesting because they allow people to host AI apps with simple interfaces, often built using Gradio, so users can interact with models directly from the browser.

I also learned about Google Colab, which gives us a remote notebook-style environment that runs in the browser. Instead of running everything on our own laptop, Colab lets us execute code on a remote machine, and in many cases, even provides free access to GPUs like the T4.

Some key benefits of Colab are free GPU access, easy collaboration, shareable notebooks, and avoiding environment mismatch issues because everyone can run the same notebook setup.

At the same time, I learned about some downsides too. Since Colab is free, the runtime can reset at any time, especially when idle. Sometimes the GPU can silently be downgraded to CPU, packages need to be installed again after a fresh session, and it may feel less responsive than coding locally.

I also learned a few survival tips for using Colab properly, such as connecting to a hosted T4 runtime, checking resources, restarting the session when needed, and understanding the difference between restarting a session and fully disconnecting/deleting the runtime.

Overall, Day 13 helped me understand two important tools in the AI development workflow: Hugging Face for discovering and using open-source AI models, and Google Colab for running notebooks on remote machines with GPU support.
