#ifndef _OMNI_3_H_
#define _OMNI_3_H_
#include "mbed.h"
#include "MD.h"

class Omni_3{
public:
    Omni_3(PinName pin_pwm_F, PinName pin_dere_F,
           PinName pin_pwm_L, PinName pin_dere_L,
           PinName pin_pwm_R, PinName pin_dere_R,
           int rev);
    void Drive(double arg_dere, double arg_speed, double arg_rota);
private:
    void Matrix(double speed[3], double duty[3]);
    int rev;
    MD md_F;
    MD md_L;
    MD md_R;
};
#endif