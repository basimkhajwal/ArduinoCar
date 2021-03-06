#include <VirtualWire.h>

#define RF_PIN 3

#define LEFT_PIN 6
#define RIGHT_PIN 5

#define FORWARD_PIN 11
#define BACK_PIN 9

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

uint8_t state;

void setup() {
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(BACK_PIN, OUTPUT);
  state = 0;
  parseState();
  
  vw_set_rx_pin(RF_PIN);
  vw_setup(1000);
  
  vw_rx_start();
}

void parseState() {
  
  boolean disabled = (ENABLE_MASK & state) == 0;
  int carDirection = (DIRECTION_MASK & state) >> 3;
  int carSpeed = disabled ? 0 : (SPEED_MASK & state);
  
  digitalWrite(LEFT_PIN, LOW);
  digitalWrite(RIGHT_PIN, LOW);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(BACK_PIN, LOW);
  
  //Later on do PWM for now it is normal on-off no speed
  if (carSpeed != 0) {
    //Multiply by 32 to make 0-7 into 0-255
    int convertedSpeed = carSpeed << 5;
    
    switch (carDirection) {
    
      case 1:
        analogWrite(FORWARD_PIN, convertedSpeed);
        digitalWrite(LEFT_PIN, HIGH);
        break;
    
      case 2:
        analogWrite(FORWARD_PIN, convertedSpeed);
        digitalWrite(RIGHT_PIN, HIGH);
        break;
    
      case 3:
        analogWrite(BACK_PIN, convertedSpeed);
        break;
        
      case 4:
        analogWrite(BACK_PIN, convertedSpeed);
        digitalWrite(LEFT_PIN, HIGH);
        break;
        
      case 5:
        analogWrite(BACK_PIN, convertedSpeed);
        digitalWrite(RIGHT_PIN, HIGH);
        break;
        
      default:
        analogWrite(FORWARD_PIN, convertedSpeed);
        break;
    
    }
  }
}

void loop() {
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  uint8_t newState = state;
  
  if (vw_get_message(buf, &buflen)) {   
     if (buf[0] & VALID_MASK) {
       state = buf[0];
       parseState();
     }
  }
}
