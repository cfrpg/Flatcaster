#ifndef _KEYS_H
#define _KEYS_H

#include "sys.h"

#define KEY_A PCin(14)
#define KEY_B PCin(15)

extern u32 KeyStatus[2];

void KeysInit(void);
void KeysUpdate(void);

#endif