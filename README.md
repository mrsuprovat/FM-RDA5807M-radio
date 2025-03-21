Advanced FM Radio with Arduino Nano, RDA5807M, LCD1602 I2C, and TTP223 Touch Switches

Overview

This project is an advanced FM radio built using an Arduino Nano, an RDA5807M FM receiver module, an LCD1602 display with I2C, and four TTP223 touch switches. It allows users to tune into FM stations, save common Indian radio frequencies, and interact with the system using touch-based controls. The radio also features a signal strength indicator represented by a tower icon on the LCD display.

Features

FM Radio Reception: Uses the RDA5807M module to receive FM signals.

LCD Display: Shows current station, signal strength, and other relevant information.

Touch Controls:

CH_UP (D2) - Next station 

CH_DOWN (D3) - Previous station 

VOL_UP (D4) - Increase volume (Long press: Switch to next saved station)

VOL_DOWN (D5) - Decrease volume (Long press: Switch to previous saved station)

Preset Stations: Saves common Indian radio stations for easy switching.

Signal Strength Display: Shows network strength with a tower icon on the LCD.

Hardware Requirements

Arduino Nano

RDA5807M FM Receiver Module

LCD1602 with I2C

4x TTP223 Touch Switches (connected to D2, D3, D4, and D5)

Speaker with amplifier (optional)

Power supply (USB or battery)

Wires and breadboard for connections

Circuit Diagram

(Include a schematic diagram if possible)

Wiring Instructions

Component

Arduino Nano Pin

RDA5807M SDA

A4

RDA5807M SCL

A5

LCD1602 SDA

A4

LCD1602 SCL

A5

TTP223 CH_UP

D2

TTP223 CH_DOWN

D3

TTP223 VOL_UP

D4

TTP223 VOL_DOWN

D5

Software Requirements

Arduino IDE

Wire.h (for I2C communication)

LiquidCrystal_I2C.h (for LCD display)

RDA5807M library (for FM radio module control)

Installation & Setup

Install Arduino IDE (if not installed already)

Install required libraries:

Open Arduino IDE → Sketch → Include Library → Manage Libraries

Search and install Wire, LiquidCrystal_I2C, and RDA5807M

Upload Code:

Connect Arduino Nano to PC via USB

Open the provided .ino file

Select Board: Arduino Nano and correct COM Port

Click Upload

Assemble the hardware according to the wiring instructions

Power on and start tuning stations

Usage

Short Press CH_UP / CH_DOWN: Manually tune to the next/previous station.

Long Press CH_UP / CH_DOWN: Switch between saved radio stations.

Short Press VOL_UP / VOL_DOWN: Adjust the volume.

LCD Display: Shows station frequency, signal strength, and volume level.

Future Improvements

Add Bluetooth streaming functionality.

Implement a rotary encoder for manual tuning.

Store user-selected favorite stations in EEPROM.

Integrate an RTC module to display current time.

License

This project is open-source under the MIT License. Feel free to modify and improve it!

Contributing

If you would like to contribute, fork the repository, create a new branch, make changes, and submit a pull request. Contributions are welcome!

Credits

This project is inspired by and utilizes the RDA5807M library from Mathertel's Radio GitHub Repository. Special thanks to Mathertel for providing an excellent radio library for Arduino projects.

Author

Suprovat Karar

Support

For any issues or suggestions, feel free to open an issue in the repository or contact me directly.
