#define RF_PIN 3
#define LED_OUT 2

void setup() {
  pinMode(LED_OUT, OUTPUT);
  pinMode(RF_PIN, OUTPUT);
}

void loop() {
  for (int i = 4000; i > 20; i -= i / 3) {
    digitalWrite(RF_PIN, HIGH);
    digitalWrite(LED_OUT, HIGH);
    delay(2000);
     
    digitalWrite(RF_PIN, LOW);
    digitalWrite(LED_OUT, LOW);
    delay(i); 
  }
  
  delay(4000);
}
