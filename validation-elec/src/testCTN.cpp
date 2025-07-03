#include <Arduino.h>
#include <math.h>
#include "IOs.h"
#include "testCTN.h"
#include "utils.h"


void setupCTN() {
  analogReadResolution(12);       // Résolution ADC ESP32
  analogSetAttenuation(ADC_11db); // Plage de lecture étendue (0-3.3V)
}

float readTemperature(int pin) {
  int adc = analogRead(pin);
  if (adc == 0 || adc >= 4095) return -999.0;  // erreur ou CTN non connectée

  float V = (adc / 4095.0) * VCC;
  float R = R_FIXED * (V / (VCC - V));
  float tempK = 1.0 / (1.0 / T_REF + log(R / R0) / BETA);
  return tempK - 273.15;
}

void testCTN() {
  
  CTNtemp1 = readTemperature(CTN1_PIN);
  CTNtemp2 = readTemperature(CTN2_PIN);

  Serial.printf("CTN1 : %.2f °C\n", CTNtemp1);
  Serial.printf("CTN2 : %.2f °C\n\n", CTNtemp2);
  delay(1000);
}