#include "hc573.h"


/**
 * @brief 选择74HC573锁存器的通道
 *
 * 该函数根据传入的通道号选择相应的74HC573锁存器通道。
 * 通过设置P2端口的特定位来实现对不同外设的片选操作。
 *
 * @param channel 要选择的通道号，可选值为 CS_LED、CS_ULN2003、CS_SMG_WELA、CS_SMG_DULA
 */
void SelectHC573(unsigned char channel)/*74HC573锁存器*/
{
	switch(channel)
	{
		case CS_LED: /*置位A2 -> 100 -> 00001000  片选LED锁存器*/
			P2 = (P2 & 0x1f) | 0x80;
		break;
		case CS_ULN2003:/*置位A0 A2 -> 片选ULN2003，控制继电器 蜂鸣器 步进电机*/
			P2 = (P2 & 0x1f) | 0xa0;
		break;
		case CS_SMG_WELA:/*置位A1 A2  片选位选*/
			P2 = (P2 & 0x1f) | 0xc0;
		break;
		case CS_SMG_DULA:/*置位A1 A2 A3  片选段选*/
			P2 = (P2 & 0x1f) | 0xe0;
		break;
	}
}