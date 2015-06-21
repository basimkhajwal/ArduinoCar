#define LED_OUT 2

const unsigned int upperThreshold = 70;
const unsigned int lowerThreshold = 50;
unsigned int readData = 0;

void setup() {
  pinMode(LED_OUT, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  readData = analogRead(A0);
  
  if (readData > upperThreshold) {
    digitalWrite(LED_OUT, HIGH);
    Serial.println(data);
  }
  
  if (readData < lowerThreshold) {
    digitalWrite(LED_OUT, HIGH);
    Serial.println(data);
  }
}
