# 100 Days of AI – Day 49: Building a Vanilla Neural Network for Price Prediction

Today, I continued working with the Amazon product dataset and experimented with building a vanilla neural network from scratch using PyTorch.

Before training any models, I tried a small and slightly painful experiment: manually predicting product prices using only their summaries.

I selected 100 products and attempted to estimate their prices based on the information provided in the text. This quickly became much more difficult than expected. Product descriptions do not always clearly indicate price, and similar-looking products can belong to completely different price ranges.

After comparing my predictions with the actual prices, my results were:

* Mean absolute error: **$87.62**
* R² score: **6.9%**

Unsurprisingly, I was not a very good price-prediction model 😭

However, this experiment helped me understand how difficult the task actually is. If a human struggles to infer prices from short and inconsistent product descriptions, a machine-learning model will also need strong features, sufficient data, and careful training to perform well.

## Preparing the text data

I originally planned to train the neural network using the complete dataset of approximately 800,000 products.

However, converting the entire sparse feature matrix into a dense NumPy array caused a memory error. The matrix had around 800,000 rows and 5,000 features, which required almost 30 GB of memory as a `float64` array.

Because of this limitation, I switched to the lighter dataset containing approximately 20,000 products.

Instead of using `CountVectorizer`, I used `HashingVectorizer`:

```python
vectorizer = HashingVectorizer(
    n_features=5000,
    stop_words="english",
    binary=True
)

X = vectorizer.fit_transform(documents)
```

The vectorizer converted each product summary into a fixed-length feature vector containing 5,000 values.

Using `binary=True` meant that the vectorizer recorded whether a word or feature was present rather than counting how many times it appeared.

One useful property of `HashingVectorizer` is that it does not need to build and store a vocabulary. This makes it more memory-efficient and suitable for large datasets.

However, hashing can also cause collisions, where multiple words are mapped to the same feature index. The binary representation also removes information about word frequency, which may reduce the amount of useful information available to the model.

## Building the neural network

I then created a fully connected neural network by extending PyTorch’s `nn.Module` class.

The model contained:

* An input layer with 5,000 features
* A hidden layer with 128 neurons
* Six hidden layers with 64 neurons each
* A final output layer with one neuron for predicting the product price
* ReLU activation functions between the hidden layers

```python
class NeuralNetwork(nn.Module):
    def __init__(self, input_size):
        super(NeuralNetwork, self).__init__()

        self.layer1 = nn.Linear(input_size, 128)
        self.layer2 = nn.Linear(128, 64)
        self.layer3 = nn.Linear(64, 64)
        self.layer4 = nn.Linear(64, 64)
        self.layer5 = nn.Linear(64, 64)
        self.layer6 = nn.Linear(64, 64)
        self.layer7 = nn.Linear(64, 64)
        self.layer8 = nn.Linear(64, 1)

        self.relu = nn.ReLU()

    def forward(self, x):
        output1 = self.relu(self.layer1(x))
        output2 = self.relu(self.layer2(output1))
        output3 = self.relu(self.layer3(output2))
        output4 = self.relu(self.layer4(output3))
        output5 = self.relu(self.layer5(output4))
        output6 = self.relu(self.layer6(output5))
        output7 = self.relu(self.layer7(output6))
        output8 = self.layer8(output7)

        return output8
```

The model had a total of:

**669,249 trainable parameters**

This means the training process had to learn more than 669,000 weights and biases from only around 20,000 examples.

## Training the model

I converted the training data into a PyTorch `TensorDataset` and used a `DataLoader` to divide it into mini-batches:

```python
train_dataset = TensorDataset(X_train, y_train)

train_loader = DataLoader(
    train_dataset,
    batch_size=64,
    shuffle=True
)

input_size = X_train_tensor.shape[1]
model = NeuralNetwork(input_size)
```

I trained the model for:

* **2 epochs**
* **Batch size of 64**

An epoch represents one complete pass through the training dataset. Since the model only trained for two epochs, it had relatively few opportunities to adjust its large number of parameters.

## Final results

After training, the neural network achieved:

* Mean absolute error: **$75.05**
* R² score: **43.8%**

The neural network performed significantly better than my manual predictions, reducing the error from $87.62 to $75.05.

However, it still performed slightly worse than the Random Forest and XGBoost models I had tested previously.

Initially, I expected the neural network to outperform the traditional machine-learning models. However, neural networks do not automatically perform better simply because they are deeper or contain more trainable parameters.

Several factors may have limited the model’s performance:

* The model was trained on only 20,000 products.
* It was trained for just two epochs.
* More than 669,000 parameters had to be learned.
* The input consisted of sparse binary text features.
* Hash collisions may have caused some information loss.
* Word frequency and word order were not preserved.
* The deep architecture may have been unnecessarily complex for this representation.
* No regularization, batch normalization, dropout, learning-rate scheduling, or systematic hyperparameter tuning was used.

Tree-based models such as Random Forest and XGBoost can often perform extremely well on structured or engineered features, especially when the dataset is not large enough for a neural network to learn more useful representations.

Therefore, the weaker neural-network result does not necessarily mean that neural networks are unsuitable for the problem. It mainly shows that architecture, feature representation, data size, training duration, and optimization choices all matter.

## Plans for tomorrow

Tomorrow, I plan to return to the full dataset of approximately 800,000 products and explore ways to train without loading the entire dense feature matrix into memory.

Possible approaches include:

* Keeping the complete matrix in sparse format
* Converting only individual batches into dense tensors
* Using smaller numerical data types such as `float32`
* Reducing the number of features
* Applying dimensionality reduction
* Training with a custom dataset or batch generator
* Experimenting with a smaller or more suitable neural-network architecture
* Increasing the number of training epochs
* Comparing different learning rates and optimizers

I also saw a benchmark where someone achieved:

* Mean absolute error: **$63.90**
* R² score: **58.2%**

using the complete dataset.

This gives me a useful result to compare against while improving my own pipeline.

I also plan to test whether large language models can estimate product prices directly from their titles, categories, brands, features, and summaries. It will be interesting to compare human predictions, traditional machine-learning models, neural networks, and LLM-based predictions on the same task.

## Today’s biggest takeaway

A neural network is not automatically better than Random Forest or XGBoost.

Its performance depends heavily on:

* How the input data is represented
* How much training data is available
* The number of parameters
* The network architecture
* The number of training epochs
* Memory-efficient data loading
* The optimization process

Today’s experiment was a simple vanilla implementation, but it helped me understand how text is transformed into numerical features, how a PyTorch neural network is constructed, how mini-batch training works, and why large datasets create practical memory challenges.

**Day 49 complete.**
