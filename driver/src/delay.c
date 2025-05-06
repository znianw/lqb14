#include "delay.h"
#include "INTRINS.H"

void delay_ms(unsigned char xms) //可以自己设置延时时间,12MHZ
{
	unsigned char i,j;
	for(i=xms;i>0;i--)
	  for(j=124;j>0;j--);
}

void Delay800ms(void)	//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 37;
	j = 123;
	k = 92;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay12us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 35;
	while (--i);
}
