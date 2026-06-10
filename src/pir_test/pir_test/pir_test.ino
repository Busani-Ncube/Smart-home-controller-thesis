#define PIR_PIN 14

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  Serial.println("PIR warming up...");
  delay(60000);
  Serial.println("Ready!");
}

void loop() {
  int motion = digitalRead(PIR_PIN);
  if (motion == HIGH) {
    Serial.println("Motion detected!");
  } else {
    Serial.println("No motion.");
  }
  delay(1000);
}