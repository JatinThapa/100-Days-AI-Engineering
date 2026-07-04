# 100 Days of AI – Day 14 Summary 🚀

Today was more of an exploration day where I experimented with using Hugging Face models inside Google Colab.

I worked with image generation models such as `stabilityai/sdxl-turbo`, `stabilityai/stable-diffusion-xl-base-1.0`, and a few other diffusion-based models. One important thing I learned is that these models are different from the transformer-based language models used in chatbots. Instead of generating text token by token, diffusion models generate images by starting from noise and gradually denoising it into a final image.

I also noticed that these models can be quite heavy and require a lot of RAM/VRAM, especially in a Colab environment. This made me understand why running image generation models locally or in notebooks can be more resource-intensive compared to simple API calls.

Another key concept I learned was inference steps. Increasing the number of inference steps generally gives the model more chances to refine the image during the denoising process. In simple terms, fewer steps can generate images faster but may reduce quality, while more steps can improve detail and consistency, though it takes more time and resources.

I also explored the idea of using a refiner model, such as `stabilityai/stable-diffusion-xl-refiner-1.0`, to improve the quality of generated images. In one setup, `n_steps = 40` and `high_noise_frac = 0.8` were used, meaning around 80% of the denoising process was handled by the base model and the remaining 20% by the refiner model. This helped me understand how different models can work together in stages to produce better final outputs.

Finally, I experimented with text-to-speech using Microsoft’s `microsoft/speecht5_tts` model. This allowed me to test how Hugging Face models can also be used for generating voice outputs, not just text or images.

Overall, Day 14 was not about building a big project, but about getting hands-on with Hugging Face models, understanding diffusion-based image generation, experimenting with refiners, and trying out text-to-speech inside Colab.
