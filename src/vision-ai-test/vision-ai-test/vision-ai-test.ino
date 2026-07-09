#include <Wire.h>
#include <Seeed_Arduino_SSCMA.h>

SSCMA AI;

void setup() {
  Serial.begin(115200);
  Wire1.begin(4, 5);
  Wire1.setClock(400000); // Fast mode 400kHz
  AI.begin(&Wire1, -1, 0x62, 10, 400000); // address 0x62, 10ms wait, 400kHz
  Serial.println("Grove Vision AI V2 ready!");
  delay(2000); // Give Vision AI time to warm up
}

void loop() {
  int result = AI.invoke();
  Serial.print("Invoke result: ");
  Serial.println(result);
  
  if (!result) {
    Serial.println("Invoke success!");
    for (int i = 0; i < AI.boxes().size(); i++) {
      Serial.print("Person detected! Score: ");
      Serial.println(AI.boxes()[i].score);
    }
    if (AI.boxes().size() == 0) {
      Serial.println("No objects detected");
    }
  }
  delay(1000);
}