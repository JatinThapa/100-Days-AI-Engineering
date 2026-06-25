# AI Brochure Generator — Task Summary

Today I worked on a small AI-powered brochure generator using **BeautifulSoup** and a local/open-source LLM like **Llama 3.2**. The goal was to take a company website URL, scrape useful website content, identify relevant links, and generate a clean brochure in Markdown format.

The task was mainly divided into two parts.

## Part 1: Selecting Relevant Links

The first part was about extracting links from a company website and asking the LLM to decide which links are useful for making a brochure.

A website can contain many links like `/about`, `/courses`, `/contact`, `/login`, `/privacy-policy`, etc. Not all of them are useful. Pages like **About**, **Courses**, **Contact**, **Mission**, or **Success Stories** are helpful, while pages like **Login**, **Signup**, **Terms**, and **Privacy Policy** are usually not.

For this, I used a function like `get_links_user_prompt()` to prepare a prompt containing all the scraped links. The LLM was then asked to return only the relevant links in a structured JSON format.

The function `select_relevant_links()` used the system prompt and user prompt to call the LLM and get relevant brochure-worthy links.

The flow was:

```txt
Website URL
→ fetch website links
→ build user prompt with links
→ LLM selects relevant links
→ return selected links in JSON format
```

This was a good use case for an LLM because selecting useful links requires understanding the meaning of the links, not just simple keyword matching.

## Part 2: Generating the Brochure

The second part was about using the selected links to collect useful content and generate the final brochure.

The function `fetch_page_and_all_relevant_links()` first fetched the landing page content using `fetch_website_contents()`, which uses **BeautifulSoup** to parse the HTML, remove unnecessary elements like scripts, styles, images, and inputs, and extract readable text.

Then, for each relevant link selected by the LLM, it fetched that page’s content too:

```python
result += f"\n\n### Link: {link['type']}\n"
result += fetch_website_contents(link["url"])
```

So the final context included the landing page plus useful pages like About, Courses, Contact, or Success Stories.

I also added a `normalize_link()` function to clean URLs before fetching them. This helped fix issues with relative links like `/about`, unsupported links like `mailto:` or `javascript:`, and suspicious URLs such as `www.about.udemy.com`.

After collecting all the content, `get_brochure_user_prompt()` created the final user prompt for brochure generation. Then `stream_brochure()` used the `brochure_system_prompt` and the user prompt to generate the final brochure in Markdown format.

The final flow was:

```txt
Website URL
→ scrape landing page
→ extract links
→ LLM selects relevant links
→ normalize selected URLs
→ fetch selected page contents
→ build brochure prompt
→ LLM generates Markdown brochure
```

## Main Learnings

Today’s main learning was that an LLM can be used as part of a pipeline, not just as a chatbot. In this project, the LLM was used twice:

```txt
1. To select relevant links
2. To generate the final brochure
```

I also learned that real websites can be messy. Some work only with `www`, some without it, and some links may be broken or oddly structured. That made URL normalization an important step.

The current version works inside a Python notebook and is still a little clumsy, but the core pipeline is working. Later, this can be improved by making the code more modular and possibly using Selenium for JavaScript-heavy websites.

Overall, today’s task turned a basic web scraping workflow into a small AI pipeline:

```txt
BeautifulSoup Scraper → Link Selection with LLM → Content Fetching → Brochure Generation
```
