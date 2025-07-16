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
  delay(500);
  digitalWrite(ledRouge, LOW);
  digitalWrite(ledVerte, HIGH);
  delay(500);
  digitalWrite(ledVerte, LOW);
  delay(100);
}

