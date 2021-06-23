from config import *
import paho.mqtt.client as mqtt
import json
import multiprocessing
from multiprocessing import Manager, Value, Queue, Pipe
import time


client = mqtt.Client("client-socks", transport='websockets')
message = dict()

dashboard_to_esp32_client_sub_topic = "esp32/#"
dashboard_to_esp32_client_pub_topic = "esp32/device1"
dashboard_sub_topic = "house/#"



def on_connect(client, userdata, flags, rc):
    print("Result from connect: {}".format(mqtt.connack_string(rc)))
    client.subscribe(dashboard_to_esp32_client_sub_topic)
    client.subscribe(dashboard_sub_topic)


def on_subscribe(client, userdata, mid, granted_qos):
    print("I've subscribe with QoS: {}".format(granted_qos[0]))


def on_message(client, userdata, msg):
    topic = msg.topic
    decode_msg = str(msg.payload.decode("utf-8", "ignore"))
    print("Topic: ", topic)
    print("Message: ", decode_msg)

    message["topic"] = topic
    message["payload"] = decode_msg
    json_message = json.dumps(message)

    if topic == dashboard_to_esp32_client_sub_topic:
        client.publish(dashboard_to_esp32_client_pub_topic, json_message)
    elif topic == "esp":
        client.publish("house/light/left", decode_msg)


client.on_connect = on_connect
client.on_subscribe = on_subscribe
client.on_message = on_message
client.connect(host=mqtt_server_host, port=mqtt_server_port, keepalive=mqtt_keepalive)

while True:
    client.loop_forever()
    time.sleep(3)


