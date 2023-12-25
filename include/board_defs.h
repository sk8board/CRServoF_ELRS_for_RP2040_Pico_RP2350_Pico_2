#ifndef BOARD_DEFS
#define BOARD_DEFS

#define LED_TYPE_SINGLE 1
#define LED_TYPE_NEOPIXEL 2
#define LED_TYPE_RGB 3

// PiPico
#if BOARD_ID == 1
    #define UART_SELECT Serial2
    #define CRSF_TX 4  // physical 6 (UART1 == Serial2)
    #define CRSF_RX 5  // physical 7 (UART1 == Serial2)

    #define LED_TYPE LED_TYPE_SINGLE
    #define LED_PIN 25

    #define PWM_PIN1 21  //GP21, ELRS Channel 1
    #define PWM_PIN2 20  //GP20, ELRS Channel 2
    #define PWM_PIN3 19  //GP19, ELRS Channel 3
    #define PWM_PIN4 18  //GP18, ELRS Channel 4
    #define PWM_PIN5 17  //GP17, ELRS Channel 5
    #define PWM_PIN6 16  //GP16, ELRS Channel 6

    #define LED_Invert >  // Change > or < to invert the LED operation
    #define External_LED_PIN1 10  //GP10, ELRS Channel 7
    #define External_LED_PIN2 11  //GP11, ELRS Channel 8
    #define External_LED_PIN3 12  //GP12, ELRS Channel 9
    #define External_LED_PIN4 13  //GP13, ELRS Channel 10
    #define External_LED_PIN5 14  //GP14, ELRS Channel 11
    #define External_LED_PIN6 15  //GP15, ELRS Channel 12

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

    #define PWM_PIN1 0  //GP0, ELRS Channel 1
    #define PWM_PIN2 1  //GP1, ELRS Channel 2
    #define PWM_PIN3 2  //GP2, ELRS Channel 3
    #define PWM_PIN4 3  //GP3, ELRS Channel 4
    #define PWM_PIN5 6  //GP6, ELRS Channel 5
    #define PWM_PIN6 7  //GP7, ELRS Channel 6

    #define LED_Invert >  // Change > or < to invert the LED operation
    #define External_LED_PIN1 29 //GP29, ELRS Channel 7
    #define External_LED_PIN2 28 //GP28, ELRS Channel 8
    #define External_LED_PIN3 27 //GP27, ELRS Channel 9
    #define External_LED_PIN4 26 //GP26, ELRS Channel 10
    #define External_LED_PIN5 25 //GPx,  ELRS Channel 11
    #define External_LED_PIN6 24 //GPx,  ELRS Channel 12

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

    #define PWM_PIN1 29  //GPIO 29, ELRS Channel 1
    #define PWM_PIN2 28  //GPIO 28, ELRS Channel 2
    #define PWM_PIN3 27  //GPIO 27, ELRS Channel 3
    #define PWM_PIN4 26  //GPIO 26, ELRS Channel 4
    #define PWM_PIN5 15  //GPIO 15, ELRS Channel 5
    #define PWM_PIN6 14  //GPIO 14, ELRS Channel 6

    #define LED_Invert >  // Change > or < to invert the LED operation
    #define External_LED_PIN1 2  //GPIO 2 ELRS Channel 7
    #define External_LED_PIN2 3  //GPIO 3 ELRS Channel 8
    #define External_LED_PIN3 4  //GPIO 4 ELRS Channel 9
    #define External_LED_PIN4 5  //GPIO 5 ELRS Channel 10
    #define External_LED_PIN5 6  //GPIO 6 ELRS Channel 11
    #define External_LED_PIN6 7  //GPIO 7 ELRS Channel 12

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

    #define PWM_PIN1 26  //GP26, ELRS Channel 1
    #define PWM_PIN2 27  //GP27, ELRS Channel 2
    #define PWM_PIN3 28  //GP28, ELRS Channel 3
    #define PWM_PIN4 29  //GP29, ELRS Channel 4
    #define PWM_PIN5 6   //GP6,  ELRS Channel 5
    #define PWM_PIN6 7   //GP7,  ELRS Channel 6

    #define LED_Invert >  // Change > or < to invert the LED operation
    #define External_LED_PIN1 2   //GP2, ELRS Channel 7
    #define External_LED_PIN2 3   //GP3, ELRS Channel 8
    #define External_LED_PIN3 4   //GP4, ELRS Channel 9
    #define External_LED_PIN4 13  //GPx, ELRS Channel 10
    #define External_LED_PIN5 14  //GPx, ELRS Channel 11
    #define External_LED_PIN6 15  //GPx, ELRS Channel 12

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

    #define PWM_PIN1 21  //GP21, ELRS Channel 1
    #define PWM_PIN2 20  //GP20, ELRS Channel 2
    #define PWM_PIN3 19  //GP19, ELRS Channel 3
    #define PWM_PIN4 18  //GP18, ELRS Channel 4
    #define PWM_PIN5 17  //GP17, ELRS Channel 5
    #define PWM_PIN6 16  //GP16, ELRS Channel 6

    #define LED_Invert >  // Change > or < to invert the LED operation
    #define External_LED_PIN1 10  //GP10, ELRS Channel 7
    #define External_LED_PIN2 11  //GP11, ELRS Channel 8
    #define External_LED_PIN3 12  //GP12, ELRS Channel 9
    #define External_LED_PIN4 13  //GP13, ELRS Channel 10
    #define External_LED_PIN5 14  //GP14, ELRS Channel 11
    #define External_LED_PIN6 15  //GP15, ELRS Channel 12

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
