## 100DaysOfAI – Day 59 🚀

Today was mostly about **evaluating the fine-tuning run** I left training for around 1.5 hours.

I used **Weights & Biases (W&B)** to monitor the training and evaluation metrics and get a better understanding of how the model was learning.

📉 **Training Loss**

* Started at **2.96159**
* Reached a global minimum of **1.19098** at step 365
* Finished at **1.26659** at step 625

The `train/grad_norm` also showed a healthy decrease, going from around **4.64** initially to **0.67** by the end of training.

📊 **Evaluation Loss**

* Started at **1.27998**
* Finished at **1.24718**

Along with this, W&B tracked metrics like token accuracy, runtime, and samples per second.

Overall, the training curves looked **promising**, especially compared to where the model started. 🚀

Tomorrow, I'll finally put the model to the real test by running it against the **test dataset** and seeing how well it actually performs on unseen data.

One step closer to finding out whether the fine-tuning actually worked! 🤞

