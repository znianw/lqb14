#include "ds1302.h"
#include "intrins.h"
 
sbit CLK=P1^7;
sbit SDA=P2^3;
sbit RST=P1^3;


void DS1302_WriteByte(unsigned char addr, unsigned char dat)
{
        unsigned char n;
        RST = 0;
        _nop_();
        CLK = 0;
        _nop_();
        RST = 1;
        _nop_();        

        for (n=0; n<8; n++) {        //发送要写入数据的内存地址
        
                SDA = addr & 0x01;
                addr >>= 1;
                CLK = 1;
                _nop_();
                CLK = 0;
                _nop_();
        }
        for (n=0; n<8; n++)  {       //将指定内容写入该地址的内存
                SDA = dat & 0x01;
                dat >>= 1;
                CLK = 1;
                _nop_();
                CLK = 0;
                _nop_();
        }                 
        RST = 0;
        _nop_();
}


unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	CLK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		CLK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		CLK=1;
	} 
 	RST=0;	_nop_();
 	CLK=0;	_nop_();
	CLK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}
 
void Set_time(unsigned char hour, unsigned char min, unsigned char sec)
{
	Write_Ds1302_Byte(0x8e, 0x00);
	Write_Ds1302_Byte(0x80, sec);
	Write_Ds1302_Byte(0x82, min);
	Write_Ds1302_Byte(0x84, hour);
	Write_Ds1302_Byte(0x8e, 0x80);
}


