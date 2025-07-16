#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>
#include <math.h>


#include "utils.h"
#include "testADC.h"
#include "testBUZZER.h"
#include "testCTN.h"
#include "testLED.h"
#include "testINA.h"
#include "IOs.h"
#include "testBLE.h"

void setup() {

  Serial.begin(115200);

  Wire.begin(); // ESP32 default: SDA=21, SCL=22
  setupINA237();
  setupADC();
  setupBuzzer();
  setupCTN();
  setupLED();
  testBuzzer();
  testBLE();

  delay(100);

}
 
// =============== Main Loop ===============================

void loop() {
  testCTN();
  testLED();
  testINA();
  delay(1000);
}
