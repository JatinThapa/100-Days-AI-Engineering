# 100 Days of AI – Day 63 🚀

## Taking My First Steps with Modal and Remote Python Compute ☁️

Today was a relatively light day in my 100 Days of AI journey, but I finally started getting hands-on with **Modal**, the serverless cloud platform I discovered while planning my agentic AI system.

My first step was creating a **Modal account** and getting the basic environment set up.

And then came the first surprise. 😂

Modal offers **$30 in free compute credits**, but apparently I needed to add a **payment method** before I could actually use those credits.

So… “free” came with a little asterisk. 😭

After getting past that, I started setting up my Python environment and imported the libraries I would need:

```python
import os
import locale
import modal
from agents.preprocessor import Preprocessor
from dotenv import load_dotenv

load_dotenv(override=True)
```

### 🔐 Getting Authentication Working

Next, I opened the terminal and configured my **Modal API credentials**.

This is where I ran into my first real problem.

The Modal CLI created the authentication token file, `.modal.toml`, inside my Windows user profile directory. However, the virtual environment I was using for the lab couldn't properly detect that file.

I tried setting environment variables and even rebooting the system, but the authentication errors continued.

Eventually, I moved the `.modal.toml` token file into the folder where I was actually working on the lab.

And suddenly… it worked. 😂

It was a small issue, but it was a good reminder that deployment and cloud development isn't always about the code itself. Sometimes the hardest bugs are just **environment and configuration problems**.

---

## 🌍 Running Python on a Remote Machine

Once authentication was working, I wrote a very small Modal application to understand the most basic concept:

**Run Python code locally vs. run it remotely.**

I created a simple function that makes a request to `ipinfo.io` and returns the location of the machine running the code.

The interesting part was that Modal let me package the function together with its environment:

```python
app = modal.App("hello")
image = modal.Image.debian_slim().pip_install("requests")

@app.function(image=image)
def hello():
    ...
```

The `Image.debian_slim()` part gives Modal a lightweight Linux environment, while `pip_install("requests")` installs the dependency that the function needs.

When I ran the code locally, I got:

**Bengaluru, Karnataka, IN 🇮🇳**

But when the same function ran remotely through Modal, I got:

**Columbus, Ohio, US 🇺🇸**

That was the moment the concept really clicked for me.

I wasn't just running a Python function on my own computer anymore.

I was telling Modal:

**“Here is my code, here are its dependencies — now run it somewhere else for me.”**

---

## 🌎 Choosing Where the Function Runs

I then discovered that Modal also allows me to **specify the region** where a function should run.

For example:

```python
@app.function(image=image, region="eu")
def hello_europe():
    ...
```

Instead of letting Modal choose the remote location, I requested a European region.

Interestingly, I got different locations on different runs:

🇧🇪 **Brussels, Brussels Capital, Belgium**

and later:

🇸🇪 **Gävle, Gävleborg, Sweden**

So even within a requested region, the actual machine running the function can vary.

That was a pretty simple experiment, but it gave me a much better understanding of what Modal is actually doing behind the scenes.

---

## 🎯 Today's Takeaway

Today wasn't about building anything complicated.

It was about understanding the **foundation of remote execution with Modal**:

**Local Python → Modal → Linux Container → Remote Compute**

I learned how to authenticate with Modal, define an execution environment, install dependencies, run Python remotely, and even influence the geographical region where the computation takes place.

And while today's experiment was just a tiny `hello()` function, this is the same basic idea that I can eventually use for something much more interesting:

🤖 **Deploying parts of my agentic AI system to the cloud.**

The next step is to start moving beyond these simple experiments and see how Modal can actually fit into the **deal-finding agent** I'm planning.

🎯 **Day 63 complete.**
