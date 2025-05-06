#ifndef _HC573_H_
#define _HC573_H_

#include "STC15F2K60S2.H"

#define CS_LED          4
#define CS_SMG_DULA     7
#define CS_SMG_WELA     6
#define CS_ULN2003      5

void SelectHC573(unsigned char channel);

#endif

