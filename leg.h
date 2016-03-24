#ifndef _LEG_H_
#define _LEG_H_

#include "mbed.h"
#include"serialServo.h"

#define step_time 0.2

class Leg{
public:
    Leg();
    Leg(int knee_addr_, int shoulder_addr_, PinName servo_tx, PinName servo_rx,
        int stretch_, int bend_, int outside_, int inside_);
    void Stretch();
    void Bend();
    void Outside();
    void Middle();
    void Inside();
    void BS_IO(bool bs_, bool io_);
    void Inv_BS();
    void Inv_IO();
    
    void StepOut();
    void StepIn();
    void StepMiddle();
    
    void attach(float time, float interval);
    void detach();
    
    void SetStretch();
    void SetBend();
    void SetOutside();
    void SetMiddle();
    void SetInside();
    void SetKnee(float angle);
    void SetShoulder(float angle);
    
    float ShoulderPos(float angle);
    void ShoulderSetPos(float angle);
    float KneePos(float angle);
    void KneeSetPos(float angle);
private:
    bool bs,io;
    int stretch, bend, outside, middle, inside;
    
    Servo Knee, Shoulder;
    Timeout timer;
};
#endif
