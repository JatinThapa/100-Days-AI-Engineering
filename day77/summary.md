# Day 77 — Understanding Structured Outputs & Constrained Decoding 🧠🔗

Today was another interesting day in my **#100DaysOfAI** journey. I've actually used **structured outputs** before, especially during my RAG experiments, but I realized that I had never really stopped to understand **what is actually happening under the hood**.

So today I went deeper into it.

### 🧩 What are Structured Outputs?

At a high level, structured outputs allow us to tell an LLM that its response needs to follow a **specific structure**, rather than simply returning free-form text.

A common way to define that structure in Python is with **Pydantic**:

```python
class Product(BaseModel):
    name: str
    price: float
    category: str
```

From this Python class, a **JSON Schema** can be generated describing exactly what the model's output should look like.

The interesting part is that the LLM isn't just being asked to *please* return valid JSON. The schema becomes part of the mechanism used to constrain the model's output, and the resulting JSON can then be parsed into the corresponding Pydantic object.

This makes working with LLM responses feel much more like working with a normal typed Python function.

### 🤯 The Part I Found Most Interesting

The really fascinating part was understanding **how constrained generation can happen at the token level**.

An LLM doesn't simply decide on one next word. During generation, it produces a probability distribution over the possible next tokens.

Conceptually, it looks something like:

**Possible tokens → probabilities → token selection**

Those probabilities are produced from the model's logits, commonly converted into probabilities using something like **softmax**.

Now imagine the model is generating JSON and reaches a point where certain tokens would make it impossible to continue producing output that conforms to the required schema.

This is where **inference-time constrained decoding** becomes interesting.

A constrained decoding mechanism can identify tokens that would violate the required structure and effectively remove them from consideration by assigning them a probability of **zero**.

So instead of:

> "Here are all the tokens the model could generate."

the generation process becomes closer to:

> "Here are the tokens the model could generate **that still keep the output valid according to the schema**."

That is a pretty powerful idea.

### 🔍 My Mental Model

After today's study, I think about structured outputs roughly like this:

**Pydantic Model**
↓
**JSON Schema**
↓
**Schema-aware generation constraints**
↓
**LLM generates tokens**
↓
**Invalid token choices are restricted**
↓
**Valid structured JSON**
↓
**Parsed into a Pydantic object**

What initially looks like the LLM simply becoming "better at JSON" is actually much more interesting. There can be an additional layer of **constraints around the generation process itself** that helps guarantee the required structure.

### 💡 Today's Takeaway

Today reminded me that using an AI API at a high level can hide a *lot* of interesting engineering underneath.

I've used structured outputs before by simply defining a Pydantic model and getting structured data back. But understanding the ideas behind **schemas, token probabilities, and constrained decoding** makes the feature feel much less like magic and much more like clever engineering.

The biggest thing I took away today:

> **Structured output isn't just asking an LLM to format its answer nicely — it's about constraining generation so the model stays within a defined structure.** 🧠

🎯 **Day 77 complete.**
