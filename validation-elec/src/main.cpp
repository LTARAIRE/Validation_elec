#include <Arduino.h>
 
int ledRouge = 3;  // Broche de la LED rouge
int ledVerte = 1;  // Broche de la LED verte
 
void setup() {
  Serial.begin(9600); // Initialisation de la communication série
 
  pinMode(ledRouge, OUTPUT); // LED rouge en sortie
  pinMode(ledVerte, OUTPUT); // LED verte en sortie
}

void loop() {
  digitalWrite(ledRouge, HIGH);  // Allume la LED rouge
  digitalWrite(ledVerte, HIGH);  // Allume la LED verte
 
  Serial.println("LED rouge et LED verte allumées");
 
  // Les LED restent allumées en continu
}