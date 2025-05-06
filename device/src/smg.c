#include "stc15f2k60s2.h"
#include "smg.h"
#include "hc573.h"
#include "delay.h"




/**数码管段选编码 0-9,a-f,p,h,-,on,off*/
const unsigned char code smg_duan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
            0x88,0x83,0xc6,0xa1,0x86,0x8e,
			0x8c,0x89,0xbf,0x00,0xff};

/**硬件连接方式如下 */
/**
H138_A0  P2^5;
H138_A1  P2^6;
H138_A2  P2^7; 
COM1-COM8: Y6
a-dp: Y7 
D0-D7:P0*/
/*================*/


/**
 * @brief 数码管显示函数
 * 
 * 该函数用于控制数码管的显示，通过位选和段选信号选择要显示的数码管位置和数字。
 * 同时支持小数点的显示控制。
 * 
 * @param wela 数码管的位选信号，用于选择要点亮的数码管位置，最左边为第0个数码管
 * @param dula 数码管的段选信号，用于选择要显示的数字或字符，按照段选编码下标传入
 * @param point 小数点显示控制信号，非零值表示显示小数点
 */
void smg_display(unsigned char wela, unsigned char dula, unsigned char point)
{
	/**消隐 */
	P0 = 0xff; 					// 清除P0端口的显示内容
	SelectHC573(CS_SMG_DULA); 	// 选择数码管的段选锁存器
	P2 &= 0x1f;  				// 关闭段选锁存器选择

	P0 = 0x01 << wela;
	SelectHC573(CS_SMG_WELA);
	P2 &= 0x1f;

	P0 = smg_duan[dula];
	if (point) {
		P0 &= 0x7f;
	}
	SelectHC573(CS_SMG_DULA);
	P2 &= 0x1f;

}

