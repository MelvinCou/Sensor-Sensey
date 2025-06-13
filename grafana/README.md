> **_Make sure you cd to grafana folder first._**

# SETUP

### Credentials

- Create copy of .env.example, rename it .env, open it and replace values with your own credentials

- Create copy of dashboards/datasources/influxdb.yml.example (in same folder), rename it influxdb.yml, open it and replace values with your own credentials

### Python environnment

**Create venv**

```bash
py -m venv venv
```

**Activate venv**

```bash
source venv/bin/activate
```

**Install requirements**

```bash
pip install -r requirements.txt
```

# HOW TO USE

**1. First, launch Grafana and InfluxDB :**

```bash
docker compose up
```

**2. Then, launch script to get data from sensorcommunity API and write it to InfluxDB :**

```bash
py api_to_influx.py
```

**3. Optionnally, if you have no real data available, launch script to produce random data and push it to sensorcommunity API, so api_to_influx.py is able to get it back :**

```bash
py random_to_api.py
```

**You can then open Grafana at http://localhost:3000/dashboards. Dashboard should load automatically.**
