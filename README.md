# PicoTempHumidMonitor — Raspberry Pi Pico 2 + Java Serial/TCP Bridge

A hardware/software integration project built for a university engineering course. A Raspberry Pi Pico 2 reads temperature and humidity from a Grove DHT11 sensor, activates a buzzer when the temperature exceeds a threshold, and communicates with Java applications over serial using a custom NAMO-style framed protocol. A Java server bridges serial messages to TCP clients.

**Demo videos**
- [Part 1 — hardware and communication demo](https://youtu.be/0w7GskAXqsA)
- [Part 2 — continued project demo](https://youtu.be/SYpWVrWdtz0)

## System overview

```text
Grove DHT11 + buzzer
        │
        ▼
Raspberry Pi Pico 2 firmware
  - DHT11 readings
  - temperature threshold
  - buzzer alert
  - framed serial messages
        │ USB serial (9600 baud; example port COM4)
        ▼
Java SerialCommunication
        │
        ▼
Java SerialServer ───── TCP port 9000 ───── Java SerialTcpClient
```

## Features documented in the original project

- Reads temperature and relative humidity from a DHT11 sensor.
- Uses a configurable firmware threshold (`tempThreshold`, initially 22.0 °C).
- Activates the buzzer briefly when temperature exceeds the threshold.
- Sends temperature, humidity, and threshold-related messages over serial.
- Uses a length-prefixed message format: 4-byte key length, 4-byte value length, key bytes, value bytes, then a one-byte message type.
- Java serial layer supports message subscriptions, background read/write threads, queued outgoing messages, and reconnection attempts.
- Java TCP server broadcasts received serial messages to connected clients and uses heartbeat messages.
- Java TCP client supports text/binary commands, listeners, heartbeat handling, and reconnect attempts.

## Hardware

The accompanying course report describes:
- Raspberry Pi Pico 2
- Seeed Studio Grove Shield for Raspberry Pi Pico
- Grove DHT11 sensor on digital pin D16
- Grove buzzer on digital pin D18

The report describes the Pico serial connection using 9600 baud, example Windows serial port COM4, and TCP port 9000. Port names vary by machine.

## Repository layout

```text
.
├── README.md
├── .gitignore
├── firmware/
│   └── PicoTempHumidMonitor.ino
├── protocol/
│   └── namo_serial_proto.h
├── java-server/
│   ├── SerialCommunication.java
│   └── SerialServer.java
├── java-client/
│   └── SerialTcpClient.java
└── docs/
    └── ProjectDemoVideosLink.txt
```

## Build and run notes

### Firmware

1. Install Arduino IDE and support for the Raspberry Pi Pico 2 board.
2. Install a compatible DHT sensor library.
3. Add `protocol/namo_serial_proto.h` to the firmware project's include path (or the Arduino library location as appropriate).
4. Check the firmware against your installed board package and libraries before compiling. Confirm all pin definitions and protocol callbacks.
5. Select the correct Pico 2 board and serial port, then upload the sketch.

### Java

The Java sources depend on **jSerialComm 2.11.0**. Obtain the dependency from its official project/release source and place the JAR in a local `lib/` folder; the JAR is not included in this repository package.

Use a recent JDK. From the repository root, example Windows PowerShell commands are:

```powershell
New-Item -ItemType Directory -Force out | Out-Null
javac -cp "lib/jSerialComm-2.11.0.jar" -d out java-server/SerialCommunication.java java-server/SerialServer.java
javac -cp "lib/jSerialComm-2.11.0.jar;out" -d out java-client/SerialTcpClient.java
```

Run the server with your actual serial port, baud rate and line configuration, for example:

```powershell
java -cp "out;lib/jSerialComm-2.11.0.jar" SerialServer 9000 COM4 9600 8N1
```

The client source's `main` currently expects three arguments (`server_host`, `server_port`, and serial port name). Check the source and run configuration before starting it. The project was originally demonstrated in a particular Windows/COM-port setup; these commands are starting points, not a guarantee that the recovered code compiles unchanged on every system.

## Known review items

This repository preserves recovered course-project source files for documentation and review. It has **not** been represented as a clean, production-ready or currently verified build.

Before claiming a fresh successful build, review at least these items:
- The firmware calls `pinMode(SPEAKER_PIN, OUTPUT)`, but the recovered sketch does not define `SPEAKER_PIN`.
- The firmware uses `serialProto.begin(onMessageReceived)`; verify the callback declaration and compile behaviour with your installed Arduino toolchain.
- Confirm the NAMO message framing and Java/Pico implementations agree on message lengths, byte order and type values.
- The Java sources contain broad exception handling and areas that merit testing, especially partial serial reads, reconnection and thread shutdown.
- The Java server and client should be tested together using the actual board and serial port.
- The original `compile.me` uses a colon-separated classpath, which is typical on Unix-like systems; Windows classpaths use semicolons.

## Academic work and attribution

This began as a group university project. Confirm your course's rules allow public release before publishing. Credit your teammate and the course/instructor where appropriate, and do not publish student IDs or other private information from the original report. The full report is intentionally not included in this starter package.

## License

No license has been selected. Until a suitable license is added and any course restrictions are checked, visitors should not assume they have permission to reuse or redistribute this code.
