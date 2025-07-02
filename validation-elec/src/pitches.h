#include <Arduino.h>
#include <math.h>

// --- Broches actuateurs ---
const int ledRouge = 3;
const int ledVerte = 1;
const int buzzerPin = 13;

// --- Broches capteurs ---
const int ctn1Pin = 34;  // MES_NTC_1
const int ctn2Pin = 33;  // MES_NTC_2

// --- PWM buzzer ---
const int buzzerChannel = 0;
const int buzzerFreq = 4000;
const int buzzerResolution = 8;

// --- Paramètres thermistance ---
const float Vcc = 3.3;
const float Rseries = 10000.0;         // Résistance de pull-down
const float R0 = 10000.0;              // Valeur nominale de la CTN à 25°C
const float T0_K = 25.0 + 273.15;      // Température de référence en Kelvin
const float Bcoef = 3950.0;            // Coefficient Beta de la CTN

void setup() {
  Serial.begin(115200);

  // LEDs
  pinMode(ledRouge, OUTPUT);
  pinMode(ledVerte, OUTPUT);
  digitalWrite(ledRouge, HIGH);
  digitalWrite(ledVerte, HIGH);

  // Buzzer PWM
  ledcSetup(buzzerChannel, buzzerFreq, buzzerResolution);
  ledcAttachPin(buzzerPin, buzzerChannel);

  // CTN
  pinMode(ctn1Pin, INPUT);
  pinMode(ctn2Pin, INPUT);

  Serial.println("Initialisation terminée.");
  Serial.println("LED rouge et LED verte allumées.");

  // Bip 3 fois
  for (int i = 0; i < 3; i++) {
    Serial.printf("Bip %d...\n", i + 1);
    ledcWriteTone(buzzerChannel, buzzerFreq);
    delay(500);
    ledcWriteTone(buzzerChannel, 0);
    delay(1000);
  }

  Serial.println("Séquence buzzer terminée. Passage en mode surveillance CTN...");
}

void loop() {
  // Lecture CTN1
  int raw1 = analogRead(ctn1Pin);
  float voltage1 = raw1 * (Vcc / 4095.0);
  float Rntc1 = Rseries * (Vcc / voltage1 - 1.0);
  float tempK1 = 1.0 / ((1.0 / T0_K) + (1.0 / Bcoef) * log(Rntc1 / R0));
  float tempC1 = tempK1 - 273.15;

  // Lecture CTN2
  int raw2 = analogRead(ctn2Pin);
  float voltage2 = raw2 * (Vcc / 4095.0);
  float Rntc2 = Rseries * (Vcc / voltage2 - 1.0);
  float tempK2 = 1.0 / ((1.0 / T0_K) + (1.0 / Bcoef) * log(Rntc2 / R0));
  float tempC2 = tempK2 - 273.15;

  // Affichage
  Serial.println("------ CTN Monitoring ------");
  Serial.printf("CTN1: ADC=%4d, V=%.2f V, R=%.0f Ω, T=%.2f °C\n", raw1, voltage1, Rntc1, tempC1);
  Serial.printf("CTN2: ADC=%4d, V=%.2f V, R=%.0f Ω, T=%.2f °C\n", raw2, voltage2, Rntc2, tempC2);
  Serial.println("----------------------------");

  delay(1000);  // 1 lecture par seconde
}
