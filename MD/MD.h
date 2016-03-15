#ifndef _MD_H_
#define _MD_H_

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
