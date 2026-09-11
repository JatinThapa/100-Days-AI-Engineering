# Day 82 — Turning My Deal Scanner into an Agent 🛒🤖

Today I took another step toward making my deal-finding system feel like a proper **agentic application**.

The scanner I built earlier was still living as somewhat messy **Jupyter notebook code**. It worked, but it wasn't exactly the kind of code I'd want inside a real project. 😂

So today's main task was to **refactor and modularize the scanner**, turning that notebook logic into a reusable `ScannerAgent` Python class.

### 🧩 Building the Scanner Agent

I created `ScannerAgent` as a subclass of my base `Agent` class:

```python
class ScannerAgent(Agent):
    MODEL = "gpt-5-mini"
```

I also kept the model instructions inside the agent itself through dedicated **system and user prompt templates**. These prompts tell the LLM to select exactly five promising deals, focus on detailed product descriptions, and most importantly, be extremely careful about extracting the **actual selling price**.

For example, a listing saying:

**"$100 off a $300 product"**

should result in:

**$200**

rather than incorrectly returning `$100`.

This price validation is particularly important because the scanner will eventually feed its results into the rest of my price-estimation system.

### 📰 Fetching Only New Deals

I also cleaned up the RSS scraping workflow by making the agent check its existing **memory** before processing new deals.

```python
urls = [opp.deal.url for opp in memory]
scraped = ScrapedDeal.fetch()
result = [scrape for scrape in scraped if scrape.url not in urls]
```

So the scanner doesn't repeatedly process deals that it has already seen.

The workflow is now essentially:

**Memory → Fetch RSS Deals → Remove Previously Seen Deals → Process New Deals**

That small change makes the scanner much more practical for eventually running continuously.

### ✍️ Preparing the LLM Input

I created a separate `make_user_prompt()` method to take the scraped deals and convert them into a clean prompt for the model.

Instead of mixing scraping, formatting, and inference into one giant block of notebook code, each responsibility now has its own method.

That's one of the biggest improvements I made today: **separating concerns** so the code is easier to understand, test, and modify later.

### 🧠 Structured Outputs Again

Just like I explored earlier, I continued using **Structured Outputs** for the scanner.

The agent calls OpenAI using:

```python
response_format=DealSelection
```

and parses the response directly into my Pydantic `DealSelection` model.

After the response comes back, I also perform a small validation step and remove anything with a price less than or equal to zero.

So the scanner pipeline is now:

**RSS Feeds → Scraped Deals → Filter New Deals → LLM Selection → Structured Output → Validated Deals**

### 🧪 Adding a Testing Path

One other useful addition was a dedicated `test_scan()` method.

Instead of needing to hit the RSS feeds and call the LLM every time I want to test another part of my application, I can return a predefined `DealSelection`.

That gives me a predictable set of sample products for development and testing.

It's a small feature, but it makes the rest of the system much easier to build without constantly depending on live data or API calls.

### 💡 Today's Takeaway

Today's work wasn't about learning a flashy new AI technique.

It was about taking code that **works** and turning it into code that is actually **usable inside a larger system**.

I'm slowly moving from:

**“I wrote some code in a notebook.”**

to:

**“I have a reusable agent with clear responsibilities.”** 🤖

And that's an important part of AI engineering that I don't want to overlook.

The Scanner Agent can now fetch deals, avoid duplicates, construct prompts, call an LLM with structured outputs, validate the results, and provide test data when needed.

The next step is to start connecting this agent with the rest of my deal-finding system and move closer to the bigger goal:

**Find deals → Estimate fair price → Decide whether it's actually a bargain.** 🔎💰

🎯 **Day 82 complete.**
