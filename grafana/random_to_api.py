import requests
import random
import time

API_URL = "https://api.sensor.community/v1/push-sensor-data/"
SENSOR_ID = "esp32-0000"
SOFTWARE_VERSION = "1"

def send_sensor_data(pin, values):
    headers = {
        "X-Sensor": SENSOR_ID,
        "X-Pin": str(pin),
        "Content-Type": "application/json"
    }
    payload = {
        "software_version": SOFTWARE_VERSION,
        "sensordatavalues": values
    }
    print(f"Sending data from pin {pin}: {payload}")
    try:
        response = requests.post(API_URL, json=payload, headers=headers)
        print(f"Response: {response.status_code} {response.text}")
    except requests.RequestException as e:
        print(f"Request failed: {e}")

def bmp280_values():
    return [
        {"value_type": "temperature", "value": f"{random.uniform(15, 35):.2f}"},
        {"value_type": "pressure", "value": f"{random.uniform(950, 1050):.2f}"},
        {"value_type": "altitude", "value": f"{random.uniform(0, 200):.2f}"}
    ]

def dust_sensor_values():
    return [
        {"value_type": "P1", "value": f"{random.uniform(5, 40):.2f}"},
        {"value_type": "P2", "value": f"{random.uniform(2, 20):.2f}"}
    ]

def sound_sensor_values():
    return [
        {"value_type": "volume", "value": f"{random.uniform(30, 90):.2f}"}
    ]

def run_forever(delay=2):
    try:
        while True:
            send_sensor_data(pin=3, values=bmp280_values())
            send_sensor_data(pin=7, values=dust_sensor_values())
            # send_sensor_data(pin=8, values=sound_sensor_values())
            time.sleep(delay)
    except KeyboardInterrupt:
        print("\nExiting cleanly.")

if __name__ == "__main__":
    run_forever()