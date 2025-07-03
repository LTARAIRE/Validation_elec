#include <Arduino.h>
#include "testADC.h"
#include "IOs.h"
// #include "utils.h"



void setupADC() {
    adcAttachPin(CTN1_PIN);
    adcAttachPin(CTN2_PIN);
    analogSetAttenuation(ADC_11db); // Plage max (0 – 3.3 V)
}