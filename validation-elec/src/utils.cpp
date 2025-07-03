#include "utils.h"
#include <stdint.h>

const float R_SHUNT = 0.0005;
const float CURRENT_LSB = 0.001;
// ... all the other variables ...
const int buzzerChannel = 0;
const int buzzerFreq = 4000;
const int buzzerResolution = 8;
const float Rseries = 10000.0;
const float R0 = 10000.0;
const float T0_K = 25.0 + 273.15;
const float Bcoef = 3950.0;
const float VCC = 3.3;
const float R_FIXED = 10000.0;
const float BETA = 3950.0;
const float T_REF = 298.15;

float CTNtemp1;
float CTNtemp2;

int16_t INA_vShuntRaw;
uint16_t INA_vBusRaw;
uint16_t INA_tempRaw;
int16_t INA_currentRaw;
uint16_t INA_powerRaw;
