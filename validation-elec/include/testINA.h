#ifndef TESTINA_H
#define TESTINA_H

uint16_t calcShuntCal();
void setupINA237();
void writeRegister(uint8_t reg, uint16_t value);
uint16_t readRegister16(uint8_t reg);
int16_t readRegister16Signed(uint8_t reg);
uint32_t readRegister24(uint8_t reg);
void readINA();
void testINA();
void convertINAData();

#endif