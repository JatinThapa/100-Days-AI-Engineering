## Day 48 – Random Forest and XGBoost for Price Prediction

Today, I experimented with two popular tree-based machine learning models on my product-price prediction dataset: **Random Forest** and **XGBoost**.

Before implementing Random Forest, I first revised how it works because it had been a long time since I last used it.

Random Forest is an **ensemble learning algorithm**, which means it combines the predictions of multiple smaller models. In this case, those smaller models are decision trees.

A decision tree behaves like a flowchart made up of conditions. For my dataset, the input features were generated from product descriptions, where each feature represented how frequently a particular word appeared.

A single tree might learn patterns such as:

* If the word “TV” appears frequently,
* and the description also contains “LED” and “HD,”
* then the product is likely to belong to a higher price range.

Decision trees are simple and fast, but they can easily overfit the training data. Random Forest reduces this problem by training many trees using different random samples of the data and features. For regression tasks, it averages their predictions to produce the final result.

I trained a Random Forest model using **30,000 training items** and 100 decision trees:

```python
subset = 30_000

rf_model = RandomForestRegressor(
    n_estimators=100,
    random_state=42,
    n_jobs=4
)

rf_model.fit(X[:subset], prices[:subset])
```

To predict the price of a new product, I transformed its summary using the same vectorizer and passed it to the trained model:

```python
def random_forest(item):
    x = vectorizer.transform([item.summary])
    return max(0, rf_model.predict(x)[0])
```

The Random Forest model performed slightly better than yesterday’s Bag-of-Words and Linear Regression approach.

Its results were:

* **Mean absolute error: $70.77**
* **R² score: 44.1%**

Next, I experimented with **XGBoost**.

Like Random Forest, XGBoost also combines multiple decision trees. However, instead of building all the trees independently, it builds them sequentially. Each new tree focuses on correcting the errors made by the previous trees.

Because training was manageable, I used the complete training dataset:

```python
np.random.seed(42)

xgb_model = xgb.XGBRegressor(
    n_estimators=1000,
    random_state=42,
    n_jobs=4,
    learning_rate=0.1
)

xgb_model.fit(X, prices)
```

XGBoost achieved the best performance so far:

* **Mean absolute error: $68.23**
* **R² score: 56.4%**

Although today was a relatively light experimentation day, it reinforced an important lesson: traditional machine learning is not only useful for understanding the history of AI. Models such as Random Forest and XGBoost are still widely used in real-world applications, especially when datasets contain clearly identifiable and structured features.

I also saw an example where Random Forest was trained on around **800,000 products**, achieving an error of approximately **$56.40**, although the training process took nearly 13 hours. This showed me how strongly dataset size and computation time can affect model performance.

Tomorrow, I plan to move beyond traditional machine learning and experiment with **neural networks and LLM-based approaches** on the same dataset.
