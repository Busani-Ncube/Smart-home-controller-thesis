## Day 1 — 28 May 2026
Today I set up Arduino IDE 2 and installed ESP32 board support by Espressif Systems. 
I installed the CH340G driver and successfully connected the ESP32-WROOM-32 via USB on COM port. 
I flashed the Blink sketch with pin 2 instead of LED_BUILTIN which is not defined on this board. 
I updated the GitHub README with the new hardware list and September 4 deadline. 
Tomorrow I will install PubSubClient and write the ESP32 temperature sensor sketch.

## Day 2 — 29 May 2026
Today I discovered the ESP-WROOM-32 uses a CP2102 chip requiring a different driver than CH340G.
I installed the CP210x driver from Silicon Labs and successfully connected on COM4.
I wrote the ESP32 internal temperature sensor sketch and got readings of 53.33°C in Serial Monitor.
WiFi connection was successful with the ESP32 obtaining IP address 172.20.10.13.

## Day 3 — 7 June 2026
Today I installed the Mosquitto MQTT broker add-on in Home Assistant via the Apps section.
I created a dedicated MQTT user with local access only for secure broker authentication.
I configured the MQTT integration in Home Assistant which auto-discovered the Mosquitto broker.
I installed MQTT Explorer on my laptop and successfully connected to homeassistant.local on port 1883.
The broker is live showing topics and system messages confirming full MQTT functionality.

## Day 4 — 8 June 2026
Today I updated the ESP32 sketch to publish temperature readings via MQTT to Home Assistant.
I used MQTT autodiscovery to automatically create the sensor entity in Home Assistant.
The ESP32 successfully connected to WiFi and MQTT broker publishing 53.33°C every 10 seconds.
The ESP32 Temperature entity appeared in Home Assistant under Devices & Services → MQTT.
I added the temperature sensor as a favourite entity on the Overview dashboard.

## Day 5 — 10 June 2026
Today I wired the HC-SR505 PIR sensor to the ESP32 on GPIO 14 using VCC, GND and OUT pins.
I troubleshot the sensor extensively — discovered it requires a 60 second warmup before detecting motion.
I wrote the PIR MQTT sketch using autodiscovery which automatically created a binary sensor entity in Home Assistant.
The PIR Motion Sensor entity state changes from Clear to Detected in real time when motion is detected.
I added both ESP32 Temperature and PIR Motion Sensor to the Overview dashboard confirming full MQTT pipeline working.
