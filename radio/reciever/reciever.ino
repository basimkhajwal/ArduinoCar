#include <VirtualWire.h>

#define RF_PIN 3

/*

A valid instruction follows the following format

1EDDDSSS

Where E is enable, if 0 then all motors are off
      D is direction, 000 is North and the rest anti-clockwise compass directions
      S is speed, 000 being off and 111 is full speed

*/
const uint8_t VALID_MASK = 0x80;
const uint8_t ENABLE_MASK = 0x40;

uint8_t state;
boolean dirty = false;

void setup() {
  vw_set_rx_pin(RF_PIN);
  vw_setup(500);
  
  vw_rx_start();
}

void parseState() {
  
  
  
}

void loop() {
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  uint8_t newState = state;
  
  if (vw_get_message(buf, &buflen)) {
     for (int i = 0; i < buflen && (state & VALID_MASK); i++) {
       newState = buf[i];
     }
     
     if (newState != state) {
       state = newState;
       dirty = true;
     }
  }
  
  if (dirty) {
    parseState();
    dirty = false;
  }
}
