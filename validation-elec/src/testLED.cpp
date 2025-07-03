#include <Arduino.h>
#include "testLED.h"
#include "IOs.h"

void setupLED() {
  pinMode(ledRouge, OUTPUT);
  pinMode(ledVerte, OUTPUT);
}

void testLED() {
  digitalWrite(ledRouge, HIGH);
  digitalWrite(ledVerte, LOW);
  delay(100);
  digitalWrite(ledVerte, HIGH);
  digitalWrite(ledRouge, LOW);
  delay(100);
}

