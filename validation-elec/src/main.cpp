#include <Arduino.h>

#include <Wire.h>
 
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
 
// =============== Calibration Constants ====================

const float R_SHUNT = 0.0005;    // 0.5 mΩ

const float CURRENT_LSB = 0.001; // 1 mA/bit
 
uint16_t calcShuntCal() {

  // SHUNT_CAL = 0.00512 / (Current_LSB * R_SHUNT)

  return (uint16_t)(0.00512 / (CURRENT_LSB * R_SHUNT));

}
 
// =============== I2C Register Functions ===================

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
 
// =============== INA237 Initialization ====================

void setupINA237() {

  // CONFIG: Default range (±163.84mV shunt)

  writeRegister(REG_CONFIG, 0x0000);

  // ADC_CONFIG: Continuous mode, all channels, 1052 µs conversion

  writeRegister(REG_ADC_CONFIG, 0xFB68);

  // SHUNT_CAL: Calculated for your shunt/current_LSB

  writeRegister(REG_SHUNT_CAL, calcShuntCal());

}
 
// =============== Arduino Setup ============================

void setup() {

  Serial.begin(115200);

  Wire.begin(); // ESP32 default: SDA=21, SCL=22

  setupINA237();

  delay(100);

  Serial.printf("SHUNT_CAL = %u\n", calcShuntCal());

}
 
// =============== Main Loop ===============================

void loop() {

  // Read Raw Registers

  int16_t vShuntRaw = readRegister16Signed(REG_VSHUNT);   // 5µV/LSB, signed

  uint16_t vBusRaw = readRegister16(REG_VBUS);            // 3.125mV/LSB, unsigned

  int16_t tempRaw = readRegister16(REG_DIETEMP);          // bits [15:4]: signed 12b, 0.125°C/LSB

  int16_t currentRaw = readRegister16Signed(REG_CURRENT); // Signed, LSB set by SHUNT_CAL

  uint32_t powerRaw = readRegister24(REG_POWER);          // Unsigned
 
  // Decode/Convert Values

  float vBus = vBusRaw * 0.003125;            // Volts

  float vShunt = vShuntRaw * 0.000005;        // Volts (5uV/LSB)

  int16_t temp12 = tempRaw >> 4;              // Sign-extend

  float temperature = temp12 * 0.125;         // °C

  float current = currentRaw * CURRENT_LSB;   // Amps

  // Power per datasheet: Power = Power Register × Power_LSB

  // Power_LSB = Current_LSB × VBUS_LSB (VBUS_LSB = 3.125 mV)

  float power = powerRaw * CURRENT_LSB * 0.003125; // Watts
 
  // Serial Output

  Serial.println("------ INA237 Measurements ------");

  Serial.printf("Bus Voltage   : %.3f V\n", vBus);

  Serial.printf("Shunt Voltage : %.6f V\n", vShunt);

  Serial.printf("Current       : %.3f A\n", current);

  Serial.printf("Power         : %.3f W\n", power);

  Serial.printf("Temperature   : %.2f °C\n", temperature);

  Serial.println("----------------------------------\n");
 
  delay(1000);

}

 