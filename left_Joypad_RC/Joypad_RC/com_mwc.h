#include "Arduino.h"
#include <ZigduinoRadio.h>

byte getChecksum(byte length, byte cmd, byte mydata[]) {
  byte checksum = 0;
  checksum ^= (length & 0xFF);
  checksum ^= (cmd & 0xFF);
  for (uint8_t i = 0; i < length; i++)
    checksum ^= (mydata[i] & 0xFF);
  return checksum;
}

uint16_t write16(boolean a, int16_t b) {
  return a ? (b >> 8) : (b & 0x00ff);
}

/*
  if Core RF
  [head,2byte,0xAA 0xBB] [type,1byte,TYPE_NUM] [data,16byte] [body,1byte,getChecksum()]
  Example:
  AA BB C8 DC 05 DC 05 D0 07 EF 03 DC 05 DC 05 DC 05 DC 05 E3
*/
#define buf_length 30   //16
#define buf_code_A 0xC8   //200
boolean buf_code = true;
boolean buf_type = true;

static byte buf_data[buf_length];
static byte buf_body;
boolean mwc_send(uint8_t _code, int16_t _channal[buf_length/2]) {
  mwc_port.beginTransmission();
  mwc_port.write(0xaa);
  mwc_port.write(0xbb);
  mwc_port.write(_code);
  for (uint8_t a = 0; a < (buf_length / 2); a++) {
    buf_data[2 * a] = write16(LOW, _channal[a]);
    buf_data[2 * a + 1] = write16(HIGH, _channal[a]);
  }
  for (uint8_t a = 0; a < buf_length; a++)
    mwc_port.write(buf_data[a]);
  buf_body = getChecksum(buf_length, _code, buf_data);
  mwc_port.write(buf_body);
  mwc_port.endTransmission();
  return true;
}

int _V_bat_RC = 0;
uint32_t mwc_rece() {
  if (mwc_port.available()) {
    while (mwc_port.available()) {
      _V_bat_RC = mwc_port.read();
    }
    RSSI = mwc_port.getLastRssi();
    return millis();
  }
  return 0;
}
