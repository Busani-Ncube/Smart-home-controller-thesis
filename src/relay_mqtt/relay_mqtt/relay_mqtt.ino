#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RELAY_PIN 0

const char* ssid = "Busani";
const char* password = "gemo8802";
const char* mqtt_server = "172.20.10.14";
const char* mqtt_user = "mqtt_user";
const char* mqtt_password = "mqtt1234";

WiFiClient espClient;
PubSubClient client(espClient);

void publishDiscovery() {
  String config = "{\"name\":\"Smart Relay\","
                  "\"command_topic\":\"home/relay/switch\","
                  "\"state_topic\":\"home/relay/state\","
                  "\"payload_on\":\"ON\","
                  "\"payload_off\":\"OFF\"}";
  client.publish("homeassistant/switch/relay1/config", config.c_str(), true);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  if (message == "ON") {
    digitalWrite(RELAY_PIN, LOW);
    client.publish("home/relay/state", "ON");
  } else if (message == "OFF") {
    digitalWrite(RELAY_PIN, HIGH);
    client.publish("home/relay/state", "OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP01Relay", mqtt_user, mqtt_password)) {
      Serial.println("connected!");
      publishDiscovery();
      client.subscribe("home/relay/switch");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}