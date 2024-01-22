## CRServoF_ELRS_for_RP2040_Pico

NOTE: This project is a work in progress for Raspberry Pi microprocessor RP2040 boards like the Pico. This project does not support other microprocessors.  

NOTE: This is experimental software/hardware and there is no guarantee of stability or reliability. **USE AT YOUR OWN RISK**.

NOTE: This project was performed using Visual Studio with Platform IO for Linux. If you are using the Windows version, then you will need to [follow these instructions](https://arduino-pico.readthedocs.io/en/latest/platformio.html#important-steps-for-windows-users-before-installing) to get this project to work with Visual Studio/Platform IO for Windows.

If you don't want to bother with the recommended Windows configuration, then try the dual boot function of Linux Mint MATE. I did not like Linux Ubuntu, but after I tried Linux Mint MATE, I was hooked. [Linux Mint Mate](https://linuxmint-installation-guide.readthedocs.io/en/latest/) is easy and fast.

## Scope

CRServoF_ELRS_for_RP2040_Pico is an RC receiver project for RC surface models and STEM robots that use ExpressLRS and EdgeTX.

This RC receiver has 6 PWM servo channels and 6 duty cycle LED channels. EdgeTX will allow the user to customize how the LED channels can be used on the RC model

For example, the user can easily program, in EdgeTX, to have the headlights turn on with a button on the RC transmitter or have the headlights turn on automatically when the throttle is applied.

Another example is the duty cycle pins could be connected to a high current relay (duty cycle 0% "Off" and 100% "On") that would be used on a STEM robot. The versatility of EdgeTX (RC transmitter software) and ELRS make this an ideal receiver for STEM robots.

[Here are RC transmitters](https://www.radiomasterrc.com/collections/transmitter) that work with ExpressLRS (ELRS).

CRServoF_ELRS_for_RP2040_Pico has a portion from https://github.com/CapnBry/CRServoF, (which is ExpressLRS (ELRS) to servos for STM32 micros) and another portion from https://github.com/mikeneiderhauser/CRSFJoystick, (which is ExpressLRS to USB video game dongle for RP2040 Pi Pico).

![ELRS Pico Receiver](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/c6fe0ac9-0438-4121-bc42-f2b662a814d6)

## Firmware

NOTE: This is experimental software/hardware and there is no guarantee of stability or reliability. **USE AT YOUR OWN RISK**.

If you want to use this software in the current state without compiling, then the `firmware.uf2` files can be found here for [Pi Pico](.pio/build/pico),  [Pi Pico W](.pio/build/pico_w),  [Seeed XAIO RP2040](.pio/build/seeedxaio2040),  [Tiny 2040](.pio/build/tiny2040), and  [Waveshare RP2040-Zero](.pio/build/wavesharerp2040zero).

## BOM

Waveshare RP2040 Zero. Other types of RP2040 microprocessor boards can be used. Please reference the Board Pinout section below for your board.

HappyModel EP2 receiver or other brand of nano ExpressLRS (ELRS) receiver.

ULN2003A transistor array. Functions as a switch with up to 0.5 amp maximum capacity.

17 x 13 hole circuit board, with typical 0.1-inch hole spacing.

Male header pins, which are typically used for RC servos.

[3D printed case](https://cad.onshape.com/documents/49e58140c1f2b9d9e9a1d4fe/w/d9ae141b1a74f2ec24c053d8/e/e737a1442b733880049387d5)

## Failsafe

I have asked for support from the ExpressLRS team to give the end user the ability to adjust failsafe settings by using the ELRS [WebUI](https://www.expresslrs.org/hardware/pwm-receivers/?#channel-mapping-and-failsafe) function, which is already available in ELRS PWM receivers. If you would like the ability to easily adjust failsafe, then please add your comments to this [feature request](https://github.com/ExpressLRS/ExpressLRS/discussions/2514). 

Until the feature request has been implemented, you will need to adjusting failsafe using the procedure below.

The default failsafe values are found in the include file, `board_defs.h`.

If you would like different failsafe values, simply edit the include file, then build the new `firmware.uf2` file.

![image](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/6bf2b9e2-0c16-41be-bff7-eeb552a1f49d)


## Board Pinout

PWM pins and UART pins are defined in the include file, `board_defs.h`. 

For example, for the Pi Pico, the pins are defined as the values shown in the red boxes below.

![image](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/5a16e7aa-889e-49ec-bfcc-44d75272b38d)

![image](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/914288ab-c057-4510-b180-132461d0ef29)

![image](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/ffe2c00c-5067-41ee-b1b6-32c7f1924cea)

![image](https://github.com/sk8board/CRServoF_ELRS_for_RP2040_Pico/assets/96895142/36ba0081-64e7-4d3e-875d-375b00ba872d)


