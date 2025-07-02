#include <Wire.h>
#include <Arduino.h>
 
#define INA237_ADDR 0x40  // Adresse par défaut, à adapter si nécessaire
#define SDA_PIN 21
#define SCL_PIN 22
 
void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN, 400000);
  Serial.println("INA237 - Test démarré");
}


uint16_t readRegister(uint8_t reg) {
  Wire.beginTransmission(INA237_ADDR);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) {
    Serial.println("Erreur I2C");
    return 0;
  }
 
  Wire.requestFrom(INA237_ADDR, (uint8_t)2);
  if (Wire.available() == 2) {
    uint16_t value = (Wire.read() << 8) | Wire.read();
    return value;
  }
  return 0;
}
 
float readShuntVoltage() {
  int16_t raw = (int16_t)readRegister(0x04);
  return raw * 0.005;  // 5µV/LSB => conversion en mV
}
 
float readBusVoltage() {
  uint16_t raw = readRegister(0x05);
  return raw * 0.003125;  // 3.125mV/LSB => conversion en V
}
 
float readCurrent() {
  int16_t raw = (int16_t)readRegister(0x07);
  float current_LSB = 0.001;  // Exemple : 1mA par LSB, à ajuster en fonction de SHUNT_CAL
  return raw * current_LSB; 
}
 
float readPower() {
  uint16_t msb = 0, lsb = 0;
  Wire.beginTransmission(INA237_ADDR);
  Wire.write(0x08);
  if (Wire.endTransmission(false) != 0) {
    Serial.println("Erreur lecture Power");
    return 0;
  }
  Wire.requestFrom(INA237_ADDR, (uint8_t)3);
  if (Wire.available() == 3) {
    uint32_t raw = ((uint32_t)Wire.read() << 16) | ((uint16_t)Wire.read() << 8) | Wire.read();
    float power_LSB = 0.025;  // Exemple : 25mW par LSB, dépend de SHUNT_CAL
    return raw * power_LSB;
  }
  return 0;
}

void loop() {
  float vshunt_mV = readShuntVoltage();
  float vbus_V = readBusVoltage();
  float current_mA = readCurrent();
  float power_mW = readPower();
 
  Serial.print("Vshunt = "); Serial.print(vshunt_mV); Serial.println(" mV");
  Serial.print("Vbus   = "); Serial.print(vbus_V); Serial.println(" V");
  Serial.print("Courant= "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Puissance = "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("---------------------------");
 
  delay(1000);
}
 