#include <VirtualWire.h>

#define RF_PIN 3

#define LEFT_PIN 6
#define RIGHT_PIN 5

#define FORWARD_PIN 11
#define BACK_PIN 10

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
  vw_setup(500);
  
  vw_rx_start();
}

void blinkLed() {
  digitalWrite(13, HIGH);
  delay(400);
  digitalWrite(13, LOW);
}

void parseState() {
  
  boolean disabled = (ENABLE_MASK & state) == 0;
  int carDirection = disabled ? 0 : (DIRECTION_MASK & state) >> 3;
  int carSpeed = disabled ? 0 : SPEED_MASK & state;
  
  digitalWrite(LEFT_PIN, LOW);
  digitalWrite(RIGHT_PIN, LOW);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(BACK_PIN, LOW);
  
  //Later on do PWM for now it is normal on-off no speed
  if (carSpeed != 0) {
    switch (carDirection) {
    
      case 1:
        digitalWrite(FORWARD_PIN, HIGH);
        digitalWrite(LEFT_PIN, HIGH);
        break;
    
      case 2:
        digitalWrite(FORWARD_PIN, HIGH);
        digitalWrite(RIGHT_PIN, HIGH);
        break;
    
      case 3:
        digitalWrite(BACK_PIN, HIGH);
        break;
        
      case 4:
        digitalWrite(BACK_PIN, HIGH);
        digitalWrite(LEFT_PIN, HIGH);
        break;
        
      case 5:
        digitalWrite(BACK_PIN, HIGH);
        digitalWrite(RIGHT_PIN, HIGH);
        break;
        
      default:
        digitalWrite(FORWARD_PIN, HIGH);
        blinkLed();
        break;
    
    }
  }
}

void loop() {
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  uint8_t newState = state;
  
  if (vw_get_message(buf, &buflen)) {
     blinkLed();
    
     for (int i = 0; i < buflen; i++) {
       newState = buf[i];
       
       if (newState & VALID_MASK) {
         state = newState;
         parseState();
         break;
       }       
     }
  }
}
