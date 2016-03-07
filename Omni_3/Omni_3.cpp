#include "Omni_3.h"
#include "mbed.h"
#include <math.h>

Omni_3::Omni_3(PinName pin_pwm_F, PinName pin_dere_F,
               PinName pin_pwm_L, PinName pin_dere_L,
               PinName pin_pwm_R, PinName pin_dere_R,
               int arg_rev = 1)
               :md_F(pin_pwm_F, pin_dere_F),
                md_L(pin_pwm_L, pin_dere_L),
                md_R(pin_pwm_R, pin_dere_R)
{
    rev = arg_rev;
}

void Omni_3::Drive(double arg_dere, double arg_speed, double arg_rota)
{
    double duty[3];
    double speed[3];
    
    speed[0] = cos(arg_dere) * arg_speed;   // vx
    speed[1] = sin(arg_dere) * arg_speed;   // vy
    speed[2] = arg_rota;                // omega
    
    Matrix(speed, duty);
    for(int i = 0; i < 3; i ++){
        if(fabs(duty[i]) > 1.0){
            int inv = duty[i];
            for(int j = 0; j < 3; j ++){
                duty[j] *= 1.0 / (double)inv;
            }
        }
    }
    md_F.rotate(duty[0]);
    md_L.rotate(duty[1]);
    md_R.rotate(duty[2]);
}

void Omni_3::Matrix(double speed[3], double duty[3])
{
    double keisu[3][3];
    keisu[0][0] = -1.0;
    keisu[0][1] = 0.0;
    keisu[0][2] = 1.0;
    keisu[1][0] = 1.0 / 2.0;
    keisu[1][1] = -sqrt(3.0) / 2.0;
    keisu[1][2] = 1.0;
    keisu[2][0] = 1.0 / 2.0;
    keisu[2][1] = sqrt(3.0) / 2.0;
    keisu[2][2] = 1.0;
    
    for(int i = 0; i < 3; i ++){
        duty[i] = 0;
        for(int j = 0; j < 3; j ++){
            duty[i] += keisu[i][j] * speed[j] * rev;
        }
    }
}