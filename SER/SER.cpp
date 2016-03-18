#include"mbed.h"
#include"SER.h"
SER::SER(PinName pwm):Pwm(pwm)
{
    Pwm.period(0.020);
}

void SER::deg(int degree)//ふたばサーボs3003用に原点、幅が調整されていまっせ
{
    double deg = degree;
    if(degree < -90.0) {
        deg = -90.0;
    }
    if(degree > 90.0) {
        deg = 90.0;
    }
          Pwm.pulsewidth((deg + 152)*0.00001);
}