## CRServoF_ELRS_for_RP2040_Pico

NOTE: This project is a work in progress for Raspberry Pi microprocessor RP2040 boards like the Pico. This project does not support other microprocessors.

NOTE: This project was performed using Visual Studio with Platform IO for Linux. If you are using the Windows version, then you will need to [follow these instructions](https://arduino-pico.readthedocs.io/en/latest/platformio.html#important-steps-for-windows-users-before-installing) to get this project to work with Visual Studio/Platform IO for Windows.

If you don't want to bother with the recommended Windows configuration, then try the dual boot function of Linux Mint MATE. I did not like Linux Ubuntu, but I tried Linux Mint MATE and was hooked. [Linux Mint Mate](https://linuxmint-installation-guide.readthedocs.io/en/latest/) is easy and fast.

## Scope

CRServoF_ELRS_for_RP2040_Pico is an RC receiver project for RC surface models and STEM robots that use ExpressLRS and EdgeTX.

This RC receiver has 6 PWM servo channels and 6 LED channels. EdgeTX will allow the user to customize how the LED channels can be used on the RC model

For example, the user can easily program, in EdgeTX, to have the headlights turn on with a button on the RC transmitter or have the headlights turn on automatically when the throttle is applied.

Another example is the LED pins can be used for more than controlling LED's. The LED pins could be connected to a high current relay that would be used on a STEM robot. The versatility of EdgeTX (RC transmitter software) and the stable radio link of ELRS makes this receiver one of the best choices for STEM robots.

[Here are RC transmitters](https://www.radiomasterrc.com/collections/transmitter) that work with ExpressLRS (ELRS).

CRServoF_ELRS_for_RP2040_Pico has a portion from https://github.com/CapnBry/CRServoF, (which is ExpressLRS (ELRS) to servos for STM32 micros) and another portion from https://github.com/mikeneiderhauser/CRSFJoystick, (which is ExpressLRS to USB video game dongle for RP2040 Pi Pico). The servo library comes from https://github.com/earlephilhower/arduino-pico .



![ELRS Surface Model Receiver](https://github.com/sk8board/CRServoF_for_RP2040_Pico/assets/96895142/b1e93c88-700e-4dc2-9b81-6335b5a790af)

## BOM

Waveshare RP2040 Zero. Other types of RP2040 microprocessor boards can be used, but you will need to modify the include file with information that is specific to your board.

HappyModel EP2 receiver. Other types of ExpressLRS (ELRS) receivers can be used. EP2 is a good choice if a small size is required for your project.

ULN2003A transistor array. Functions as a switch with up to 0.5 amp maximum capacity.

16 x 13 hole circuit board, with typical 0.1-inch hole spacing.

Male header pins, which are typically used for RC servos.
