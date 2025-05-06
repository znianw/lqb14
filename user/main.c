#include "STC15F2K60S2.H"



unsigned char Led_Buf[8] = {0, 0, 0,0,0,0,0,0};
unsigned char Smg_Buf[8] = {20, 20, 20, 20,20, 20, 20, 20};   /**OFF */
unsigned char Smg_Point[8] = {0, 0, 0,0,0,0,0,0};


typedef struct {
	unsigned char hour;
	unsigned char minutes;
	unsigned char second;
}Time;
Time current_time = {0};

unsigned char show_mode = 0;   /**0 时间  1 温度回显   2参数界面       10 湿度回旋 11时间回显  20温湿度界面*/


void show_process(void);

int main()
{
	return 0;
}


void show_process(void)
{
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
		break;

		case 1:
		break;

		case 2:
		break;

		case 10:
		break;

		case 11:
		break;

		case 20:
		break;


	}
}
