#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <BH1750.h>
#include <Seeed_Arduino_SSCMA.h>

// WiFi and MQTT
const char* ssid = "Busani";
const char* password = "gemo8802";
const char* mqtt_server = "172.20.10.14";
const char* mqtt_user = "mqtt_user";
const char* mqtt_password = "mqtt1234";

// Pin definitions
#define PIR_PIN 14
#define RELAY1_PIN 26
#define RELAY2_PIN 27

// Internal temp sensor
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

// Objects
WiFiClient espClient;
PubSubClient client(espClient);
BH1750 lightMeter;
SSCMA AI;

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  String t = String(topic);
  
  if (t == "home/relay1/switch") {
    if (message == "ON") {
      digitalWrite(RELAY1_PIN, LOW);   // LOW = relay ON (active LOW)
      client.publish("home/relay1/state", "ON");
      Serial.println("Relay 1 ON - LED should light");
    } else {
      digitalWrite(RELAY1_PIN, HIGH);  // HIGH = relay OFF
      client.publish("home/relay1/state", "OFF");
      Serial.println("Relay 1 OFF - LED should turn off");
    }
  }
  
  if (t == "home/relay2/switch") {
    if (message == "ON") {
      digitalWrite(RELAY2_PIN, LOW);
      client.publish("home/relay2/state", "ON");
      Serial.println("Relay 2 ON");
    } else {
      digitalWrite(RELAY2_PIN, HIGH);
      client.publish("home/relay2/state", "OFF");
      Serial.println("Relay 2 OFF");
    }
  }
}

void publishDiscovery() {
  // Temperature
  client.publish("homeassistant/sensor/esp32temp/config",
    "{\"name\":\"ESP32 Temperature\",\"state_topic\":\"home/esp32/temperature\","
    "\"unit_of_measurement\":\"°C\",\"device_class\":\"temperature\"}", true);

  // PIR
  client.publish("homeassistant/binary_sensor/esp32pir/config",
    "{\"name\":\"PIR Motion Sensor\",\"state_topic\":\"home/esp32/pir\","
    "\"device_class\":\"motion\",\"payload_on\":\"ON\",\"payload_off\":\"OFF\"}", true);

  // Light
  client.publish("homeassistant/sensor/esp32light/config",
    "{\"name\":\"BH1750 Light Sensor\",\"state_topic\":\"home/esp32/light\","
    "\"unit_of_measurement\":\"lx\",\"device_class\":\"illuminance\"}", true);

  // Relay 1
  client.publish("homeassistant/switch/relay1/config",
    "{\"name\":\"Smart Relay 1\",\"command_topic\":\"home/relay1/switch\","
    "\"state_topic\":\"home/relay1/state\",\"payload_on\":\"ON\",\"payload_off\":\"OFF\"}", true);

  // Relay 2
  client.publish("homeassistant/switch/relay2/config",
    "{\"name\":\"Smart Relay 2\",\"command_topic\":\"home/relay2/switch\","
    "\"state_topic\":\"home/relay2/state\",\"payload_on\":\"ON\",\"payload_off\":\"OFF\"}", true);

  // Vision AI
  client.publish("homeassistant/binary_sensor/visionai/config",
    "{\"name\":\"Vision AI Person Detection\",\"state_topic\":\"home/esp32/vision\","
    "\"device_class\":\"occupancy\",\"payload_on\":\"ON\",\"payload_off\":\"OFF\"}", true);

  Serial.println("Autodiscovery published");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Combined", mqtt_user, mqtt_password)) {
      Serial.println("connected!");
      publishDiscovery();
      client.subscribe("home/relay1/switch");
      client.subscribe("home/relay2/switch");
    } else {
      Serial.print("failed rc=");
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
  Serial.println("\nWiFi connected!");
}

void setup() {
  Serial.begin(115200);
  
  // Relay setup
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  
  // PIR setup
  pinMode(PIR_PIN, INPUT);
  
  // BH1750 setup
  Wire.begin(21, 22);
  lightMeter.begin();
  
  // WiFi first
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  // Vision AI setup AFTER WiFi
  Wire1.begin(4, 5);
  Wire1.setClock(400000);
  delay(1000); // Give Vision AI time to boot
  bool aiOK = AI.begin(&Wire1, -1, 0x62, 10, 400000);
  Serial.println(aiOK ? "Vision AI OK" : "Vision AI FAILED");
  
  Serial.println("PIR warming up...");
  delay(60000);
  Serial.println("System ready!");
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // Temperature
  float tempF = temprature_sens_read();
  float tempC = (tempF - 32) / 1.8;
  char tempStr[8];
  dtostrf(tempC, 4, 2, tempStr);
  client.publish("home/esp32/temperature", tempStr);
  Serial.print("Temp: "); Serial.println(tempC);

  // PIR
  int motion = digitalRead(PIR_PIN);
  client.publish("home/esp32/pir", motion == HIGH ? "ON" : "OFF");
  Serial.println(motion == HIGH ? "Motion: ON" : "Motion: OFF");

  // Light
  float lux = lightMeter.readLightLevel();
  char luxStr[8];
  dtostrf(lux, 4, 2, luxStr);
  client.publish("home/esp32/light", luxStr);
  Serial.print("Light: "); Serial.println(lux);

// Vision AI
static unsigned long lastDetection = 0;
int aiResult = AI.invoke();

if (aiResult == 0) {
  bool personDetected = false;
  for (int i = 0; i < AI.boxes().size(); i++) {
    if (AI.boxes()[i].score > 60) {
      personDetected = true;
    }
  }
  if (personDetected) {
    lastDetection = millis();
    client.publish("home/esp32/vision", "ON", false);
    Serial.println("Vision AI: Person detected!");
  }
}

// Publish OFF if no detection for 5 seconds
if (millis() - lastDetection > 5000) {
  client.publish("home/esp32/vision", "OFF", false);
}

  delay(2000);
}