#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Attente active si liaison série non encore ouverte
  }

  Serial.println("Démarrage de la carte ELECE...");
}

void loop() {
  Serial.println("Hello, world!");
  delay(1000);
}
