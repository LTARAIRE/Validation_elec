#include <stdint.h>
#include <math.h>
#include <Arduino.h>
#include <Wire.h>

#include "testINA.h"
#include "utils.h"
#include "IOs.h"



void setupINA237() {
  // CONFIG: Default range (±163.84mV shunt)
  writeRegister(REG_CONFIG, 0x0000);

  // ADC_CONFIG: Continuous mode, all channels, 1052 µs conversion
  writeRegister(REG_ADC_CONFIG, 0xFB68);

  // SHUNT_CAL: Calculated for the shunt/current_LSB
  writeRegister(REG_SHUNT_CAL, calcShuntCal());

}
 
uint16_t calcShuntCal() {
  // SHUNT_CAL = 0.00512 / (Current_LSB * R_SHUNT)
  return (uint16_t)(0.00512 / (CURRENT_LSB * R_SHUNT));
}
 
void writeRegister(uint8_t reg, uint16_t value) {

  Wire.beginTransmission(INA237_ADDR);

  Wire.write(reg);

  Wire.write(value >> 8);

  Wire.write(value & 0xFF);

  Wire.endTransmission();

}
 
uint16_t readRegister16(uint8_t reg) {

  Wire.beginTransmission(INA237_ADDR);

  Wire.write(reg);

  Wire.endTransmission(false);

  Wire.requestFrom(INA237_ADDR, 2);

  uint16_t msb = Wire.read();

  uint16_t lsb = Wire.read();

  return (msb << 8) | lsb;

}
 
int16_t readRegister16Signed(uint8_t reg) {

  return (int16_t)readRegister16(reg);

}
 
uint32_t readRegister24(uint8_t reg) {

  Wire.beginTransmission(INA237_ADDR);

  Wire.write(reg);

  Wire.endTransmission(false);

  Wire.requestFrom(INA237_ADDR, 3);

  uint32_t msb = Wire.read();

  uint32_t mid = Wire.read();

  uint32_t lsb = Wire.read();

  return (msb << 16) | (mid << 8) | lsb;

}

void readINA() {
  INA_vShuntRaw   = readRegister16Signed(REG_VSHUNT);   // 5µV/LSB, signed
  INA_vBusRaw     = readRegister16(REG_VBUS);            // 3.125mV/LSB, unsigned
  INA_tempRaw     = readRegister16(REG_DIETEMP);          // bits [15:4]: signed 12b, 0.125°C/LSB
  INA_currentRaw  = readRegister16Signed(REG_CURRENT); // Signed, LSB set by SHUNT_CAL
  INA_powerRaw    = readRegister24(REG_POWER);          // Unsigned
}

void testINA() {
// Decode/Convert Values

  float   INA_vBus        = INA_vBusRaw * 0.003125;            // Volts
  float   INA_vShunt      = INA_vShuntRaw * 0.000005;        // Volts (5uV/LSB)
  int16_t INA_temp12      = INA_tempRaw >> 4;              // Sign-extend
  float   INA_temperature = INA_temp12 * 0.125;         // °C
  float   INA_current     = INA_currentRaw * CURRENT_LSB;   // Amps

  // Power = Power Register × Power_LSB
  float power = INA_powerRaw * CURRENT_LSB * 0.003125; // Watts
  
  // Power_LSB = Current_LSB × VBUS_LSB (VBUS_LSB = 3.125 mV)
 
  // Serial Output

  Serial.println("------ INA237 Measurements ------");
  Serial.printf("SHUNT_CAL = %u\n", calcShuntCal());
  Serial.printf("Bus Voltage   : %.3f V\n", INA_vBus);
  Serial.printf("Shunt Voltage : %.6f V\n", INA_vShunt);
  Serial.printf("Current       : %.3f A\n", INA_current);
  Serial.printf("Power         : %.3f W\n", power);
  Serial.printf("Temperature   : %.2f °C\n", INA_temperature);
  Serial.println("----------------------------------\n");

}