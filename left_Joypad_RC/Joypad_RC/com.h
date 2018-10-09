#include "Arduino.h"
#include "com_mwc.h"

//debug--------------------------
void comBegin() {
  unsigned long _channel;
  _channel = mwc_channal;
  mwc_port.begin(_channel);
}

boolean comSend(uint8_t _code, int16_t _channal[buf_length / 2]) {
  if (mwc_send(_code, _channal)) //QuadCopter
    return true;
}

boolean comRece() {
  return boolean(mwc_rece());
}
