
#include "ds18b20.h"
#include "delay.h"


sbit DQ = P1^4;

/**
 * @brief 为单总线通信提供延时。
 * 
 * 该函数通过循环递减计数器来实现延时，延时时间由传入的参数决定。
 * 计数器先乘以 12 以调整延时精度，然后在循环中递减直至为 0。
 * 
 * @param t 延时时间参数，实际延时时间与该参数值成正比。
 */
void delay_onewrite(unsigned char t)
{
    unsigned char i = 0;
    while(t--) {
        for(i = 0; i<12; i++);
    }
}

void write_ds18b20(unsigned char dat)
{
    unsigned char i;
    for(i = 0; i < 8; i++) {
        DQ = 0;
        DQ = dat&0x01;
        delay_onewrite(5);
        DQ = 1;
        dat >>= 1;
    }
    delay_onewrite(5);
}

unsigned char read_ds18b20(void)
{
    unsigned char i;
    unsigned char dat;

    for(i = 0; i < 8; i++) {
        DQ = 0;
        dat >>= 1;
        DQ = 1;
        if (DQ) {
            dat |= 0x80;
        }
        delay_onewrite(5);
    }

    return dat;
}

/**
 * @brief 初始化 DS18B20 温度传感器。
 * 
 * 该函数按照 DS18B20 的初始化时序要求，通过控制单总线 DQ 的电平并结合延时操作，
 * 完成对 DS18B20 的初始化过程，并返回初始化是否成功的标志位。
 * 
 * @return bit 初始化成功标志位，0 表示初始化失败，1 表示初始化成功。
 */
bit init_ds18b20(void)
{
    bit initflag = 0;

    DQ = 1;
    delay_onewrite(12);

    DQ = 0;
    delay_onewrite(80);

    DQ = 1;
    delay_onewrite(10);

    initflag = DQ;
    delay_onewrite(5);

    return initflag;
}



/**
 * @brief 读取 DS18B20 温度传感器的温度值。
 * 
 * 该函数通过一系列操作与 DS18B20 温度传感器进行通信，
 * 先启动温度转换，然后读取转换后的温度数据，
 * 最后将读取到的原始数据转换为实际的温度值并返回。
 * 
 * @return float 读取到的温度值，单位为摄氏度。
 */
float read_tempture(bit first_read_flag)
{
    unsigned char low, high;

	init_ds18b20();
    // 发送跳过 ROM 指令，直接对 DS18B20 进行操作
	write_ds18b20(0xcc);
    // 发送启动温度转换指令
	write_ds18b20(0x44);

    if (first_read_flag)
        Delay800ms();
	
    // 再次初始化 DS18B20 传感器，准备读取温度数据
	init_ds18b20();
    // 发送跳过 ROM 指令，直接对 DS18B20 进行操作
	write_ds18b20(0xcc);
    // 发送读取温度寄存器指令
	write_ds18b20(0xbe);
    // 读取温度数据的低 8 位
    low = read_ds18b20();
    // 读取温度数据的高 8 位
    high = read_ds18b20();

    // 将高 8 位和低 8 位数据合并，并除以 16.0 转换为实际的温度值
    return (float)((high << 8) | low) / 16.0;
}