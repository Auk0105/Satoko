#ifndef _RCV_H_
#define _RCV_H_

#include "Omni_3.h"
#include "pin.h"
#include "mbed.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define Duty 0.5
#define RotaGain 1.0
#define SlowGain 0.5
#define MAX_xy 512

void Drive(int x_, int y_, bool sw1_, bool sw2_);

#endif
