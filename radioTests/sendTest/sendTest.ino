#include <VirtualWire.h>

#define RF_PIN 3
#define LED_OUT 2

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_OUT, OUTPUT);
  digitalWrite(LED_OUT, LOW);
  
  vw_set_tx_pin(RF_PIN);
  vw_setup(500);
}

void loop() {
  
  if (Serial.available()){
    char c  = Serial.read();
    
    if (c == '1' || c == '0') {
      vw_send((uint8_t *) c, 1);
      
      if (c == '1') {
        digitalWrite(LED_OUT, HIGH);
      } else {
        digitalWrite(LED_OUT, LOW);
      }
    }
  }
}
