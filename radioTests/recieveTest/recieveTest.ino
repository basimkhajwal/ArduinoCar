#include <VirtualWire.h>

#define LED_OUT 2
#define RF_PIN 3

void setup() {
  pinMode(LED_OUT, OUTPUT);
  digitalWrite(LED_OUT, LOW);
  
  vw_set_rx_pin(RF_PIN);
  vw_setup(500);
  
  vw_rx_start();
}

void loop() {
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  
  if (vw_get_message(buf, &buflen)) {
    for (int i = 0; i< buflen; i++) {
      if (buf[i] == '1') {
        digitalWrite(LED_OUT, HIGH);
      } else if (buf[i] == '0') {
        digitalWrite(LED_OUT, LOW);
      }
    }
  }
}
