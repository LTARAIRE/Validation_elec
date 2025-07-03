#ifndef IOS_H
#define IOS_H

// =============== INA237 Register Addresses ===============
#define INA237_ADDR      0x40  // Change if A0/A1 are wired differently
#define REG_CONFIG       0x00
#define REG_ADC_CONFIG   0x01
#define REG_SHUNT_CAL    0x02
#define REG_VSHUNT       0x04
#define REG_VBUS         0x05
#define REG_DIETEMP      0x06
#define REG_CURRENT      0x07
#define REG_POWER        0x08
// === Broches LEDs ===
const int ledRouge   =   15;
const int ledVerte   =   14;
const int buzzerPin  =   13;

// Broches des CTN
const int CTN1_PIN   =   26;
const int CTN2_PIN   =   25;

#endif