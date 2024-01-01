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

![ELRS Pico Receiver](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/c6fe0ac9-0438-4121-bc42-f2b662a814d6)

## BOM

Waveshare RP2040 Zero. Other types of RP2040 microprocessor boards can be used, but you will need to modify the include file with information that is specific to your board.

HappyModel EP2 receiver. Other types of ExpressLRS (ELRS) receivers can be used. EP2 is a good choice if a small size is required for your project.

ULN2003A transistor array. Functions as a switch with up to 0.5 amp maximum capacity.

17 x 13 hole circuit board, with typical 0.1-inch hole spacing.

Male header pins, which are typically used for RC servos.

[3D printed case](https://cad.onshape.com/documents/49e58140c1f2b9d9e9a1d4fe/w/d9ae141b1a74f2ec24c053d8/e/e737a1442b733880049387d5)

## Failsafe

I have asked of the ExpressLRS team to give the user the ability to adjust failsafe settings by using the ELRS [WebUI](https://www.expresslrs.org/hardware/pwm-receivers/?#channel-mapping-and-failsafe) function, which is already available in ELRS PWM receivers. If you would like the ability to easily adjust failsafe, then please add your comments to this [feature request](https://github.com/ExpressLRS/ExpressLRS/discussions/2514). 

Until the feature request has been implemented, you will need to adjusting failsafe using the procedure below.

The default failsafe values are found in the include file, `board_defs.h`.

If you would like different failsafe values, simply edit the include file, then build the new `firmware.uf2` file.

![image](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/a28e3b99-f194-4c22-b3fa-ff9a471b743c)


