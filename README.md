\# Multi-Interface Smart Home Controller

\*\*Bachelor's Thesis — Computer Engineering \& Mechatronics\*\*

\*\*WSG University Bydgoszcz | Busani Ncube | 2026\*\*



\## Project Overview

A low-cost, multi-interface smart home automation system built on a Raspberry Pi 4B 

running Home Assistant OS. The system integrates multiple sensors, AI vision detection, 

and a local touchscreen interface — all managed through a unified MQTT communication layer.



\## Hardware

\- Raspberry Pi 4B (4GB RAM) — Central hub running Home Assistant OS

\- ESP32-WROOM-32 — Primary sensor node

\- Grove Vision AI V2 + Raspberry Pi Camera V2 — On-device person detection

\- HC-SR505 PIR Motion Sensor

\- BH1750 Ambient Light Sensor

\- 2-Channel Relay Module (JQC3F 05VDC)

\- Waveshare 4.3" HDMI Touchscreen



\## Features

\- Real-time temperature, motion, and light monitoring via MQTT

\- On-device AI person detection (no cloud dependency)

\- Physical device switching via relay module

\- 5 automations including context-aware lighting

\- Push notifications for alerts

\- Local touchscreen kiosk dashboard

\- Remote access via browser and mobile app

\- GVM network vulnerability assessment



\## Repository Structure

\- src/ — All Arduino sketches

\- media/ — Screenshots, photos, and demo videos

\- daily\_log.md — Development log



\## Supervisor

Professor Pólkowski — WSG University Bydgoszcz



\## GitHub

github.com/Busani-Ncube/Smart-home-controller-thesis

