#ifndef _LED_H_
#define _LED_H_

#include "stc15f2k60s2.h"

#define LED_OFF         0
#define LED_ON          1

void led_display(unsigned char addr,bit enable);

#endif
