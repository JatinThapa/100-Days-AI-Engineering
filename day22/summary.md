# Day 22 — CareSyncAI Deployment, Production Debugging & TURN Server Setup

Today was a major practical engineering day focused on deploying our hackathon project, **CareSyncAI**, and making sure it worked properly in a real production environment.

## Cloud Deployment

I deployed the complete project on an **AMD Developer Cloud GPU droplet**.

The deployment involved:

* Creating and configuring the droplet
* Connecting through SSH
* Cloning the project from a private GitHub repository
* Configuring production environment variables
* Building and starting all services with Docker Compose
* Connecting the application to `caresyncai.duckdns.org`
* Configuring Nginx as the reverse proxy
* Enabling HTTPS using Let’s Encrypt certificates

The production stack included:

* Next.js frontend
* FastAPI backend
* PostgreSQL
* Redis
* Celery worker
* Ollama
* Qdrant
* Nginx
* Prometheus
* Grafana
* Coturn

## Registration Bug

After deployment, user registration started failing with a `404 Not Found`.

The backend, database and public API route were tested separately and were all working correctly.

The actual problem was that the frontend was calling:

```text
/api/api/auth/register
```

instead of:

```text
/api/auth/register
```

The frontend base URL already included `/api`, while the request path also added `/api`.

I fixed the production environment variable, rebuilt the Next.js frontend and successfully restored registration and authorization.

## Celery and AI Report Generation

I inspected the Celery logs to understand which AI model generated consultation reports.

The logs showed:

* Gemini successfully received requests
* One Gemini response contained malformed JSON
* The system attempted to fall back to Ollama
* Ollama was running but did not have a model installed
* A second Celery task successfully generated the report using Gemini

I then:

* Passed `AI_PROVIDER`, `AI_MODEL` and `OLLAMA_FALLBACK_MODEL` into the Celery container
* Recreated the Celery worker
* Installed `llama3.2:latest` inside the Ollama container
* Verified that Gemini remained the primary provider and Ollama was available as the fallback

## GitHub and Deployment Configuration

I committed the safe production configuration changes to the private repository, including:

* Celery AI provider environment mappings
* Updated Docker Compose configuration
* Improved `.gitignore`

I also made sure not to commit:

* `.env`
* API keys
* TURN credentials
* HTTPS certificates
* private keys

I later prepared the project files for the official hackathon repository and began following the team’s planned commit strategy.

## Cross-Network WebRTC Problem

Video consultations worked between my laptop and phone, but initially failed when my friend joined from a different network.

The reason was that the application only used STUN servers.

STUN can help establish a direct peer-to-peer WebRTC connection, but some routers, mobile networks and strict NAT configurations prevent that direct connection.

To solve this, I deployed a **Coturn TURN server**.

The setup included:

* Opening TCP and UDP port `3478`
* Opening UDP relay ports `49160–49200`
* Creating TURN authentication credentials
* Adding Coturn to Docker Compose
* Running Coturn with host networking
* Testing TURN allocation from the server
* Testing TURN externally using Trickle ICE
* Confirming successful relay candidates over both UDP and TCP

I then added the TURN configuration to the frontend WebRTC hook using build-time environment variables, rebuilt the frontend container and redeployed it.

## Final Result

After the TURN integration, my friend and I successfully joined the same consultation room from different networks.

We could:

* See each other clearly
* Hear each other
* Use the consultation room without connection failures
* Generate AI consultation reports successfully

## Key Learnings

Today helped me understand that deploying an AI application is much more than starting a model.

It involves:

* Cloud infrastructure
* Docker networking
* Reverse proxies
* HTTPS
* Environment variables
* Background workers
* Database connectivity
* AI-provider fallbacks
* WebRTC signaling
* STUN and TURN servers
* Production debugging
* Git security practices

The biggest lesson was:

> A feature working locally or on the same network does not always mean it will work reliably for real users across the internet.

**Day 22 complete — CareSyncAI successfully deployed and working across different networks.** 🚀
