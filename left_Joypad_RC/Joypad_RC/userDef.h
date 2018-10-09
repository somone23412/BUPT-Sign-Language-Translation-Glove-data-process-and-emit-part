#include "Arduino.h"

//DEBUG-----------
//#define Serial_DEBUG

#if defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define LARGE_FLASH
#endif
#if defined(__AVR_ATmega128RFA1__)
#define RF_PORT
#endif

#define Joy_MID 1500

//RSSI------------
int8_t RSSI = -40;

//MWC-------------
uint8_t mwc_channal = 16; //RF channel

#define mwc_port ZigduinoRadio    //RF

//nRF-------------
#define interval_debug  100

//Time------------
#define interval_TIME1 1000    //setup delay
#define interval_time2 40      //send interval
#define interval_time3 1000    //battery interval
#define interval_time4 40      //tft interval

