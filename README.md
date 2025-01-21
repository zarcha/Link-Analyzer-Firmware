# Link-Analyzer-Firmware
- Created by Zach Lambert to read, write, and restore Megaman Link Navi chips.

# Flashing/Updating
- Download the lastest Arduino IDE from: https://www.arduino.cc/en/software
- Download the latest firmware `Link-Analyzer-Firmware.ino` file from .
- Open the `Link-Analyzer-Firmware.ino` file in the Arduino IDE.
- In the “Tools” menu, set the “Board” option to “Arduino Nano”.
- Set the “Port” option to the serial port of your device. On Windows, this will have appeared in the Device Manager as described earlier.
- The correct “Processor” option might be either “ATmega328P” or “ATmega328P (Old Bootloader)”. We just have to guess.
- Click the “Upload” button and wait. If it was unsuccessful, select the other “Processor” option and try again.
![image](https://github.com/user-attachments/assets/256f5ebc-cfcb-41a3-9534-880efc523b79)
