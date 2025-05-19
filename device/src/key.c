#include "key.h"

sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;

//sbit C4 = P3^4;
sbit C3 = P3^5;
sbit C2 = P4^2;
sbit C1 = P4^4;

/**
 * @brief 矩阵键盘扫描函数
 *
 * 该函数用于扫描 4x4 矩阵键盘，检测按键按下事件，并返回按键对应的键值。
 * 通过逐列扫描的方式，检测每一列上的按键状态，若检测到按键按下，则更新键值。
 *
 * @param 无
 * @return 按键对应的键值，若没有按键按下则返回 0
 * @note 如果有需要使用555芯片，需要注释掉P34端口相关，否则会引起硬件冲突，这里只考虑了判断哪个
 *       按键按下，此外按下和松开分别实现不同功能、长按生效、短按生效等考点也经常考
 */
unsigned char Key_Matrix_Scan(void)
{
	unsigned char temp = 0;

	C1 = 0;
	C2 = 1;
	C3 = 1;
	//C4 = 1;
	if (R1 == 0)
		temp = KEY_R1C1;
	if (R2 == 0)
		temp = KEY_R2C1;
	if (R3 == 0)
		temp = KEY_R3C1;
	if (R4 == 0)
		temp = KEY_R4C1;

	C1 = 1;
	C2 = 0;
	C3 = 1;
	//C4 = 1;
	if (R1 == 0)
        temp = KEY_R1C2;
	if (R2 == 0)
		temp = KEY_R2C2;
	if (R3 == 0)
		temp = KEY_R3C2;
	if (R4 == 0)
		temp = KEY_R4C2;

	if (R3 == 0 && R4 == 0)
		temp = 89;
	C1 = 1;
	C2 = 1;
	C3 = 0;
	//C4 = 1;
	if (R1 == 0)
		temp = KEY_R1C3;
	if (R2 == 0)
		temp = KEY_R2C3;
	if (R3 == 0)
		temp = KEY_R3C3;
	if (R4 == 0)
		temp = KEY_R4C3;

#if 0
	C1 = 1;
	C2 = 1;
	C3 = 1;
	C4 = 0;
	if (R1 == 0)
		temp = KEY_R2C4;
	if (R2 == 0)
		temp = KEY_R2C4;
	if (R3 == 0)
		temp = KEY_R3C4;
	if (R4 == 0)
		temp = KEY_R4C4;
#endif
	return temp;
}
