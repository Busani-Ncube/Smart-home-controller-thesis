#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Busani";
const char* password = "gemo8802";
const char* mqtt_server = "172.20.10.14";
const char* mqtt_user = "mqtt_user";
const char* mqtt_password = "mqtt1234";

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

WiFiClient espClient;
PubSubClient client(espClient);

void publishDiscovery() {
  String config = "{\"name\":\"ESP32 Temperature\","
                  "\"state_topic\":\"home/esp32/temperature\","
                  "\"unit_of_measurement\":\"°C\","
                  "\"device_class\":\"temperature\"}";
  client.publish("homeassistant/sensor/esp32temp/config", config.c_str(), true);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected!");
      publishDiscovery();
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
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback([](char* topic, byte* payload, unsigned int length){});
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float tempF = temprature_sens_read();
  float tempC = (tempF - 32) / 1.8;

  char tempStr[8];
  dtostrf(tempC, 4, 2, tempStr);

  client.publish("home/esp32/temperature", tempStr);

  Serial.print("Published temp: ");
  Serial.println(tempC);

  delay(10000);
}