#include "leg.h"

Leg::Leg()  // ダミーのデフォルトコンストラクタ
            :Knee(0, 0, p28, p27)
            ,Shoulder(0, 0, p28, p27)
            
{
}

Leg::Leg(   int knee_addr_, int shoulder_addr_, PinName servo_tx, PinName servo_rx,
            int stretch_, int bend_, int outside_, int inside_)
            :Knee(knee_addr_, -1, servo_tx, servo_rx)
            ,Shoulder(shoulder_addr_, -1, servo_tx, servo_rx)
{
    stretch = stretch_;
    bend = bend_;
    outside = outside_;
    inside = inside_;
    middle = (outside + inside) / 2;
    Stretch();
    Middle();
}

void Leg::Stretch()
{
    Knee.SetPos(stretch);
    bs = 0;
}

void Leg::Bend()
{
    Knee.SetPos(bend);
    bs = 1;
}

void Leg::Outside()
{
    Shoulder.SetPos(outside);
    io = 0;
}

void Leg::Middle()
{
    Shoulder.SetPos(middle);
}

void Leg::Inside()
{
    Shoulder.SetPos(inside);
    io = 1;
}

void Leg::BS_IO(bool bs_, bool io_)
{
    if(bs_)
        Knee.SetPos(bend);
    else
        Knee.SetPos(stretch);
    if(io_)
        Shoulder.SetPos(inside);
    else
        Shoulder.SetPos(outside);
    bs = bs_;
    io = io_;
}

void Leg::Inv_BS()
{
    if(bs)
        Knee.SetPos(stretch);
    else
        Knee.SetPos(bend);
    bs ^= 1;
}

void Leg::Inv_IO()
{
    if(io)
        Shoulder.SetPos(outside);
    else
        Shoulder.SetPos(inside);
    io ^= 1;
}

void Leg::StepOut()
{
    SetBend();
    SetOutside();
    timer.attach(this, &Leg::SetStretch, step_time);
}

void Leg::StepIn()
{
    SetBend();
    SetInside();
    timer.attach(this, &Leg::SetStretch, step_time);
}

void Leg::StepMiddle()
{
	SetBend();
	SetMiddle();
	timer.attach(this, &Leg::SetStretch, step_time);
}

void Leg::attach(float time, float interval)
{
    Knee.attach(time);
    wait(interval);
    Shoulder.attach(time);
}

void Leg::SetStretch()
{
    Knee.SetSend(stretch);
}

void Leg::SetBend()
{
    Knee.SetSend(bend);
}

void Leg::SetOutside()
{
    Shoulder.SetSend(outside);
}

void Leg::SetMiddle()
{
    Shoulder.SetSend(middle);
}

void Leg::SetInside()
{
    Shoulder.SetSend(inside);
}

void Leg::SetKnee(float angle)
{
    Knee.SetSend(angle);
}

void Leg::SetShoulder(float angle)
{
    Shoulder.SetSend(angle);
}

void Leg::KneeSetPos(float angle)
{
    Knee.SetPos(angle);
}

void Leg::ShoulderSetPos(float angle)
{
    Shoulder.SetPos(angle);
}
