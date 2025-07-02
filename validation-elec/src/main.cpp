#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Attente active si liaison série non encore ouverte
  }

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}