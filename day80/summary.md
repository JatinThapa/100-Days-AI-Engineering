# Day 80 — Building an AI-Powered Deal Scanner 🛒🤖

Today marked another interesting step in my **#100DaysOfAI** journey: I started building a **deal scanner in Python** that can collect online deals, extract useful product information, and use an LLM to identify the best ones.

The main focus today was combining three things I've been working with throughout this journey:

**Web scraping + RSS feeds + Structured Outputs** 🔗🧠

### 📰 Scraping Deals from RSS Feeds

Instead of scraping an entire website from scratch, I decided to start with **RSS feeds**, which provide a much cleaner and more structured source of recently published deals.

I used three DealNews feeds covering:

* 📱 Electronics
* 💻 Computers
* 🏠 Smart Home

Each feed provides around **10 deals**, giving the scanner a pool of products to process.

For parsing the RSS feeds, I used the **Feedparser** Python library.

### 🔎 Building the `ScrapedDeal`

I created a `ScrapedDeal` class to represent each deal retrieved from the RSS feed.

The class takes the raw RSS entry and extracts useful information such as:

* Product title
* Summary
* Deal URL
* Detailed product information
* Product features

For the information that isn't directly available in the RSS entry, I used **Requests + BeautifulSoup** to visit the actual deal page and extract the detailed product content.

I also cleaned up the scraped text and split the content into **details and features**, giving the LLM much richer information about the actual product.

This part was important because I don't just want my scanner to know *that something is on sale*—I want it to understand **what the product actually is**.

### 🧠 Bringing in the LLM

Once I had a collection of scraped deals, I needed the LLM to select the best ones.

I designed both a **system prompt and user prompt** that instructed the model to return exactly **5 high-quality deals** from the available options.

But there was one particularly important requirement:

> **The model needs to return the actual selling price, not the discount amount.**

For example, if a deal says:

**“$100 off a $300 product”**

the scanner needs to return:

💰 **$200**

—not `$100`.

I also instructed the model to be very careful with phrases like **“$XXX off”** or **“reduced by $XXX”**, because those numbers aren't necessarily the actual price.

Another important instruction was that **the product description matters more than the wording of the deal itself**.

So rather than filling the output with things like coupons, discount percentages, or promotional language, I wanted the model to provide a useful **3–4 sentence description of the actual product**.

And finally, the model should only select a deal when it is **highly confident that the price is correct**.

### 🧩 Using Structured Outputs

This was also another opportunity to revisit the structured output concepts I studied on **Day 77**.

Instead of using the usual `.create()` call, I used:

```python
response = openrouter.chat.completions.parse(
    model=MODEL,
    messages=messages,
    response_format=DealSelection,
    reasoning_effort="minimal"
)

results = response.choices[0].message.parsed
```

The reason for using `.parse()` is that I wanted the LLM's response to conform directly to my **Pydantic models**.

I defined a `Deal` model containing:

```python
class Deal(BaseModel):
    product_description: str
    price: float
    url: str
```

and then wrapped multiple deals inside:

```python
class DealSelection(BaseModel):
    deals: List[Deal]
```

So instead of getting back some unpredictable block of text, I get a structured collection of **five `Deal` objects** containing exactly the information my application needs.

### 🛒 Example Output

For example, one of the structured results looked roughly like:

**Product:** Tikland 1.91" fitness tracker with a compact smartwatch design, fitness tracking capabilities, a 1.91" display, and support for basic smart features such as making and answering calls.

**Price:** `$15`

**URL:** Deal page URL

This is exactly the kind of output I want my future agent to consume without having to manually parse messy LLM responses.

### 💡 Today's Takeaway

Today's work might look like a relatively small piece of the larger project, but it connects several concepts I've been learning throughout the journey.

The workflow is now starting to look like:

**RSS Feed → Scraping → Product Information → LLM Selection → Structured Output → Clean Deal Objects**

And that's exciting because this is moving my project one step closer to the **Scanner Agent** I planned earlier.

I've already built an ensemble system that can **estimate what a product should cost**.

Now I'm building a scanner that can **find products and their current prices**.

Put those two together, and we might finally have something that can answer the question:

> **“Is this actually a good deal?”** 👀💰

🎯 **Day 80 complete.**
