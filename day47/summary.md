## Day 47 – Establishing Baselines for Product Price Prediction

Today, I downloaded the fully preprocessed version of the product dataset that I explored earlier. Unlike the smaller “lite” version, this dataset contained around **800,000 structured product records**, which was much larger than I expected.

The product descriptions had already been rewritten into a clean and consistent format, making them more suitable for training models to predict a product’s price from its textual information.

Before trying proper machine learning models, I started with a deliberately simple and slightly ridiculous baseline: assigning every test item a completely random price between $1 and $999.

```python
def random_pricer(item):
    return random.randrange(1, 1000)
```

As expected, this performed terribly:

* Error: **$382.08**
* R²: **−896.9%**

A strongly negative R² means the predictions were considerably worse than simply predicting a constant average price for every product.

Next, I created a constant-price baseline by assigning the same average price to every item. Surprisingly—but logically—it performed much better than the random predictor:

* Error: **$106**
* R²: approximately **−0.2%**

One correction here is that the average should be calculated from the **training dataset**, not the test dataset. Using the test-set prices to create the prediction introduces data leakage. A mean predictor calculated from the training data should normally produce an R² close to zero and serves as a useful baseline for evaluating future models.

I then trained my first actual machine learning model: **Linear Regression**.

Because linear regression cannot directly understand text, I created a few basic numerical features:

```python
def get_features(item):
    return {
        "weight": item.weight,
        "weight_unknown": 1 if item.weight == 0 else 0,
        "text_length": len(item.summary)
    }
```

The model learned the following coefficients:

* Weight: **0.449**
* Unknown-weight indicator: **−6.628**
* Text length: **0.247**
* Intercept: **51.11**

Its training results were:

* Mean Squared Error: **25,615.84**
* R²: **−0.059**

When evaluated using the test data, it achieved:

* Error: **$101.56**
* R²: **5.2%**

The features were extremely limited, but the model still slightly outperformed the constant-price baseline. This showed that properties such as weight and description length contain at least some information about a product’s price, although they are not nearly enough for strong predictions.

Finally, I moved on to a basic NLP technique: **Bag of Words**.

Using Scikit-learn’s `CountVectorizer`, I selected the 2,000 most common non-stop words from the training summaries:

```python
vectorizer = CountVectorizer(
    max_features=2000,
    stop_words="english"
)

X = vectorizer.fit_transform(documents)
```

This gave me an important realization about the difference between Bag-of-Words vectors and the embeddings I previously used in RAG.

A Bag-of-Words vector is simply a list of word counts. Each position represents one word from the vocabulary, and its value shows how many times that word appears in the product summary. It does not understand meaning, context, similarity, or word order.

Dense embeddings, in comparison, attempt to represent the semantic meaning of the complete text, allowing related words and descriptions to appear closer together in vector space.

Despite its simplicity, Bag of Words produced a major improvement:

* Error: **$76.81**
* R²: **41.8%**

This demonstrated that the words used in a product’s description contain much more useful pricing information than basic features such as weight and text length.

Today’s experiments created a clear progression:

**Random prices → constant baseline → basic numerical features → Bag of Words**

Each step gave me a more meaningful benchmark for evaluating future models.

Tomorrow, I plan to experiment with more advanced machine learning algorithms such as **Random Forest and XGBoost** and compare how much further they can improve the price predictions.
