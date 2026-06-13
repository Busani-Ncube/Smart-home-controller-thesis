#include <WiFi.h>
#include <PubSubClient.h>

#define PIR_PIN 14

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
  // Temperature sensor
  String tempConfig = "{\"name\":\"ESP32 Temperature\","
                      "\"state_topic\":\"home/esp32/temperature\","
                      "\"unit_of_measurement\":\"°C\","
                      "\"device_class\":\"temperature\"}";
  client.publish("homeassistant/sensor/esp32temp/config", tempConfig.c_str(), true);

  // PIR sensor
  String pirConfig = "{\"name\":\"PIR Motion Sensor\","
                     "\"state_topic\":\"home/esp32/pir\","
                     "\"device_class\":\"motion\","
                     "\"payload_on\":\"ON\","
                     "\"payload_off\":\"OFF\"}";
  client.publish("homeassistant/binary_sensor/esp32pir/config", pirConfig.c_str(), true);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Combined", mqtt_user, mqtt_password)) {
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
  Serial.println("WiFi connected!");
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback([](char* topic, byte* payload, unsigned int length){});
  Serial.println("PIR warming up...");
  delay(60000);
  Serial.println("Ready!");
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // Read and publish temperature
  float tempF = temprature_sens_read();
  float tempC = (tempF - 32) / 1.8;
  char tempStr[8];
  dtostrf(tempC, 4, 2, tempStr);
  client.publish("home/esp32/temperature", tempStr);
  Serial.print("Temp: ");
  Serial.println(tempC);

  // Read and publish PIR
  int motion = digitalRead(PIR_PIN);
  if (motion == HIGH) {
    client.publish("home/esp32/pir", "ON");
    Serial.println("Motion: ON");
  } else {
    client.publish("home/esp32/pir", "OFF");
    Serial.println("Motion: OFF");
  }

  delay(1000);
}