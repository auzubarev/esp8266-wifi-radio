# Wifi Radio on ESP8266

Wifi Radio on ESP8266 microcontroller and I2S sound module on MAX98357A.
The project allows you to create a radio that can connect to a Wi-Fi network and play music streams over the internet.
The device includes a volume control and a button to switch between streams.


## Requirements

Before using this project, you will need the following components and software:
- ESP8266 board (Wemos D1 R2 or Wemos D1 mini)
- MAX98357A I2S module
- Button and potentiometer
- 10kΩ and 4.7Ω resistors
- Arduino IDE
- Wi-Fi network

## Device Schematic

![wifi radio schematic](scheme/radio.png?raw=true)

## Installation

1. Download and install Arduino IDE from https://www.arduino.cc/en/software
2. Install the driver for Wemos from https://www.wemos.cc/en/latest/ch340_driver.html
3. Add support for ESP8266 in Arduino IDE (File -> Preferences, enter the following in "Additional Board Manager URLs":
   http://arduino.esp8266.com/stable/package_esp8266com_index.json, then click OK).
4. Open the project, enter the ssid and password for the wifi.
5. Connect the board to the computer via USB.
6. Upload the program to the board.