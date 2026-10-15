# Raspberry Pi Pico 2 Temperature & Humidity Monitoring System

An embedded systems project built around the Raspberry Pi Pico 2 and a Grove DHT11 temperature and humidity sensor. The system monitors environmental conditions, uses a buzzer to provide temperature-based alerts, and integrates with a Java serial communication and TCP networking framework.

**Project demonstrations**

- [Watch Part 1 on YouTube](https://youtu.be/0w7GskAXqsA)
- [Watch Part 2 on YouTube](https://youtu.be/SYpWVrWdtz0)

## Project Overview

The goal of this project was to build a working embedded environmental monitoring system and integrate it with a software communication framework.

The microcontroller runs Arduino/C++ firmware to collect temperature and humidity readings from a DHT11 sensor. The application also implements buzzer behaviour based on temperature readings.

For communication with other software components, the project uses professor-provided Java serial communication and TCP client/server classes built around the NAMO serial communication protocol. I adapted the provided configuration values to match my hardware and project setup.

## Features

- **Temperature and humidity monitoring:** Read environmental measurements from a Grove DHT11 sensor.
- **Embedded firmware:** Implemented the application logic in Arduino/C++ for the Raspberry Pi Pico 2.
- **Temperature-based alerts:** Activate a buzzer according to the application's configured temperature threshold.
- **Serial communication integration:** Connect the microcontroller application to an existing Java serial communication framework.
- **TCP client/server integration:** Use the provided Java networking components to facilitate communication between serial hardware and network-connected applications.
- **Hardware integration and testing:** Configure the sensor and buzzer, integrate the components, and demonstrate the working system.

## Hardware

| Component | Purpose |
|---|---|
| Raspberry Pi Pico 2 | Main microcontroller |
| Grove DHT11 temperature and humidity sensor | Environmental measurements |
| Grove buzzer module | Audible temperature alerts |
| Grove Shield / compatible hardware connections | Peripheral integration and wiring |

### Pin Configuration

The original project configuration uses the following connections:

| Component | Pin |
|---|---|
| DHT11 sensor | D16 |
| Buzzer | D18 |

Confirm these pin assignments against your actual wiring and the recovered firmware before recreating the setup.

## Software and Technologies

- Arduino/C++
- Raspberry Pi Pico 2
- DHT11 sensor integration
- Serial communication
- Java
- TCP/IP networking
- NAMO serial communication protocol
- Git and GitHub

## System Architecture

The system consists of two main software layers.

### 1. Embedded application

The Raspberry Pi Pico 2 runs the Arduino/C++ firmware responsible for:

1. Initializing the sensor and required hardware.
2. Reading temperature and humidity measurements.
3. Evaluating temperature readings against the configured alert threshold.
4. Activating the buzzer according to the application's alert logic.
5. Communicating with the surrounding system as implemented in the firmware.

### 2. Java communication framework

The project also includes Java components for serial communication and TCP networking. These components provide a bridge between the serial-connected hardware and network clients.

The Java framework and NAMO protocol were provided by Professor Navid Mohammed at York University. I adapted the relevant configuration values for my project setup rather than claiming authorship of the original communication framework.

## My Contributions

Although this project was classified as a university group assignment, I independently implemented the working embedded application and prepared the project report.

My contributions included:

- Developing the Arduino/C++ firmware for the Raspberry Pi Pico 2.
- Implementing temperature and humidity monitoring using the DHT11 sensor.
- Implementing temperature-based buzzer behaviour.
- Integrating the sensor and buzzer with the microcontroller.
- Configuring the application to work with the provided communication framework.
- Testing the integrated hardware and software and documenting the results.
- Recording project demonstrations showing the system operating in practice.

I also received guidance from my professor on initializing the chipset and sensors.

## Acknowledgments and Third-Party Components

The Java serial communication classes, Java TCP client/server classes, and NAMO serial communication protocol were provided by Professor Navid Mohammed at York University.

These components were adapted for the project's hardware and configuration. They are acknowledged as professor-provided materials and are not claimed as my original implementations.

The professor permits redistribution under a restriction against proprietary commercial or industrial use. The included professor-provided materials remain subject to that restriction. Their inclusion does not grant permission for proprietary commercial or industrial use.

## Running the Project

Recreating the original project requires the appropriate hardware, software and configuration.

1. Set up the Raspberry Pi Pico 2 development environment with the required Arduino support.
2. Connect the DHT11 sensor and buzzer according to the project's pin configuration.
3. Open the recovered Arduino firmware in the development environment.
4. Verify the board settings, sensor initialization and pin assignments.
5. Upload the firmware to the Raspberry Pi Pico 2 and test the sensor readings and buzzer behaviour.
6. If reproducing the Java communication setup, configure the serial port, baud rate and TCP port to match your computer and hardware.
7. Run the Java communication components with their required dependencies and verify communication between the hardware and software layers.

The original setup used COM4 at 9600 baud and TCP port 9000. These are configuration values from the original environment and may need to be changed on another computer.

Refer to the source files and demonstration videos for additional implementation details.

## Future Improvements

Potential improvements include:

- Add structured logging for sensor readings and communication events.
- Improve error handling for sensor failures and serial disconnections.
- Add configurable temperature thresholds.
- Add automated tests for firmware logic and communication message handling.
- Build a dashboard to display historical environmental readings.
- Improve configuration management so hardware settings do not need to be edited directly in the source code.

## Project Context

This project demonstrates hands-on experience with embedded firmware, sensor integration, hardware testing, and integration with an existing Java networking framework.

It was developed as a university engineering project, with the original implementation and demonstration videos reflecting the work completed at that time.
