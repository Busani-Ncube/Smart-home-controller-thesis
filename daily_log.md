## Day 1 — 27 May 2026
Today I set up Arduino IDE 2 and installed ESP32 board support by Espressif Systems. 
I installed the CH340G driver and successfully connected the ESP32-WROOM-32 via USB on COM port. 
I flashed the Blink sketch with pin 2 instead of LED_BUILTIN which is not defined on this board. 
I updated the GitHub README with the new hardware list and September 4 deadline. 
Tomorrow I will install PubSubClient and write the ESP32 temperature sensor sketch.