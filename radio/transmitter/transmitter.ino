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
const uint8_t NORMAL_MASK = VALID_MASK | ENABLE_MASK | SPEED_MASK;

uint8_t FORWARD = NORMAL_MASK;
uint8_t FORWARD_LEFT = NORMAL_MASK | (1 << 3);
uint8_t FORWARD_RIGHT = NORMAL_MASK | (2 << 3);
uint8_t BACK = NORMAL_MASK | (3 << 3);
uint8_t BACK_LEFT = NORMAL_MASK | (4 << 3);
uint8_t BACK_RIGHT = NORMAL_MASK | (5 << 3);
uint8_t STOP = VALID_MASK;

void setup() {
  Serial.begin(9600);
  
  vw_set_tx_pin(RF_PIN);
  vw_setup(500);
}

void sendSignal(uint8_t* signal) {
  vw_send(signal, 1); 
}

String directions[] = {
  "forward",
  "forward left",
  "forward right",
  
  "backward",
  "backward left",
  "backward right"
};

void loop() {
  
  uint8_t signal;
  
  if (Serial.available()) {
    String input = String(Serial.readStringUntil('\n'));
    input.toLowerCase();
    
    /*
    
    The first section checks for a space, if there
    is none then the code will default to stop the
    program.
    
    Otherwise the input is split into two with the
    first signifying the direction and the second
    the speed. (Note. these are not checked and an
    error could arise with invalid input)
    
    */
    
    
    int index = input.indexOf(' ');
    signal = VALID_MASK;
    
    if (index != -1) {
      
      //Extract the direction and the speed
      String directionString = input.substring(0, index);
      int givenSpeed = input.substring(index + 1).toInt();
      givenSpeed %= 7;
      
      /*
      Iterate over each vliad direction and test if the input
      matches the direction given, then generate a valid signal
      and terminate the loop
      */
      for (int i = 0; i < 6; i++) {
        if (directionString == directions[i]) {
          signal = VALID_MASK | ENABLE_MASK | (i << 3) | givenSpeed;
          break;
        }
      }
      
    }
   
    //If no direction was found / no space then stop by default
    if (signal == VALID_MASK) {
      Serial.println("Stopping");
    }
    
    sendSignal(&signal);
  }
  
}
