# SerialSmartRelay

**SerialSmartRelay** controls a smart relay via a serial interface (UART) using the A0 protocol. Thanks to the library's architecture, the code automatically adapts to different platforms (ESP32, ESP8266, Arduino).

## Supported devices

**ESP8266 ESP-01 WIFI Wireless with 1CH Relay Module Board**

<img src="images/esp-01_relay_x1_module.png" alt="Device preview" width="150">

**ESP8266 ESP-01 WIFI Wireless with 2CH Relay Module Board**

<img src="https://github.com/UDFSmart/Relay-Controller/blob/main/docs/images/x2/esp-01-relay-x2_preview.jpg" alt="Device preview" width="150">


## 🔌 Connection Diagram
To ensure proper communication, you must connect the TX/RX lines in a cross-over configuration.

## For ESP32-C3 / ESP32
The hardware Serial1 peripheral is used by default.
| Relay | ESP32-C3 (GPIO) | Notes |
| :--- | :--- | :--- |
| VCC | 5V / 3.3V | Depends on your relay model |
| GND | GND | Common ground |
| RX | GPIO 5 (TX) | Data transmission |
| TX | GPIO 4 (RX) | Data reception |

## For Arduino Uno / Nano / ESP8266
Uses SoftwareSerial to keep the primary Hardware Serial port free for debugging.
| Relay | Arduino Pin | Notes |
| :--- | :--- | :--- |
| RX | Pin 1 (TX) | For Hardware Serial usage |
| RX | Pin 3 (TX) | For Software Serial usage |
| TX | Pin 2 (RX) | For Software Serial usage |

## 🚀 How It Works
The example utilizes a factory function createRelayController(true), which performs the following:

  1. Initializes the data stream (Stream).
  2. Configures the serial port parameters (115200 baud).
  3. Instantiates the SerialRelayController object.

## Core Commands
The library encapsulates the A0 protocol. When you call setOn(0), the following byte packet is sent to the port:
```A0 00 01 A1``` (Open Channel 0).

## 🛠 Sketch Configuration
Before uploading, please verify the following parameters in the code:

  * **Type Selection:** Ensure that createRelayController(true) is called within setup().
  * **Pin Definitions:** If you are using non-standard pins, update the RELAY_RX and RELAY_TX macros.
  * **Baud Rate:** Most Chinese relay modules operate at 115200 baud. If the relay does not respond, try switching to 9600.

## 📋 Implementation Highlights
**Polymorphism:** The code interacts with the RelayController* pointer. You can swap a Serial relay for a standard GPIO relay by changing a single flag without modifying the logic in loop().

**Efficiency:** Channel states are cached in memory, allowing you to check the status via getState(i) instantly without overhead.

---

**Developed by** [UDFSOFT](https://udfsoft.com) _Copyright 2026 UDFOwner. Licensed under the Apache License 2.0._
