from config import *
import paho.mqtt.client as mqtt
from main import *
import time
import json


client2 = mqtt.Client(protocol=mqtt.MQTTv311)

def on_connect(client, userdata, flags, rc):
    print("Result from connect: {}".format(mqtt.connack_string(rc)))


while True:
    client2.connect(host=broker, port=port, keepalive=keepalive)

    client2.publish("esp/led", message_json)
    time.sleep(1)
