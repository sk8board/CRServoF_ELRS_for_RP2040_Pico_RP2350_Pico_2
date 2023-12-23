#include <Arduino.h>
#include <CrsfSerial.h>  // https://github.com/CapnBry/CRServoF/
#include <Servo.h>
#include "board_defs.h"

// BOARD_ID SELECTION HAPPENS IN PLATFORMIO ENVIRONMENT SELECTION

// Blink routine variables and state tracking
#define BLINK_ENABLED                    // comment this line out to disable led blink
#define BLINK_TIME 60000                 // blink routine window (in ms)
#define BLINK_DELAY 500                  // delay in between led state change (in ms)

static bool serialEcho;
static char serialInBuff[64];
static uint8_t serialInBuffLen;

bool led_state = false;                  // track led on/off state
unsigned long ms_curr = 0;               // current time
unsigned long ms_last_link_changed = 0;  // last time crsf link changed
unsigned long ms_last_led_changed = 0;   // last time led changed state in blink routine

CrsfSerial crsf(UART_SELECT, CRSF_BAUDRATE); // pass any HardwareSerial port
int channel_data = 0;
int map_data = 0;
Servo servo1, servo2, servo3, servo4, servo5, servo6;
bool External_LED_PIN1_State;
bool External_LED_PIN2_State;
bool External_LED_PIN3_State;
bool External_LED_PIN4_State;
bool External_LED_PIN5_State;
bool External_LED_PIN6_State;

/*// for testing only
int channel1_data;
int channel2_data;
int channel3_data;
int channel4_data;
int channel5_data;
int channel6_data;
int channel7_data;
int channel8_data;
int channel9_data;
int channel10_data;
int channel11_data;
int channel12_data;
*/


void packetChannels()
{
    // Manually expanding instead of looping so I can change params as needed


    // Pin locations can be set up in calibrations.h
    // Channels 1 - 6 are PWM outputs
    // Channels 7 - 12 are LED ground side driver outputs

    // channelX_data is used for testing only
    /*channel1_data = crsf.getChannel(1);
    channel2_data = crsf.getChannel(2);
    channel3_data = crsf.getChannel(3);
    channel4_data = crsf.getChannel(4);
    channel5_data = crsf.getChannel(5);
    channel6_data = crsf.getChannel(6);
    channel7_data = crsf.getChannel(7);
    channel8_data = crsf.getChannel(8);
    channel9_data = crsf.getChannel(9);
    channel10_data = crsf.getChannel(10);
    channel11_data = crsf.getChannel(11);
    channel12_data = crsf.getChannel(12);
    */
    servo1.write(crsf.getChannel(1));
    servo2.write(crsf.getChannel(2));
    servo3.write(crsf.getChannel(3));
    servo4.write(crsf.getChannel(4));
    servo5.write(crsf.getChannel(5));
    servo6.write(crsf.getChannel(6));

    if (crsf.getChannel(7) LED_Invert 1600)
    {
      if (External_LED_PIN1_State == 0)
      {
        gpio_put(External_LED_PIN1, HIGH);
        External_LED_PIN1_State = 1;
      }
    }
    else
    {
      if (External_LED_PIN1_State == 1)
      {
        gpio_put(External_LED_PIN1, LOW);
        External_LED_PIN1_State = 0;
      }
    }

    if (crsf.getChannel(8) LED_Invert 1600)
    {
      if (External_LED_PIN2_State == 0)
      {
        gpio_put(External_LED_PIN2, HIGH);
        External_LED_PIN2_State = 1;
      }
    }
    else
    {
      if (External_LED_PIN2_State == 1)
      {
        gpio_put(External_LED_PIN2, LOW);
        External_LED_PIN2_State = 0;
      }
    }

    if (crsf.getChannel(9) LED_Invert 1600)
    {
      if (External_LED_PIN3_State == 0)
      {
        gpio_put(External_LED_PIN3, HIGH);
        External_LED_PIN3_State = 1;
      }
    }
    else
    {
      if (External_LED_PIN3_State == 1)
      {
        gpio_put(External_LED_PIN3, LOW);
        External_LED_PIN3_State = 0;
      }
    }

    if (crsf.getChannel(10) LED_Invert 1600)
    {
      if (External_LED_PIN4_State == 0)
      {
        gpio_put(External_LED_PIN4, HIGH);
        External_LED_PIN4_State = 1;
      }
    }
    else
    {
      if (External_LED_PIN4_State == 1)
      {
        gpio_put(External_LED_PIN4, LOW);
        External_LED_PIN4_State = 0;
      }
    }

    if (crsf.getChannel(11) LED_Invert 1600)
    {
      if (External_LED_PIN5_State == 0)
      {
        gpio_put(External_LED_PIN5, HIGH);
        External_LED_PIN5_State = 1;
      }
    }
    else
    {
      if (External_LED_PIN5_State == 1)
      {
        gpio_put(External_LED_PIN5, LOW);
        External_LED_PIN5_State = 0;
      }
    }

    if (crsf.getChannel(12) LED_Invert 1600)
    {
      if (External_LED_PIN6_State == 0)
      {
        gpio_put(External_LED_PIN6, HIGH);
        External_LED_PIN6_State = 1;
      }
    }
    else
    {
      if (External_LED_PIN6_State == 1)
      {
        gpio_put(External_LED_PIN6, LOW); 
        External_LED_PIN6_State = 0;
      }
    }
}

void crsfLinkUp() {
  ms_last_link_changed = millis();
  ms_last_led_changed = ms_last_link_changed;
  led_state = true;
  led_on();
}

void crsfLinkDown() {
  ms_last_link_changed = millis();
  ms_last_led_changed = ms_last_link_changed;
  led_state = false;
  led_off();
}

static void passthroughBegin(uint32_t baud)
{
    if (baud != crsf.getBaud())
    {
        // Force a reboot command since we want to send the reboot
        // at 420000 then switch to what the user wanted
        const uint8_t rebootpayload[] = { 'b', 'l' };
        crsf.queuePacket(CRSF_ADDRESS_CRSF_RECEIVER, CRSF_FRAMETYPE_COMMAND, &rebootpayload, sizeof(rebootpayload));
    }
    crsf.setPassthroughMode(true, baud);
    
    serialEcho = false;
}

static void crsfOobData(uint8_t b)
{
    Serial.write(b);
}

/***
 * @brief Processes a text command like we're some sort of CLI or something
 * @return true if CrsfSerial was placed into passthrough mode, false otherwise
*/

static bool handleSerialCommand(char *cmd)
{
    // Fake a CRSF RX on UART6
    bool prompt = true;
    if (strcmp(cmd, "#") == 0)
    {
        Serial.println("Fake CLI Mode, type 'exit' or 'help' to do nothing\r\n");
        serialEcho = true;
    }

    else if (strcmp(cmd, "serial") == 0)
        Serial.println("serial 5 64 0 0 0 0\r\n");

    else if (strcmp(cmd, "get serialrx_provider") == 0)
        Serial.println("serialrx_provider = CRSF\r\n");

    else if (strcmp(cmd, "get serialrx_inverted") == 0)
        Serial.println("serialrx_inverted = OFF\r\n");

    else if (strcmp(cmd, "get serialrx_halfduplex") == 0)
        Serial.println("serialrx_halfduplex = OFF\r\n");

    else if (strncmp(cmd, "serialpassthrough 5 ", 20) == 0)
    {
        Serial.println(cmd);

        unsigned int baud = atoi(&cmd[20]);
        passthroughBegin(baud);

        return true;
    }

    else
        prompt = false;

    if (prompt)
        Serial.print("# ");

    return false;
}

static void checkSerialInNormal()
{
    while (Serial.available())
    {
        char c = Serial.read();
        if (serialEcho && c != '\n')
            Serial.write(c);

        if (c == '\r' || c == '\n')
        {
            if (serialInBuffLen != 0)
            {
                Serial.write('\n');
                serialInBuff[serialInBuffLen] = '\0';
                serialInBuffLen = 0;

                bool goToPassthrough = handleSerialCommand(serialInBuff);
                // If need to go to passthrough, get outta here before we dequeue any bytes
                if (goToPassthrough)
                    return;
            }
        }
        else
        {
            serialInBuff[serialInBuffLen++] = c;
            // if the buffer fills without getting a newline, just reset
            if (serialInBuffLen >= sizeof(serialInBuff))
                serialInBuffLen = 0;
        }
    }  /* while Serial */
}

static void checkSerialInPassthrough()
{
    static uint32_t lastData = 0;
    static bool LED = false;
    bool gotData = false;
    unsigned int avail;
    while ((avail = Serial.available()) != 0)
    {
        uint8_t buf[16];
        avail = Serial.readBytes((char *)buf, min(sizeof(buf), avail));
        crsf.write(buf, avail);
        LED ? led_on() : led_off();
        LED = !LED;
        gotData = true;
    }
    // If longer than X seconds since last data, switch out of passthrough
    if (gotData || !lastData)
        lastData = millis();

    // Turn off LED 1s after last data
    else if (LED && (millis() - lastData > 1000))
    {
        LED = false;
        led_off();
    }

    // Short blink LED after timeout
    else if (millis() - lastData > 5000)
    {
        lastData = 0;
        led_on();
        delay(200);
        led_off();
        crsf.setPassthroughMode(false);
    }
}

static void checkSerialIn()
{
    if (crsf.getPassthroughMode())
        checkSerialInPassthrough();
    else
        checkSerialInNormal();
}

#ifdef BLINK_ENABLED
void led_loop() {
  ms_curr = millis();
  // link is down
  if(!crsf.isLinkUp()) {
    // within the blink routine window (BLINK_TIME)
    if(ms_curr < (ms_last_link_changed + BLINK_TIME)) {
      // handle led toggle delay
      if(ms_curr > (ms_last_led_changed + BLINK_DELAY)) {
        ms_last_led_changed = ms_curr;
        led_state ? led_on() : led_off();
        led_state = !led_state;  // toggle led state
      }
    }
    else
    {
      // ensure the led is off if the blink routine expired and link is down
      led_off();
    }
  }
}
#endif



void setup()
{
    Serial.begin(115200);
    UART_SELECT.setTX(CRSF_TX);
    UART_SELECT.setRX(CRSF_RX);
    boardSetup();
    crsfLinkDown();


    // Attach the channels callback
    crsf.onPacketChannels = &packetChannels;
    crsf.onLinkUp = &crsfLinkUp;
    crsf.onLinkDown = &crsfLinkDown;
    crsf.onOobData = &crsfOobData;
    crsf.begin();
    serialEcho = true;
    gpio_init (External_LED_PIN1); 
    gpio_init (External_LED_PIN2);
    gpio_init (External_LED_PIN3);
    gpio_init (External_LED_PIN4);
    gpio_init (External_LED_PIN5);
    gpio_init (External_LED_PIN6);
    gpio_set_dir(External_LED_PIN1, OUTPUT);
    gpio_set_dir(External_LED_PIN2, OUTPUT);
    gpio_set_dir(External_LED_PIN3, OUTPUT);
    gpio_set_dir(External_LED_PIN4, OUTPUT);
    gpio_set_dir(External_LED_PIN5, OUTPUT);
    gpio_set_dir(External_LED_PIN6, OUTPUT);

    servo1.attach(PWM_PIN1);
    servo2.attach(PWM_PIN2);
    servo3.attach(PWM_PIN3);
    servo4.attach(PWM_PIN4);
    servo5.attach(PWM_PIN5);
    servo6.attach(PWM_PIN6);
}

void loop()
{
    // Must call CrsfSerial.loop() in loop() to process data
    crsf.loop();
    checkSerialIn();
    #ifdef BLINK_ENABLED
    led_loop();
    #endif
}

/*
void setup1()  // for second core
{

}

void loop1()   // for second core
{
  Serial.print("Channel 1  ");
  Serial.print(channel1_data);
  Serial.println();
  Serial.print("Channel 2  ");
  Serial.print(channel2_data);
  Serial.println();
  Serial.print("Channel 3  ");
  Serial.print(channel3_data);
  Serial.println();
  Serial.print("Channel 4  ");
  Serial.print(channel4_data);
  Serial.println();
  Serial.print("Channel 5  ");
  Serial.print(channel5_data);
  Serial.println();
  Serial.print("Channel 6  ");
  Serial.print(channel6_data);
  Serial.println();
  Serial.print("Channel 7  ");
  Serial.print(channel7_data);
  Serial.println();
  Serial.print("Channel 8  ");
  Serial.print(channel8_data);
  Serial.println();
  Serial.print("Channel 9  ");
  Serial.print(channel9_data);
  Serial.println();
  Serial.print("Channel 10  ");
  Serial.print(channel10_data);
  Serial.println();
  Serial.print("Channel 11  ");
  Serial.print(channel11_data);
  Serial.println();
  Serial.print("Channel 12  ");
  Serial.print(channel12_data);
  Serial.println();
  Serial.print(External_LED_PIN6_State);
  Serial.println();
  Serial.print(crsf.getChannel(12) < 1600);
  Serial.println();
  delay(1000);
}
*/
