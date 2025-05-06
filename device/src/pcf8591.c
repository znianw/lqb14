#include "pcf8591.h"
#include "i2c.h"


/**
 * @brief 从PCF8591模数转换器读取指定通道的数据
 * 
 * 该函数通过I2C总线与PCF8591通信，发送写地址和通道地址，然后切换到读取模式，最后读取指定通道的数据
 * 
 * @param addr 要读取的PCF8591通道地址，滑动变阻器或光敏电阻
 * @return unsigned char 从指定通道读取的8位数据 返回的是数字量
 */
unsigned char PCF8591_Read(unsigned char addr)
{
	unsigned char temp;
	I2CStart();
	I2CSendByte(PCF8591_WRITE_ADDR);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(PCF8591_READ_ADDR);
	I2CWaitAck();
	temp = I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
	return temp;
}


/**
 * @brief 向PCF8591的数模转换器（DAC）写入数据
 * 
 * 该函数通过I2C总线与PCF8591进行通信，向其DAC写入指定的数据
 * 
 * @param dat 要写入PCF8591 DAC的8位数据，最大255
 */
void PCF8591_DA_Write(unsigned char dat)
{
    I2CStart();
	I2CSendByte(PCF8591_WRITE_ADDR);
	I2CWaitAck();
	I2CSendByte(0x40);   //使能模拟输出
	I2CWaitAck();
	I2CSendByte(dat);
	I2CWaitAck();
}