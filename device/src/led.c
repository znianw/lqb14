#include "led.h"
#include "hc573.h"




/**
 * @brief 控制指定地址的 LED 点亮或熄灭
 *
 * 该函数根据传入的地址和开关状态控制 LED 的显示。
 * 通过位操作设置 LED 的状态，并仅在状态改变时更新硬件。
 *
 * @param addr LED 的位地址，范围为 0 - 7，对应 8 个 LED
 * @param enable 控制开关，1 表示点亮 LED，0 表示熄灭 LED
 */
void led_display(unsigned char addr,bit enable)
{
	static unsigned char temp = 0x00;
	static unsigned char temp_old = 0xff;
	
    if(enable) {
        temp |= 0x01 <<addr;
    }
	else  {
        temp &= ~(0x01 <<addr);
    }

     // 检查当前状态是否与上一次状态不同 如果相同不需要改变LED的状态
	if(temp != temp_old) {
		P0 = ~temp;
        //SelectHC573(CS_LED);
        //调用函数更符合软件开发规范，但是51单片机资源有限，调用函数会增加开销，这里直接对P2进行位操作
		P2 = P2 & 0x1f | 0x80;
		P2 &= 0x1f;
		temp_old = temp;
	}
}

