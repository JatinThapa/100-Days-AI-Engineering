# Day 72 — Revisiting Model Training, Hyperparameter Tuning & Batch Inference ⚙️🤖

Today was another **revision-focused day** in my #100DaysOfAI journey.

Rather than jumping into a completely new project, I went back to some of the fundamentals I had covered earlier—particularly **model training and hyperparameter tuning**. With the number of different models and experiments I've worked with throughout this journey, I felt it was useful to step back and reinforce the concepts behind how we actually get the best performance from a model.

### 🔄 Revisiting Model Training

I revised the overall training workflow and the role different components play in it:

* 📊 Preparing and splitting the dataset
* 🧠 Choosing an appropriate model
* ⚙️ Configuring training parameters
* 📉 Understanding training and validation loss
* 🧪 Evaluating the model on unseen data
* 🔁 Iterating based on the results

I also revisited the difference between **model parameters** learned during training and **hyperparameters** that we choose before or during the training process.

### 🎛️ Hyperparameter Tuning

I spent some time revising how hyperparameters can significantly affect model performance.

Things like:

🔹 Learning rate
🔹 Batch size
🔹 Number of epochs
🔹 Model depth/size
🔹 Regularization
🔹 Optimizer settings

can make a huge difference in whether a model **underfits, overfits, or learns effectively**.

This connected nicely with my earlier experiments involving **QLoRA fine-tuning**, where selecting appropriate training parameters was just as important as choosing the model itself.

### ⚡ Exploring Groq Batch Requests

I also looked into **batch processing through Groq** and how batch requests can be useful when you need to process a large number of independent LLM requests.

Instead of sending requests one by one and waiting for each response, batch processing allows multiple requests to be submitted together and processed asynchronously.

This is particularly interesting for the kind of work I've been doing with large product datasets, where I might need an LLM to process **thousands of individual items**.

It also made me think more about the difference between **interactive inference** and **large-scale offline processing**.

💡 **Today's Takeaway**

Today's revision reminded me that AI engineering isn't always about learning something new every single day.

Sometimes, going back to the fundamentals helps connect the newer concepts with what I've already learned.

And the more I work with AI systems, the more I realize that **training a model is only one part of the problem**.

Choosing the right hyperparameters, evaluating the results, optimizing inference, and figuring out how to process requests efficiently are all equally important parts of building a practical AI system. 🧠⚙️

🎯 **Day 72 complete.** 🚀
