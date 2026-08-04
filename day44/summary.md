## Day 44 – Preparing the Amazon Product Dataset

Today was a relatively light day focused on downloading and preparing the dataset for my next project: predicting the price of a product based only on its description.

I explored the **McAuley-Lab/Amazon-Reviews-2023** dataset on Hugging Face, which contains Amazon product information and reviews across multiple categories. Instead of downloading the entire dataset, I selected only the raw metadata for the **Appliances** category:

```python
dataset = load_dataset(
    "McAuley-Lab/Amazon-Reviews-2023",
    "raw_meta_Appliances",
    split="full",
    trust_remote_code=True
)
```

The Appliances dataset contained **94,327 products**, which is still large enough for experimentation while being more manageable than the complete dataset.

To represent each cleaned product consistently, I created a Pydantic `Item` model containing fields such as the product title, category, price, description, weight, summary, prompt, and ID. This gives every processed product a predictable and structured format that can later be stored, analysed, or passed into a model.

I also started building the parsing pipeline. The parser removes unnecessary metadata, restricts the amount of text collected from each product, and filters products based on their price and description length.

The current filtering rules include:

* Minimum description length of 600 characters
* Price range between $0.50 and $999.49
* Maximum text length limits for individual and combined fields
* Removal of metadata such as part numbers, bestseller rankings, battery information, and model numbers

Filtering the price range should reduce extreme outliers and create a more focused dataset for the price-prediction model.

Finally, the parser extracts useful information such as the title, description, features, details, weight, and price. It combines the relevant textual information into a cleaned product description and returns it as a structured `Item` object.

Tomorrow, I plan to continue parsing the dataset and begin visualising important properties such as price distributions, text lengths, missing values, and possible outliers.
