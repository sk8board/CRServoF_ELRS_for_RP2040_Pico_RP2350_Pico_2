#include <Arduino.h>
#include <CrsfSerial.h>  // https://github.com/CapnBry/CRServoF/
#include <Servo.h>       // https://guthub.com/earlephilhower/arduino-pico
#include "board_defs.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
//#include <stdio.h>
//#include "pico/time.h"
#include "RP2040_PWM.h"

RP2040_PWM* PWM_Instance;
uint32_t frequency;
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
Servo servo00, servo01, servo02, servo03, servo04, servo05, servo06, servo07, servo08, servo09, servo10, servo11, servo12, servo13, servo14, servo15;
int16_t duty_cycle_value;


// Debug code which is used for sending channel data to USB serial monitor
#define DEBUG 0    // 0 turns off serial debug, 1 turns on serial debug
uint16_t channel1_data;
uint16_t channel2_data;
uint16_t channel3_data;
uint16_t channel4_data;
uint16_t channel5_data;
uint16_t channel6_data;
uint16_t channel7_data;
uint16_t channel8_data;
uint16_t channel9_data;
uint16_t channel10_data;
uint16_t channel11_data;
uint16_t channel12_data;
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#define debug_delay(x) delay(x)
#else
#define debug(x)
#define debugln(x)
#define debug_delay(x)
#endif


// Failsafe declaration and function
void failsafe_output();

void failsafe_output() 
{
  for (u16_t i=0; i<Number_of_Channel_Outputs; ++i)
  {
    if (Channel_Config_Setting[i] == Channel_Set_To_PWM)
    {
      if (i == 0){
        servo00.write(Failsafe_Channel_Value[i]);
        }
      if (i == 1){
        servo01.write(Failsafe_Channel_Value[i]);
        }
      if (i == 2){
        servo02.write(Failsafe_Channel_Value[i]);
        }
      if (i == 3){
        servo03.write(Failsafe_Channel_Value[i]);
        }
      if (i == 4){
        servo04.write(Failsafe_Channel_Value[i]);
        }
      if (i == 5){
        servo05.write(Failsafe_Channel_Value[i]);
        }
      if (i == 6){
        servo06.write(Failsafe_Channel_Value[i]);
        }
      if (i == 7){
        servo07.write(Failsafe_Channel_Value[i]);
        }
      if (i == 8){
        servo08.write(Failsafe_Channel_Value[i]);
        }
      if (i == 9){
        servo09.write(Failsafe_Channel_Value[i]);
        }
      if (i == 10){
        servo10.write(Failsafe_Channel_Value[i]);
        }
      if (i == 11){
        servo11.write(Failsafe_Channel_Value[i]);
        }
      if (i == 12){
        servo12.write(Failsafe_Channel_Value[i]);
        }
      if (i == 13){
        servo13.write(Failsafe_Channel_Value[i]);
        }
      if (i == 14){
        servo14.write(Failsafe_Channel_Value[i]);
        }
      if (i == 15){
        servo15.write(Failsafe_Channel_Value[i]);
        }
    }
    if (Channel_Config_Setting[i] == Channel_Set_To_DutyCycle)
    { 
      duty_cycle_value = (Failsafe_Channel_Value[i]-1000)/10;
      if (duty_cycle_value > 90){
        duty_cycle_value = 100;
      }
      if (duty_cycle_value < 10){
        duty_cycle_value = 0;
      }
      if (Duty_Cycle_Invert == 1){
        duty_cycle_value = (duty_cycle_value-100)*-1;
      }
      pwm_set_gpio_level (Channel_GPIO_Mapping[i], duty_cycle_value);
    }
  }
}


void packetChannels()
{
  // Pin locations can be set up in board_defs.h

  // channelX_data is used for debug only
  if (DEBUG == 1)
  {    
    channel1_data = crsf.getChannel(1);
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
  }

  for (uint8_t i=0; i<Number_of_Channel_Outputs; ++i)
  {
    if (Channel_Config_Setting[i] == Channel_Set_To_PWM)
    {
      if (i == 0){
        servo00.write(crsf.getChannel(i+1));
        }
      if (i == 1){
        servo01.write(crsf.getChannel(i+1));
        }
      if (i == 2){
        servo02.write(crsf.getChannel(i+1));
        }
      if (i == 3){
        servo03.write(crsf.getChannel(i+1));
        }
      if (i == 4){
        servo04.write(crsf.getChannel(i+1));
        }
      if (i == 5){
        servo05.write(crsf.getChannel(i+1));
        }
      if (i == 6){
        servo06.write(crsf.getChannel(i+1));
        }
      if (i == 7){
        servo07.write(crsf.getChannel(i+1));
        }
      if (i == 8){
        servo08.write(crsf.getChannel(i+1));
        }
      if (i == 9){
        servo09.write(crsf.getChannel(i+1));
        }
      if (i == 10){
        servo10.write(crsf.getChannel(i+1));
        }
      if (i == 11){
        servo11.write(crsf.getChannel(i+1));
        }
      if (i == 12){
        servo12.write(crsf.getChannel(i+1));
        }
      if (i == 13){
        servo13.write(crsf.getChannel(i+1));
        }
      if (i == 14){
        servo14.write(crsf.getChannel(i+1));
        }
      if (i == 15){
        servo15.write(crsf.getChannel(i+1));
        }
    }
    if (Channel_Config_Setting[i] == Channel_Set_To_DutyCycle)
    { 
      duty_cycle_value = ((crsf.getChannel(i+1)-1000)/10);
      if (duty_cycle_value > 90){
        duty_cycle_value = 100;
      }
      if (duty_cycle_value < 10){
        duty_cycle_value = 0;
      }
      if (Duty_Cycle_Invert == 1){
        duty_cycle_value = (duty_cycle_value-100)*-1;
      }
      //pwm_set_gpio_level (Channel_GPIO_Mapping[i], duty_cycle_value);
      PWM_Instance->setPWM(Channel_GPIO_Mapping[i], frequency, duty_cycle_value);
    }
  }   
}


void crsfLinkUp() 
{
  ms_last_link_changed = millis();
  ms_last_led_changed = ms_last_link_changed;
  led_state = true;
  led_on();
}


void crsfLinkDown() 
{
  ms_last_link_changed = millis();
  ms_last_led_changed = ms_last_link_changed;
  led_state = false;
  led_off();
  failsafe_output();
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
    debugln("Fake CLI Mode, type 'exit' or 'help' to do nothing\r\n");
    serialEcho = true;
  }

  else if (strcmp(cmd, "serial") == 0)
      debugln("serial 5 64 0 0 0 0\r\n");

  else if (strcmp(cmd, "get serialrx_provider") == 0)
      debugln("serialrx_provider = CRSF\r\n");

  else if (strcmp(cmd, "get serialrx_inverted") == 0)
      debugln("serialrx_inverted = OFF\r\n");

  else if (strcmp(cmd, "get serialrx_halfduplex") == 0)
      debugln("serialrx_halfduplex = OFF\r\n");

  else if (strncmp(cmd, "serialpassthrough 5 ", 20) == 0)
  {
    debugln(cmd);

    unsigned int baud = atoi(&cmd[20]);
    passthroughBegin(baud);

    return true;
  }

  else
      prompt = false;

  if (prompt)
      debug("# ");

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

uint8_t Channel_Pin;

void pwm_init_pin(uint8_t Channel_Pin) {
    gpio_set_function(Channel_Pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(Channel_Pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);
}

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

  uint8_t Channel_Pin;

  unsigned i;
  for (i=0; i<Number_of_Channel_Outputs; ++i)
  {
    if (Channel_Config_Setting[i] == Channel_Set_To_PWM)
    {
      if (i == 0){
        servo00.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 1){
        servo01.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 2){
        servo02.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 3){
        servo03.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 4){
        servo04.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 5){
        servo05.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 6){
        servo06.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 7){
        servo07.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 8){
        servo08.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 9){
        servo09.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 10){
        servo10.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 11){
        servo11.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 12){
        servo12.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 13){
        servo13.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 14){
        servo14.attach(Channel_GPIO_Mapping[i]);
        }
      if (i == 15){
        servo15.attach(Channel_GPIO_Mapping[i]);
        }
    }
    if (Channel_Config_Setting[i] == Channel_Set_To_DutyCycle)
    { 
      Channel_Pin = Channel_GPIO_Mapping[i];
      frequency = 10000;  // hz
      PWM_Instance = new RP2040_PWM(Channel_Pin, frequency, 0);
      // pwm_init_pin(Channel_Pin); 
      // pwm_set_gpio_level (Channel_Pin, 0);
    }
  } 
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


void setup1()  // for second core
{

}


void loop1()   // for second core
{
  debug("Channel 1  ");
  debug(channel1_data);
  debugln();
  debug("Channel 2  ");
  debug(channel2_data);
  debugln();
  debug("Channel 3  ");
  debug(channel3_data);
  debugln();
  debug("Channel 4  ");
  debug(channel4_data);
  debugln();
  debug("Channel 5  ");
  debug(channel5_data);
  debugln();
  debug("Channel 6  ");
  debug(channel6_data);
  debugln();
  debug("Channel 7  ");
  debug(channel7_data);
  debugln();
  debug("Channel 8  ");
  debug(channel8_data);
  debugln();
  debug("Channel 9  ");
  debug(channel9_data);
  debugln();
  debug("Channel 10  ");
  debug(channel10_data);
  debugln();
  debug("Channel 11  ");
  debug(channel11_data);
  debugln();
  debug("Channel 12  ");
  debug(channel12_data);
  debugln();
  debug_delay(1000);
}
