# Day 8 Summary – Building LLM User Interfaces with Gradio

Today I learned how to build simple and interactive user interfaces using the **Gradio** framework.

I started with the basics and saw how a single line like:

```python
gr.Interface(fn=shout, inputs="textbox", outputs="textbox", flagging_mode="never").launch()
```

can create a working UI directly inside a notebook. I also explored useful Gradio options such as `share=True` for creating a temporary public URL, `inbrowser=True` for opening the app directly in the browser, and `auth=("jatin", "1234")` for adding basic access control.

After understanding the basics, I connected Gradio with LLM calls and built an interface where I could select between free GPT and Gemini models. This helped me understand how a frontend-like UI can interact with different LLM backends.

A major concept I learned today was the `yield` function in Python. I understood how it returns a generator object and why it is useful for streaming responses word by word or chunk by chunk into a Markdown output.

Finally, I applied these concepts to upgrade my AI Brochure Generator. The scraper remained mostly the same, but the experience became much more visually appealing and interactive. Users can now enter a company name, provide a landing page URL, and select which model they want to use to generate the brochure.

Overall, today helped me move from simple backend LLM calls toward building more usable AI applications with interactive interfaces.
