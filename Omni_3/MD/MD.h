#ifndef _MD_H_
#define _MD_H_
#include "mbed.h"

class MD
{
public:
    MD(PinName pwm,PinName dere);
    void rotate(double duty);
private:
    PwmOut Pwm;
    DigitalOut Dere;
};

#endif