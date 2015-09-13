#include <VirtualWire.h>

#define RF_PIN 3

void setup() {
  vw_set_rx_pin(RF_PIN);
  vw_setup(500);
  
  vw_rx_start();
}

void loop() {
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  
  if (vw_get_message(buf, &buflen)) {
    
  }
}
