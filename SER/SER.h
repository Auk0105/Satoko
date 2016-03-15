#ifndef _SER_H_
#define _SER_H_

class SER
{
public:
    SER(PinName pwm);
    void  deg(int degree);
private:
    PwmOut Pwm;
};

#endif