#ifndef _DS1302_H_
#define _DS1302_H_

#include "STC15F2K60S2.H"

#define Ds1302_Read_Hour() Read_Ds1302_Byte(0x85)
#define Ds1302_Read_Min() Read_Ds1302_Byte(0x83)
#define Ds1302_Read_Sec() Read_Ds1302_Byte(0x81)


void DS1302_WriteByte(unsigned char addr, unsigned char dat);
unsigned char Read_Ds1302_Byte ( unsigned char address );
void Set_time(unsigned char hour, unsigned char min, unsigned char sec);

void ds1302_get_time(unsigned char* hour, unsigned char* min, unsigned char* sec);

#endif
