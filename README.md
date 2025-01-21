# Link-Analyzer-Firmware
- Created by Zach Lambert to read, write, and restore Megaman Link Navi chips.

# Arduino IDE
Install the Arduino IDE from the [official site](https://www.arduino.cc/en/software). This may also install the required driver.

# Driver
Windows
- Open the Device Manager without your Arduino connected.
- Look for “Ports (COM & LPT)”, and “Other devices”, and check if anything is there already.
- Connect your Arduino to the USB and see what appears in the Device Manager.
- If it says “COM[number]”, the correct driver is already installed.
- If it says “FT232R USB UART” without a COM number, install the [FTDI VCP driver](https://ftdichip.com/drivers/vcp-drivers/).
- If it says “USB2.0-serial” without a COM number, install the [CH340 driver](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all).

Mac
- Recent MacOS does not require a driver to be installed. You may need to adjust permissions for the serial port before apps can access it.
- If you are running MacOS 10.13 High Sierra or earlier, you may need to install a driver for CH340. Installing `CH34x_Install_V1.5.zip` from [this source](https://github.com/adrianmihalko/ch340g-ch34g-ch34x-mac-os-x-driver/) has been suggested.
- The FTDI link above also has Mac drivers for if your version of MacOS does not include one.

Linux
- Linux does not require a driver to be installed. You may need to adjust permissions for the serial port before apps can access it. Typically, there is a group which has access to serial ports, most often named `dialout`, but could be `uucp` or something else. Add your user account to the relevant group, then log out and in again.

# Flashing/Updating
- Download the lastest Arduino IDE from the [official site](https://www.arduino.cc/en/software)
- Download the latest firmware `Link-Analyzer-Firmware.ino` file from .
- Open the `Link-Analyzer-Firmware.ino` file in the Arduino IDE.
- In the “Tools” menu, set the “Board” option to “Arduino Nano”.
- Set the “Port” option to the serial port of your device. On Windows, this will have appeared in the Device Manager as described earlier.
- The correct “Processor” option might be either “ATmega328P” or “ATmega328P (Old Bootloader)”. We just have to guess.
- Click the “Upload” button and wait. If it was unsuccessful, select the other “Processor” option and try again.
![image](https://github.com/user-attachments/assets/256f5ebc-cfcb-41a3-9534-880efc523b79)
