#include <VirtualWire.h>

#define RF_PIN 10

void setup() {
  vw_set_tx_pin(RF_PIN);
  vw_setup();
}

void loop() {
  
  if (Serial.available()) {
    char c = Serial.read();
    
    
  }
  
}
