/* Description: 
 * It receive data from published in json format.
 * We use ArduinoJson library for deserialize message.
 * Author: Md. Kamruzzaman Tipu
 * Contact: it.ktipu@gmail.com
 */



#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#define LED 2 



const char* ssid = "NybSys_IoT";
const char* password =  "NYBSYS@I0T";
const char* mqttServer = "192.168.1.102";
const int mqttPort = 1883;
 
WiFiClient espClient;
PubSubClient client(espClient);
StaticJsonDocument<256> doc;

const char *dashboard_sub_topic = "esp32/device1/#";
const char *dashboard_pub_topic = "";
const char *dashboard_command_for_led_topic = "esp32/device1/light";
 
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  deserializeJson(doc, message, length); 
  String receive_msg_topic = doc["topic"];

  if(doc["topic"]==dashboard_command_for_led_topic){
    if(doc["light1"]== "1") {
      Serial.println("Turning led on");
      digitalWrite(LED,HIGH);
    }
    else {
      Serial.println("Turning led off");
      digitalWrite(LED, LOW);
    }
  }
}
 
void setup() {
 
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.subscribe(dashboard_sub_topic);
 
}
//void led(){
//  
//}
 
void loop() {
  client.loop();
}
