#include <Arduino.h>

int ledRouge = 17;  // Broche de la LED rouge
int ledVerte = 21;  // Broche de la LED verte

void setup() {
  Serial.begin(115200); // Initialisation de la communication série
  
  pinMode(ledRouge, OUTPUT); // LED rouge en sortie
  pinMode(ledVerte, OUTPUT); // LED verte en sortie
}

void loop() {
  digitalWrite(ledRouge, HIGH);  // Allume la LED rouge
  digitalWrite(ledVerte, HIGH);  // Allume la LED verte

  Serial.println("LED rouge et LED verte allumées");
  
  // Les LED restent allumées en continu
}