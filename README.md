## CRServoF for RP2040 Pico

NOTE: This project is a work in progress for Raspberry Pi microprocessor RP2040 boards like the Pico. This project does not support other microprocessors.

NOTE: This project was performed using Visual Studio with Platform IO for Linux. If you are using the Windows version, then you will need to follow these instuctions to get this project to work with Visual Studio/Platform IO for Windows.

https://arduino-pico.readthedocs.io/en/latest/platformio.html#important-steps-for-windows-users-before-installing

If you don't want to bother with the recommended Windows configuration, then try the dual boot function of Linux Mint MATE. I did not like Linux Ubuntu, but I tried Linux Mint MATE and was hooked. Linux Mint MATE is easy and fast.

https://linuxmint-installation-guide.readthedocs.io/en/latest/

## Scope

CRServoF for RP2040 Pico is an RC receiver project for RC surface models that use ExpressLRS and EdgeTX.

This RC receiver has 6 PWM servo channels and 6 LED channels. EdgeTX will allow the user to customize how the LED channels can be used on the RC model

For example, the user can easily program, in EdgeTX, to have the headlights turn on with a button on the RC transmitter or have the headlights turn on automatically when the throttle is applied.

CRServoF for RP2040 Pico is a project partly from https://github.com/CapnBry/CRServoF, (which is ExpressLRS (ELRS) to servos for STM32 micros) and partly from https://github.com/mikeneiderhauser/CRSFJoystick, (which is ExpressLRS to USB video game dongle for RP2040 Pi Pico). The servo library comes from https://github.com/earlephilhower/arduino-pico .



![ELRS Surface Model Receiver](https://github.com/sk8board/CRServoF_for_RP2040_Pico/assets/96895142/b1e93c88-700e-4dc2-9b81-6335b5a790af)
