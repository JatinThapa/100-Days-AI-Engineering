## Day 18 Summary – 100 Days of AI 🚀

Today I explored two very interesting sides of AI: **how models predict text** and how AI can turn **audio into useful meeting notes**.

First, I learned how to **visualize token prediction in a language model**. Instead of just seeing the final answer, I looked at the possible next tokens the model could choose, along with their probabilities. The visualization made it clearer how an LLM builds a response step by step: at each stage, it considers many possible tokens, but the tokens with higher probabilities usually guide the answer toward something meaningful and coherent.

The attached output helped me understand that text generation is not magic. It is a repeated process of predicting the next most likely token based on the previous context.

The second part of the day was about creating **meeting minutes from an audio file** 🎧📝

I downloaded an audio file, mounted Google Drive inside Colab, and stored the file in a folder so it could be accessed from the notebook. Then I used Hugging Face pipelines with:

`openai/whisper-medium.en`

to transcribe the audio into text.

After getting the transcript, I moved into the summarization step. I used an `AutoModelForCausalLM` with quantization configuration to make the model more memory-efficient. Before passing the transcript to the model, I tokenized it using `AutoTokenizer` and formatted it with `apply_chat_template`, so the model could understand the instruction properly.

Finally, I generated the output in Markdown format, turning the raw transcript into cleaner, structured meeting minutes.

Overall, Day 18 helped me connect two important ideas:

AI models generate text by predicting tokens one step at a time, and with the right pipeline, those same models can be used to build practical workflows like audio transcription, summarization, and automatic meeting minutes.
