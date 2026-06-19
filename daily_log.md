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

## Day 6 — 11 June 2026
Today I attempted to integrate the relay module (SRD-03VDC-SL-C) with the ESP32.
I discovered the relay provided is an ESP-01 relay board requiring the ESP-01S module and USB-to-TTL adapter to program.
I researched the board extensively and confirmed it uses GPIO0 of the ESP-01S to trigger the relay via active LOW signal.
I installed ESP8266 board support in Arduino IDE and prepared the MQTT relay sketch for the ESP-01S.
The relay integration is pending — I will request a standard 5V relay module (SRD-05VDC-SL-C) to connect directly to ESP32 GPIO for a cleaner architecture.

## Day 7 — 12 June 2026
Today I combined the temperature and PIR sensor sketches into one unified ESP32 sketch.
Both sensors are now publishing simultaneously to Home Assistant via MQTT autodiscovery.
I confirmed ESP32 Temperature and PIR Motion Sensor entities both show live data on the HA dashboard at the same time.
I organised all project photos and screenshots into the media folder and cleaned up the repository.

## Day 8 — 13 June 2026
Today I confirmed the Waveshare 4.3" HDMI touchscreen is connected and working with the Raspberry Pi.
I installed the HAOS Kiosk Display community add-on to launch a browser dashboard on the touchscreen.
The HA Overview dashboard successfully displayed on the Waveshare screen in kiosk mode.
Touch input was confirmed working — scrolling and basic navigation functional on the touchscreen.
The kiosk add-on is set to manual start only to avoid interfering with normal HA operation.

## Day 9 — 13 June 2026
Today I confirmed all ESP32 sensors are successfully connected to the Raspberry Pi Home Assistant instance.
The Mosquitto MQTT broker on the Pi is receiving data from the ESP32 reliably.
ESP32 Temperature and PIR Motion Sensor entities are both showing live data in Home Assistant.
All MQTT autodiscovery configurations are working correctly on the Pi HA instance.
Relay entity integration is pending arrival of standard 5V relay module to connect directly to ESP32 GPIO.

## Day 10 — 13 June 2026
Today I completed the Waveshare 4.3" touchscreen configuration with Home Assistant in kiosk mode.
The HAOS Kiosk Display add-on successfully launches the HA dashboard fullscreen on the Waveshare screen.
Touch input is working — scrolling and tapping confirmed functional on the touchscreen display.
I recorded a video demonstration of the touchscreen dashboard for thesis evidence in Chapter 4.2.
The kiosk add-on is manually started to avoid interfering with normal HA browser access.

## Day 11 — 13 June 2026
Today I built a professional Lovelace dashboard called Smart Home Controller in Home Assistant.
The dashboard includes a temperature gauge, PIR motion sensor entity, 24-hour temperature history graph, weather forecast and clock cards.
I tested the dashboard from my phone browser confirming remote access works correctly at 172.20.10.14:8123.
Push notifications were enabled on the phone for future automation alerts.
Screenshots of the dashboard from both laptop and phone were taken for thesis evidence in Chapter 4

## Day 12 — 15 June 2026
Today I built two working automations in Home Assistant using the Automations and Scenes editor.
The Temperature Alert automation triggers a push notification to my phone when ESP32 temperature crosses a set threshold.
The Motion Alert automation sends a push notification when the PIR sensor detects motion.
Both automations were tested successfully using the Run Actions feature and confirmed via live notifications on my phone.
The relay-dependent automations (motion-triggered relay and scheduled relay off) are pending the standard 5V relay module which I will collect from my lecturer next week.
Tomorrow I will run a full system test of Part 1 hardware and begin writing Chapter 1 of the thesis in parallel.

