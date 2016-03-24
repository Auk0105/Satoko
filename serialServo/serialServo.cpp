#include "serialServo.h"

Servo::Servo(int arg_addr, float arg_angle, PinName tx, PinName rx):serial(tx, rx)
{
    serial.baud(115200);
    serial.format(8, Serial::Even, 1);
    
    addr = arg_addr;
    angle = arg_angle;
    bef_angle = -1;
    if(angle >= 0)
        SetPos(angle);
}

void Servo::SetPos(float arg_angle)
{
    int send_angle;
    if(arg_angle > 270)
        arg_angle = 270;
    if(arg_angle < 0)
        arg_angle = 0;
    angle = arg_angle;
    send_angle = 3500 + int((8000 * angle) / 270);
    serial.putc(0x80 | addr);
    serial.putc( (send_angle >> 7) & 0x7f);
    serial.putc(send_angle & 0x7f);
    wait(0.001);
}

void Servo::SetSend(float arg_angle)
{
    send = arg_angle;
}

void Servo::SendPos()
{
    int send_angle;
    send_angle = 3500 + int((8000 * send) / 270);
    serial.putc(0x80 | addr);
    serial.putc( (send_angle >> 7) & 0x7f);
    serial.putc(send_angle & 0x7f);
}

void Servo::attach(float time)
{
    timer.attach(this, &Servo::SendPos, time);
}

void Servo::detach()
{
    timer.detach();
}

float Servo::Getpos()
{
    return angle;
}