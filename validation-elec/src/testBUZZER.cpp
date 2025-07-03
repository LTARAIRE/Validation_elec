#include <Arduino.h>
#include "testBUZZER.h" 
#include "utils.h" 
#include "IOs.h" 


void setupBuzzer() {
    ledcSetup(buzzerChannel, buzzerFreq, buzzerResolution);
    ledcAttachPin(buzzerPin, buzzerChannel);
}

void testBuzzer() {
  for (int i = 0; i < 3; i++) {
    Serial.printf("Bip %d...\n", i + 1);
    ledcWriteTone(buzzerChannel, buzzerFreq);
    delay(500);
    ledcWriteTone(buzzerChannel, 0);
    delay(1000);
  }
  Serial.println(">>> Test buzzer terminé. Lecture CTN en continu...");
}
