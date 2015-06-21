#define RF_PIN 3

void setup() {
  pinMode(RF_PIN, OUTPUT);
}

void loop() {
  for (int i = 4000; i > 20; i -= i / 3) {
    digitalWrite(RF_PIN, HIGH);
    delay(2000);
     
    digitalWrite(RF_PIN,LOW);
    delay(i); 
  }
  
  delay(4000);
}
