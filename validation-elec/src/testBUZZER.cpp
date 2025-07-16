#include "testBUZZER.h"
#include "utils.h"
#include "IOs.h"
#include <Arduino.h>

void setupBuzzer() {
  ledcSetup(buzzerChannel, buzzerFreq, buzzerResolution);
  ledcAttachPin(buzzerPin, buzzerChannel);
}

void testBuzzer() {
  Serial.println("Test buzzer : 3 bips courts");

  for (int i = 0; i < 3; i++) {
    ledcWriteTone(buzzerChannel, 1000); // Bip à 1000 Hz
    delay(200);                         // Durée du bip (ms)
    ledcWriteTone(buzzerChannel, 0);    // Arrêt du son
    delay(150);                         // Pause entre les bips
  }

  Serial.println("Fin du test buzzer.");
}
