#ifndef UTILS_H
#define UTILS_H

// int16_t vShuntRaw;
// uint16_t vBusRaw;
// int16_t tempRaw;
// int16_t currentRaw;
// uint32_t powerRaw;

// =============== Calibration Constants ====================
extern const float R_SHUNT = 0.0005;    // 0.5 mΩ
extern const float CURRENT_LSB = 0.001; // 1 mA/bit

// =============== PWM buzzer ===============
extern const int buzzerChannel = 0;
extern const int buzzerFreq = 4000;
extern const int buzzerResolution = 8;

// =============== Paramètres thermistance ===============
extern const float Rseries = 10000.0;
extern const float R0 = 10000.0;
extern const float T0_K = 25.0 + 273.15;  // 25 °C en Kelvin
extern const float Bcoef = 3950.0;

// =============== Constantes CTN ===============
extern const float VCC = 3.3;
extern const float R_FIXED = 10000.0;     // Résistance fixe (pont diviseur)
extern const float BETA = 3950.0;         // Coefficient B de la CTN
extern const float T_REF = 298.15;        // 25°C en Kelvin

extern float CTNtemp1;
extern float CTNtemp2;



extern int16_t INA_vShuntRaw;
extern uint16_t INA_vBusRaw;
extern uint16_t INA_tempRaw;
extern int16_t INA_currentRaw;
extern uint16_t INA_powerRaw;

#endif