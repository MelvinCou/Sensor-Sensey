import requests
import time
from datetime import datetime
from influxdb_client import InfluxDBClient, Point, WriteOptions
import dotenv

INFLUXDB_URL = "http://localhost:8086"
INFLUXDB_ORG = "my_org"
INFLUXDB_BUCKET = "sensor_data"
INFLUXDB_TOKEN = dotenv.get_key(".env", "DOCKER_INFLUXDB_INIT_ADMIN_TOKEN")
print(INFLUXDB_TOKEN)

SENSOR_COMMUNITY_API_URL = "https://data.sensor.community/static/v2/data.json"
SENSOR_IDS = [94395, 94396]

COLLECTION_INTERVAL_SECONDS = 600 # CAREFUL : too frequent blocks IP !!


def get_sensor_data():
    try:
        print(f"{datetime.now()}: Getting data...")
        response = requests.get(SENSOR_COMMUNITY_API_URL, timeout=10)
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        print(f"Error fetching : {e}")
        return []


def process_sensor_record(record):
    sensor_id = str(record["sensor"]["id"])
    timestamp = record.get("timestamp")
    point = Point("sensor_community_data").tag("sensor_id", sensor_id)

    for value_entry in record.get("sensordatavalues", []):
        try:
            point.field(value_entry["value_type"], float(value_entry["value"]))
        except (ValueError, TypeError):
            print(f"  - Ignoring non numerical value {value_entry}")
    return point.time(timestamp) if point._fields else None


def collect_and_store():
    raw_data = get_sensor_data()
    if not raw_data:
        return

    with InfluxDBClient(url=INFLUXDB_URL, token=INFLUXDB_TOKEN, org=INFLUXDB_ORG) as client:
        write_api = client.write_api(
            write_options=WriteOptions(batch_size=1, flush_interval=1000))

        for sensor_id in SENSOR_IDS:
            for record in raw_data:
                if record.get("sensor", {}).get("id") == sensor_id:
                    point = process_sensor_record(record)
                    if point:
                        write_api.write(bucket=INFLUXDB_BUCKET, record=point)
                        print(f"  -> Data stored for sensor {sensor_id}")
                    break
            else:
                print(f"  -> Sensor {sensor_id} not found")


if __name__ == "__main__":
    print("Starting collection and storage...")
    try:
        while True:
            collect_and_store()
            time.sleep(COLLECTION_INTERVAL_SECONDS)
    except KeyboardInterrupt:
        print("\nExiting cleanly.")
