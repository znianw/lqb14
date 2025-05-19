#include "STC15F2K60S2.H"
#include "smg.h"
#include "ds18b20.h"
#include "hc573.h"
#include "timer.h"
#include "key.h"
#include "led.h"



unsigned char Led_Buf[8] = {0, 0, 0,0,0,0,0,0};
unsigned char Smg_Buf[8] = {20, 20, 20, 20,20, 20, 20, 20};   /**OFF */
unsigned char Smg_Point[8] = {0, 0, 0,0,0,0,0,0};


typedef struct {
	unsigned char hour;
	unsigned char minutes;
	unsigned char second;
}Time;
Time current_time = {0};
Time last_time = {0};  //最后一次触发时间

typedef struct {
	unsigned char temp;
	unsigned char tempture_max;
	unsigned char tempture_prg;
	float temputre_avg;
}Tempture;
Tempture tempture = {0};

typedef struct {
	unsigned char hmdy;
	unsigned char humidity_max;
	float humidity_avg;
}Humidity;
Humidity humidity = {0};


unsigned char show_mode = 0;   /**0 时间  1 温度回显   2参数界面       10 湿度回旋 11时间回显  20温湿度界面*/
unsigned int sys_ticks = 0; /**系统时钟滴答 */

unsigned char trigger_count = 0; /**触发次数 */
unsigned char pos_index = 0;  /**数码管和LED显示索引 */


bit clear_flag = 0;  //数据清楚标志位
unsigned int time2s = 0;  //2s定时
void show_process(void);


void Sys_Init(void)
{
    P0 = 0xff;
    SelectHC573(CS_LED);
    P2 &= 0x1F;  //关闭LED
    
    P0 = 0x00;   //关蜂鸣器，继电器 步进电机
    SelectHC573(CS_ULN2003);
     P2 &= 0x1F; 
}

int main()
{
	Sys_Init();
	Timer1_Init();
	tempture.temp = read_tempture(1);   //先读一次温度，内部加了延迟，后续可以read_tempture(0)
	tempture.tempture_prg = 30;

	while(1) {
		show_process();
	}
	return 0;
}


void show_process(void)
{
	if (sys_ticks % 200 != 0) return;
	switch(show_mode) {
		case 0:  //时间
			Smg_Buf[0] = current_time.hour / 10;
			Smg_Buf[1] = current_time.hour % 10;
			Smg_Buf[2] = 18; /*"-"*/
			Smg_Buf[3] = current_time.minutes / 10;
			Smg_Buf[4] = current_time.minutes % 10;
			Smg_Buf[5] = 18;
			Smg_Buf[6] = current_time.second / 10;
			Smg_Buf[7] = current_time.second % 10;
			Smg_Point[6] = 0;
		break;

		case 1:  //温度回显
			Smg_Buf[0] = 12; /*c*/
			Smg_Buf[1] = 20; /**off */
			if (trigger_count != 0) {
				Smg_Buf[2] = tempture.tempture_max / 10;
				Smg_Buf[3] = tempture.tempture_max % 10;
				Smg_Buf[4] = 18; /*"-"*/
				Smg_Buf[5] = (int)tempture.temputre_avg / 10;
				Smg_Buf[6] = (int)tempture.temputre_avg % 10;
				Smg_Buf[7] = (int)(10 * tempture.temputre_avg) % 10;
				Smg_Point[6] = 1;
			}else {
				Smg_Buf[2] = Smg_Buf[3] = Smg_Buf[4] = Smg_Buf[5]= Smg_Buf[6]= Smg_Buf[7] = 20;
			}
			
		break;

		case 2: //参数界面
			Smg_Buf[0] = 16; /*p*/
			Smg_Buf[1] = 20; /**off */
			Smg_Buf[2] = 20; /**off */
			Smg_Buf[3] = 20; /**off */
			Smg_Buf[4] = 20; /**off */
			Smg_Buf[5] = 20; /**off */
			Smg_Buf[6] = tempture.tempture_prg / 10;
			Smg_Buf[7] = tempture.tempture_prg % 10;
			Smg_Point[6] = 0;
		break;

		case 10:  //湿度回显
			Smg_Buf[0] = 17; /*H*/
			Smg_Buf[1] = 20; /**off */
			if (trigger_count != 0) {
				Smg_Buf[2] = humidity.humidity_max / 10;
				Smg_Buf[3] = humidity.humidity_max % 10;
				Smg_Buf[4] = 18; /*"-"*/
				Smg_Buf[5] = (int)humidity.humidity_avg / 10;
				Smg_Buf[6] = (int)humidity.humidity_avg % 10;
				Smg_Buf[7] = (int)(10 * humidity.humidity_avg) % 10;
				Smg_Point[6] = 1;
			}else {
				Smg_Buf[2] = Smg_Buf[3] = Smg_Buf[4] = Smg_Buf[5]= Smg_Buf[6]= Smg_Buf[7] = 20;
				Smg_Point[6] = 0;
			}
			
		break;

		case 11: //时间回显
			Smg_Buf[0] = 15; /*F*/
			Smg_Buf[1] = trigger_count / 10;
			Smg_Buf[2] = trigger_count % 10;
			Smg_Point[6] = 0;
			if (trigger_count != 0) {
				Smg_Buf[3] = last_time.hour / 10;
				Smg_Buf[4] = last_time.hour % 10;
				Smg_Buf[5] = 18; /*"-"*/
				Smg_Buf[6] = last_time.minutes / 10;
				Smg_Buf[7] = last_time.minutes % 10;
			}else {
				Smg_Buf[3] = Smg_Buf[4] = Smg_Buf[5]= Smg_Buf[6]= Smg_Buf[7] = 20;
			}
			
		break;

		case 20: //温湿度界面
			Smg_Buf[0] = 14; /*E*/
			Smg_Buf[1] = 20;
			Smg_Buf[2] = 20;
			Smg_Buf[3] = tempture.temp / 10;
			Smg_Buf[4] = tempture.temp % 10;
			Smg_Buf[5] = 18;
			Smg_Buf[6] = humidity.hmdy / 10;
			Smg_Buf[7] = humidity.hmdy % 10;
			Smg_Point[6] = 0;
			/**无效数据的处理 */
		break;
	}
}


void key_process(void)
{
	static unsigned char Key_Val, Key_Down, Key_Up, Key_Old;
    if(sys_ticks % 50 || show_mode == 20) {  
        return; 
    }
    
    Key_Val = Key_Matrix_Scan();

    /**官方提供的消抖代码 */
    Key_Down = Key_Val & (Key_Old ^ Key_Val);
	Key_Up = ~Key_Val & (Key_Old ^ Key_Val);
	Key_Old = Key_Val;

	 /**0 时间  1 温度回显   2参数界面       10 湿度回显 11时间回显  20温湿度界面*/
	if (Key_Down == KEY_S4) {//S4
		if (show_mode == 10 || show_mode == 11 || show_mode == 1) {
			show_mode = 2;
		}else if (show_mode == 0) {
			show_mode = 1;
		}else if (show_mode == 2) {
			show_mode = 0;
		}
	} else if(Key_Down == KEY_S5) {//S5
		if (show_mode == 1){
			show_mode = 10;
		} else if(show_mode == 10) {
			show_mode == 11;
		}else if (show_mode == 11) {
			show_mode = 1;
		}
	}else if (Key_Down == KEY_S8) {
		if (show_mode == 2) {
			tempture.tempture_prg++;
		}
	}else if (Key_Down == KEY_S9) {
		if (show_mode == 2) {
			tempture.tempture_prg--;
		}else if (show_mode == 11) {
			//时间回显界面
			clear_flag = 1;
		}
	}

	if (time2s == 2001) { //>2s定时时间
		clear_flag = 0;
		time2s = 0;
		trigger_count = 0;
	}
}

void led_process(void)
{
	(show_mode == 0) ? (Led_Buf[0] = LED_ON) : (Led_Buf[0] = LED_OFF);
	(show_mode == 1 || show_mode == 10 || show_mode == 11) ? (Led_Buf[1] = LED_ON) : (Led_Buf[1] = LED_OFF);
	(show_mode == 20) ? (Led_Buf[1] = LED_ON) : (Led_Buf[1] = LED_OFF);

}

/**
 * @brief 定时器1中断服务函数
 *
 * 该函数在定时器1产生中断时被调用，用于处理系统的定时任务，
 * 包括更新系统时钟滴答、数码管显示、LED显示和继电器控制等。
 *
 * @param 无
 * @return 无
 */
void Timer1_Handler(void) interrupt 3
{
    sys_ticks=(++sys_ticks) % 1000;

    pos_index = (++pos_index) % 8;
    smg_display(pos_index, Smg_Buf[pos_index], Smg_Point[pos_index]);
    led_display(pos_index, Led_Buf[pos_index]);

	if (clear_flag == 1) { //清零键被按下
		if (time2s >= 2000) {
			time2s = 2001;
		}
	}
}

