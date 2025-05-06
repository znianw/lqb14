#ifndef _KEY_H_
#define _KEY_H_

#include "stc15f2k60s2.h"


#define KEY_S4      4
#define KEY_S5      5
#define KEY_S6      6
#define KEY_S7      7
#define KEY_S8      8
#define KEY_S9      9
#define KEY_S10      10
#define KEY_S11      11
#define KEY_S12      12
#define KEY_S13      13
#define KEY_S14      14
#define KEY_S15      15
#define KEY_S16      16
#define KEY_S17      17
#define KEY_S18      18
#define KEY_S19      19

#define KEY_R1C1    KEY_S7
#define KEY_R2C1    KEY_S6
#define KEY_R3C1    KEY_S5
#define KEY_R4C1    KEY_S4

#define KEY_R1C2    KEY_S11
#define KEY_R2C2    KEY_S10
#define KEY_R3C2    KEY_S9
#define KEY_R4C2    KEY_S8

#define KEY_R1C3    KEY_S15
#define KEY_R2C3    KEY_S14
#define KEY_R3C3    KEY_S13
#define KEY_R4C3    KEY_S12

#define KEY_R1C4    KEY_S19
#define KEY_R2C4    KEY_S18
#define KEY_R3C4    KEY_S17
#define KEY_R4C4    KEY_S16

unsigned char Key_Matrix_Scan(void);





#endif
