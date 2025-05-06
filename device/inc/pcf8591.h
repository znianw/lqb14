#ifndef _PCF8591_H_
#define _PCF8591_H_

#include "stc15f2k60s2.h"

#define PCF8591_READ_ADDR   0x91
#define PCF8591_WRITE_ADDR  0x90


#define PCF8591_CH0
#define PCF8591_CH1     0x01    //光敏电阻
#define PCF8591_CH2
#define PCF8591_CH3     0x03    //滑动变阻器

unsigned char PCF8591_Read(unsigned char addr);
void PCF8591_DA_Write(unsigned char dat);

#endif
