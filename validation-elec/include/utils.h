#ifndef UTILS_H
#define UTILS_H
 
#include <stdint.h>
// int16_t vShuntRaw;
// uint16_t vBusRaw;
// int16_t tempRaw;
// int16_t currentRaw;
// uint32_t powerRaw;
 
// =============== Calibration Constants ====================
extern const float R_SHUNT;
extern const float CURRENT_LSB;
 
// =============== PWM buzzer ===============
extern const int buzzerChannel;
extern const int buzzerFreq;
extern const int buzzerResolution;
 
// =============== Paramètres thermistance ===============
extern const float Rseries;
extern const float R0;
extern const float T0_K;  // 25 °C en Kelvin
extern const float Bcoef;
 
// =============== Constantes CTN ===============
extern const float VCC;
extern const float R_FIXED;     // Résistance fixe (pont diviseur)
extern const float BETA;         // Coefficient B de la CTN
extern const float T_REF;        // 25°C en Kelvin
 
extern float CTNtemp1;
extern float CTNtemp2;
 
 
 
extern int16_t INA_vShuntRaw;
extern uint16_t INA_vBusRaw;
extern uint16_t INA_tempRaw;
extern int16_t INA_currentRaw;
extern uint16_t INA_powerRaw;
 
#endif