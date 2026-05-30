#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "Busani’s iPhone";
const char* password = "gemo8802";

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read internal temperature
  float tempF = temprature_sens_read();
  float tempC = (tempF - 32) / 1.8;
  
  Serial.print("ESP32 Internal Temp: ");
  Serial.print(tempC);
  Serial.println(" °C");
  
  delay(2000);
}