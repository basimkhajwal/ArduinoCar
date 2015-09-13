#include <VirtualWire.h>

#define RF_PIN 10

/*

A valid instruction follows the following format

1EDDDSSS

Where E is enable, if 0 then all motors are off
      D is direction, (see below)
      S is speed, 000 being off and 111 is full speed (TO BE DONE LATER)

Directions:
0 - Forward
1 - Forward Left
2 - Forward Right
3 - Backward
4 - Backward Left
5 - Backward Right

Any other value will default to Forward

*/
const uint8_t VALID_MASK = 0x80;
const uint8_t ENABLE_MASK = 0x40;
const uint8_t DIRECTION_MASK = 0x38;
const uint8_t SPEED_MASK = 0x07;

const uint8_t FORWARD = VALID_MASK | ENABLE_MASK | SPEED_MASK ;
const uint8_t BACK = VALID_MASK | ENABLE_MASL | SPEED_MASK | 0x28; //Binary 00101000 which is 5 (for the reciever)
const uint8_t STOP = VALID_MASK;

void setup() {
  vw_set_tx_pin(RF_PIN);
  vw_setup(500);
}

void sendSignal(uint8_t* signal) {
  vw_send(signal, 1); 
}

void loop() {
  
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n').toLower();
    
    if (input == "forward") {
      Serial.write("Moving forward");
      sendSignal(&FORWARD);
    } else if (input == "backward") {
      Serial.write("Moving backward");
      sendSignal(&BACKWARD);
    } else {
      Serial.write("Stopping");
      sendSignal(&STOP);
    }
  }
  
}
