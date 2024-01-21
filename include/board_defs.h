#include "pico.h"

#ifndef BOARD_DEFS
#define BOARD_DEFS

#define LED_TYPE_SINGLE 1
#define LED_TYPE_NEOPIXEL 2
#define LED_TYPE_RGB 3

// Channel_Function_Enable
#define Channel_Set_To_Off 0
#define Channel_Set_To_PWM 1
#define Channel_Set_To_DutyCycle 2

#define Servo_Min_us 1000
#define Servo_Max_us 2000

// Failsafe values, 1000 to 2000
uint16_t Failsafe_Channel_Value [16] = {
1500,    // Channel 1 Failsafe value           
1500,    // Channel 2 Failsafe value                 
1500,    // Channel 3 Failsafe value                
1500,    // Channel 4 Failsafe value                 
1500,    // Channel 5 Failsafe value                 
1500,    // Channel 6 Failsafe value                 
1500,    // Channel 7 Failsafe value                 
1500,    // Channel 8 Failsafe value                 
1500,    // Channel 9 Failsafe value                  
1500,    // Channel 10 Failsafe value                 
1500,    // Channel 11 Failsafe value                
1500,    // Channel 12 Failsafe value  
1500,    // Channel 13 Failsafe value                 
1500,    // Channel 14 Failsafe value                
1500,    // Channel 15 Failsafe value   
1500    // Channel 16 Failsafe value   
};            

// PiPico
#if BOARD_ID == 1
    #define UART_SELECT Serial2
    #define CRSF_TX 4  // physical 6 (UART1 == Serial2)
    #define CRSF_RX 5  // physical 7 (UART1 == Serial2)

    #define LED_TYPE LED_TYPE_SINGLE
    #define LED_PIN 25
    
    #define Duty_Cycle_Invert 0  // 1 enables inverting the duty cycle signal

    // Set channel function (off, PWM, or Duty Cycle) and GPIO pin number below
    #define Number_of_Channel_Outputs 12  // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_Config_Setting[Number_of_Channel_Outputs] = {
      Channel_Set_To_PWM, // Channel 1 config setting
      Channel_Set_To_PWM, // Channel 2 config setting
      Channel_Set_To_PWM, // Channel 3 config setting
      Channel_Set_To_PWM, // Channel 4 config setting
      Channel_Set_To_PWM, // Channel 5 config setting
      Channel_Set_To_PWM, // Channel 6 config setting
      Channel_Set_To_PWM, // Channel 7 config setting
      Channel_Set_To_PWM, // Channel 8 config setting
      Channel_Set_To_PWM, // Channel 9 config setting
      Channel_Set_To_PWM, // Channel 10 config setting
      Channel_Set_To_PWM, // Channel 11 config setting
      Channel_Set_To_PWM // Channel 12 config setting
    };

    // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_GPIO_Mapping[Number_of_Channel_Outputs] ={
      21, //GPIO 21, ELRS Channel 1
      20, //GPIO 20, ELRS Channel 2
      19, //GPIO 19, ELRS Channel 3
      18, //GPIO 18, ELRS Channel 4
      17, //GPIO 17, ELRS Channel 5
      16, //GPIO 16, ELRS Channel 6
      10, //GPIO 10, ELRS Channel 7
      11, //GPIO 11, ELRS Channel 8
      12, //GPIO 12, ELRS Channel 9
      13, //GPIO 13, ELRS Channel 10
      14, //GPIO 14, ELRS Channel 11
      15  //GPIO 15, ELRS Channel 12
    };

    void boardSetup() {
      pinMode(LED_PIN,OUTPUT);
    }

    void led_off() {
      digitalWrite(LED_PIN, LOW);
    }
    
    void led_on() {
      digitalWrite(LED_PIN, HIGH);
    }
#endif

// TINY2040
#if BOARD_ID == 2
    #define UART_SELECT Serial2
    #define CRSF_TX 4  // (UART1 == Serial2)
    #define CRSF_RX 5  // (UART1 == Serial2)

    #define LED_TYPE LED_TYPE_RGB
    #define LED_PIN_R 18
    #define LED_PIN_G 19
    #define LED_PIN_B 20
    
    #define Duty_Cycle_Invert 0  // 1 enables inverting the duty cycle signal

    // Set channel function (off, PWM, or Duty Cycle) and GPIO pin number below
    #define Number_of_Channel_Outputs 10  // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_Config_Setting[Number_of_Channel_Outputs] = {
      Channel_Set_To_PWM, // Channel 1 config setting
      Channel_Set_To_PWM, // Channel 2 config setting
      Channel_Set_To_PWM, // Channel 3 config setting
      Channel_Set_To_PWM, // Channel 4 config setting
      Channel_Set_To_PWM, // Channel 5 config setting
      Channel_Set_To_PWM, // Channel 6 config setting
      Channel_Set_To_PWM, // Channel 7 config setting
      Channel_Set_To_PWM, // Channel 8 config setting
      Channel_Set_To_PWM, // Channel 9 config setting
      Channel_Set_To_PWM, // Channel 10 config setting
    };

    // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_GPIO_Mapping[Number_of_Channel_Outputs] = {
      0, //GPIO 0, ELRS Channel 1
      1, //GPIO 1, ELRS Channel 2
      2, //GPIO 2, ELRS Channel 3
      3, //GPIO 3, ELRS Channel 4
      6, //GPIO 6, ELRS Channel 5
      7, //GPIO 7, ELRS Channel 6
      29, //GPIO 29, ELRS Channel 7
      28, //GPIO 28, ELRS Channel 8
      27, //GPIO 27, ELRS Channel 9
      26, //GPIO 26, ELRS Channel 10
    };

    void boardSetup() {
      pinMode(LED_PIN_R,OUTPUT);
      pinMode(LED_PIN_G,OUTPUT);
      pinMode(LED_PIN_B,OUTPUT);
    }

    void led_off() {
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, HIGH);
    }
    
    void led_on() {
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, LOW);
    }
#endif

// WaveShare RP2040-Zero
#if BOARD_ID == 3
    #define UART_SELECT Serial2
    #define CRSF_TX 8  // (UART1 == Serial2)
    #define CRSF_RX 9  // (UART1 == Serial2)

    #define LED_TYPE LED_TYPE_NEOPIXEL
    #define LED_PIN 16

    #define Duty_Cycle_Invert 0  // 1 enables inverting the duty cycle signal

    // Set channel function (off, PWM, or Duty Cycle) 
    #define Number_of_Channel_Outputs 12  // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_Config_Setting[Number_of_Channel_Outputs] = {
      Channel_Set_To_PWM, // Channel 1 config setting
      Channel_Set_To_PWM, // Channel 2 config setting
      Channel_Set_To_PWM, // Channel 3 config setting
      Channel_Set_To_PWM, // Channel 4 config setting
      Channel_Set_To_PWM, // Channel 5 config setting
      Channel_Set_To_PWM, // Channel 6 config setting
      Channel_Set_To_DutyCycle, // Channel 7 config setting
      Channel_Set_To_DutyCycle, // Channel 8 config setting
      Channel_Set_To_DutyCycle, // Channel 9 config setting
      Channel_Set_To_DutyCycle, // Channel 10 config setting
      Channel_Set_To_DutyCycle, // Channel 11 config setting
      Channel_Set_To_DutyCycle // Channel 12 config setting
    };

    // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_GPIO_Mapping[Number_of_Channel_Outputs] = {
      29, //GPIO 29, ELRS Channel 1
      28, //GPIO 28, ELRS Channel 2
      27, //GPIO 27, ELRS Channel 3
      26, //GPIO 26, ELRS Channel 4
      15, //GPIO 15, ELRS Channel 5
      14, //GPIO 14, ELRS Channel 6
      2, //GPIO 2, ELRS Channel 7
      3, //GPIO 3, ELRS Channel 8
      4, //GPIO 4 ELRS Channel 9
      5, //GPIO 5 ELRS Channel 10
      6, //GPIO 6 ELRS Channel 11
      7  //GPIO 7 ELRS Channel 12
    };

    #include <Adafruit_NeoPixel.h>
    Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);
    
    void boardSetup() {
      // noop
    }

    void led_off() {
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.show();
    }
    
    void led_on() {
      pixels.setPixelColor(0, pixels.Color(0,0,255));
      pixels.show();
      
    }

    void led_color(uint8_t r, uint8_t g, uint8_t b) {
      pixels.setPixelColor(0, pixels.Color(r,g,b));
      pixels.show();
    }
#endif

// Seeed XIAO 2040
#if BOARD_ID == 4
    #define UART_SELECT Serial1
    #define CRSF_TX 0  // (GP0 == UART0 == Serial1) Problem with main.cpp which uses (UART1 == Serial2)?
    #define CRSF_RX 1  // (GP1 == UART0 == Serial1) Problem with main.cpp which uses (UART1 == Serial2)?

    // 1 NEOPixel - currently unused
    //#define LED_TYPE LED_TYPE_NEOPIXEL
    //#define LED_NEO_PWR 11
    //#define LED_PIN 12

    #define Duty_Cycle_Invert 0  // 1 enables inverting the duty cycle signal

    // Set channel function (off, PWM, or Duty Cycle) and GPIO pin number below
    #define Number_of_Channel_Outputs 9  // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_Config_Setting[Number_of_Channel_Outputs] = {
      Channel_Set_To_PWM, // Channel 1 config setting
      Channel_Set_To_PWM, // Channel 2 config setting
      Channel_Set_To_PWM, // Channel 3 config setting
      Channel_Set_To_PWM, // Channel 4 config setting
      Channel_Set_To_PWM, // Channel 5 config setting
      Channel_Set_To_PWM, // Channel 6 config setting
      Channel_Set_To_PWM, // Channel 7 config setting
      Channel_Set_To_PWM, // Channel 8 config setting
      Channel_Set_To_PWM, // Channel 9 config setting
    };

    // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_GPIO_Mapping[Number_of_Channel_Outputs] ={
      26, //GPIO 29, ELRS Channel 1
      27, //GPIO 28, ELRS Channel 2
      28, //GPIO 27, ELRS Channel 3
      29, //GPIO 26, ELRS Channel 4
      6, //GPIO 15, ELRS Channel 5
      7, //GPIO 14, ELRS Channel 6
      2, //GPIO 2, ELRS Channel 7
      3, //GPIO 3, ELRS Channel 8
      4, //GPIO 4 ELRS Channel 9
    };

    //#include <Adafruit_NeoPixel.h>
    //Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);
    
    // 1 Active Low RGB
    //#define LED_ACTIVE_LOW LED_ACTIVE_LOW_TRUE
    #define LED_TYPE LED_TYPE_RGB
    #define LED_PIN_R 17
    #define LED_PIN_G 16
    #define LED_PIN_B 25

    void boardSetup() {
        // Enable neopixel LED
        //pinMode(LED_NEO_PWR, OUTPUT);
        //digitalWrite(LED_NEO_PWR,HIGH);
        // Turn off user led
        pinMode(LED_PIN_R,OUTPUT);
        pinMode(LED_PIN_G,OUTPUT);
        pinMode(LED_PIN_B,OUTPUT);
        digitalWrite(LED_PIN_R, HIGH);
        digitalWrite(LED_PIN_G, HIGH);
        digitalWrite(LED_PIN_B, HIGH);
    }

    void led_off() {
      //pixels.setPixelColor(0, pixels.Color(0,0,0));
      //pixels.show();
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, HIGH);
    }
    
    void led_on() {
      //pixels.setPixelColor(0, pixels.Color(0,0,255));
      //pixels.show();
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, LOW);
    }
    
#endif

// PiPico_W
#if BOARD_ID == 5
    #define UART_SELECT Serial2
    #define CRSF_TX 4  // physical 6 (UART1 == Serial2)
    #define CRSF_RX 5  // physical 7 (UART1 == Serial2)

    #define LED_TYPE LED_TYPE_SINGLE
    #define LED_PIN 6  // Need to install an external LED since Pico W internal LED is difficult to access.

    #define Duty_Cycle_Invert 0  // 1 enables inverting the duty cycle signal

    // Set channel function (off, PWM, or Duty Cycle) and GPIO pin number below
    #define Number_of_Channel_Outputs 12  // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_Config_Setting[Number_of_Channel_Outputs] = {
      Channel_Set_To_PWM, // Channel 1 config setting
      Channel_Set_To_PWM, // Channel 2 config setting
      Channel_Set_To_PWM, // Channel 3 config setting
      Channel_Set_To_PWM, // Channel 4 config setting
      Channel_Set_To_PWM, // Channel 5 config setting
      Channel_Set_To_PWM, // Channel 6 config setting
      Channel_Set_To_DutyCycle, // Channel 7 config setting
      Channel_Set_To_DutyCycle, // Channel 8 config setting
      Channel_Set_To_DutyCycle, // Channel 9 config setting
      Channel_Set_To_DutyCycle, // Channel 10 config setting
      Channel_Set_To_DutyCycle, // Channel 11 config setting
      Channel_Set_To_DutyCycle // Channel 12 config setting
    };

    // NOTE: PWM Channels must be set in Slice Pairs
    uint16_t Channel_GPIO_Mapping[Number_of_Channel_Outputs] ={
      21, //GPIO 21, ELRS Channel 1
      20, //GPIO 20, ELRS Channel 2
      19, //GPIO 19, ELRS Channel 3
      18, //GPIO 18, ELRS Channel 4
      17, //GPIO 17, ELRS Channel 5
      16, //GPIO 16, ELRS Channel 6
      10, //GPIO 10, ELRS Channel 7
      11, //GPIO 11, ELRS Channel 8
      12, //GPIO 12, ELRS Channel 9
      13, //GPIO 13, ELRS Channel 10
      14, //GPIO 14, ELRS Channel 11
      15  //GPIO 15, ELRS Channel 12
    };

    void boardSetup() {
      pinMode(LED_PIN,OUTPUT);
    }

    void led_off() {
      digitalWrite(LED_PIN, LOW);
    }
    
    void led_on() {
      digitalWrite(LED_PIN, HIGH);
    }
#endif

#endif
