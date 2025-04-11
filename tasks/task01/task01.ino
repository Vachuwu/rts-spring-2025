const int pin10ms = 3;
const int pin1ms = 5;
const int pin500us = 6;
const int pin100us = 9;
const int pin50us = 10;

int state10ms = LOW;
int state1ms = LOW;
int state500us = LOW;
int state100us = LOW;
int state50us = LOW;

unsigned long previousMillis10ms = 0;
unsigned long previousMillis1ms = 0;
unsigned long previousMicros500us = 0;
unsigned long previousMicros100us = 0;
unsigned long previousMicros50us = 0;

const long interval10ms = 10;        // период 10 мс 
const long interval1ms = 1;          // период 1 мс 
const long interval500us = 500;      // период 500 мкс 
const long interval100us = 100;      // период 100 мкс 
const long interval50us = 50;        // период 50 мкс 

void setup() {
  pinMode(pin10ms, OUTPUT);
  pinMode(pin1ms, OUTPUT);
  pinMode(pin500us, OUTPUT);
  pinMode(pin100us, OUTPUT);
  pinMode(pin50us, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long currentMicros = micros();

  if (currentMillis - previousMillis10ms >= interval10ms) {
    previousMillis10ms = currentMillis;
    state10ms = !state10ms;
    digitalWrite(pin10ms, state10ms);
  }


  if (currentMillis - previousMillis1ms >= interval1ms) {
    previousMillis1ms = currentMillis;
    state1ms = !state1ms;
    digitalWrite(pin1ms, state1ms);
  }

  if (currentMicros - previousMicros500us >= interval500us) {
    previousMicros500us = currentMicros;
    state500us = !state500us;
    digitalWrite(pin500us, state500us);
  }

  // Генерация 100 мкс импульса (50 мкс HIGH, 50 мкс LOW)
  if (currentMicros - previousMicros100us >= interval100us) {
    previousMicros100us = currentMicros;
    state100us = !state100us;
    digitalWrite(pin100us, state100us);
  }

  if (currentMicros - previousMicros50us >= interval50us) {
    previousMicros50us = currentMicros;
    state50us = !state50us;
    digitalWrite(pin50us, state50us);
  }
}