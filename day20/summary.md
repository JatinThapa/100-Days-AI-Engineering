# Day 20 Summary — 100 Days of AI 🚀

Today was a full-on hackathon project grind day.

I spent most of the day working on our **computer vision healthcare system**, where doctors and patients can interact using **gestures and voice**, and the system generates a clean AI-powered medical report at the end.

The first major issue I fixed was with the **AI report generation flow**.
Previously, the report would get stuck at:

```txt
Report generating...
```

At first, it looked like the AI model or API was the problem, but the real issue was that the **Celery worker was not running**.

That helped me understand the backend architecture better:

```txt
FastAPI / Uvicorn → handles API requests
Celery worker     → handles background jobs like AI report generation
Redis             → works as the message broker
```

So the report was not being generated directly inside the API request. The API was probably queuing the job, but without the Celery worker running, nobody was picking up that job. Once I started the worker properly, the report generation flow started working.

After that, I updated the `.env` configuration to use a local Ollama model:

```txt
llama3.2:latest
```

This was important because earlier, when no proper AI provider was available, the system could fall back to a basic non-AI stub report. By configuring the local Llama model, the report generation could actually use a real local AI model instead of just producing a minimal fallback response.

The next part of the day was frontend integration.

One of my teammates had refactored the whole UI, so I replaced my local frontend with the updated version. But after testing it, I noticed an important issue: the frontend did not properly preserve sessions. Every time the page was refreshed after login, the user was being logged out.

So I worked on fixing the frontend session persistence issue.

The fix involved making sure the frontend auth state properly survives refreshes and does not redirect the user too early before the stored auth state is loaded. After the fix, both doctor and patient logins stayed active even after refreshing their dashboards.

That was a small bug on the surface, but a pretty important one for the actual user experience. A healthcare dashboard where doctors and patients get logged out on refresh would feel broken immediately.

Finally, I worked on extending the AI provider support.

The project already supported providers like:

```txt
OpenAI
Anthropic
Ollama/local model fallback
```

But since I do not currently have OpenAI or Anthropic API keys, I added support for:

```txt
Gemini
```

This means the backend can now be configured to generate reports using Gemini as well, while still keeping the previous provider options intact. So now the project has more flexibility depending on what API keys or local models are available.

Overall, today was one of those days where I touched multiple real-world parts of an AI application:

```txt
Background workers
Environment configuration
Local LLM fallback
Frontend session persistence
Team UI integration
AI provider extensibility
```

It was less about learning one isolated AI concept and more about understanding how an actual AI-powered product works when frontend, backend, background jobs, environment variables, and model providers all have to cooperate.

Basically, Day 20 was a reminder that AI apps are not just about calling a model.

They are also about making sure the worker is running, the env is correct, the frontend remembers the user, the backend has fallback paths, and the whole system does not silently collapse because one terminal command was missing 😭
