#ifndef _I2C_H_
#define _I2C_H_

#include "stc15f2k60s2.h"

void I2CStart(void);
void I2CStop(void);
void I2CSendByte(unsigned char byt);
unsigned char I2CReceiveByte(void);
unsigned char I2CWaitAck(void);
void I2CSendAck(unsigned char ackbit);

#endif
