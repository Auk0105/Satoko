#include"mbed.h"
#include"MD.h"
MD::MD(PinName pwm,PinName dere):Pwm(pwm),Dere(dere)
{
    Pwm.period(0.0001);
}

void MD::rotate(double duty)
{
    if(duty > 0)
    {
        Dere = 0;
        Pwm = duty;
    }
    else
    {
        Dere = 1;
        Pwm = -duty;
    }
}