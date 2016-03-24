#ifndef _SERIAL_SERVO_H_
#define _SERIAL_SERVO_H_
#include "mbed.h"
// mbed.hをダウングレード
// http://d.hatena.ne.jp/rinie/20121125/1353770901
// https://developer.mbed.org/users/screamer/code/mbed/rev/#node|short#

class Servo{
public:
    Servo(int arg_addr, float arg_angle, PinName tx, PinName rx);
    void SetPos(float arg_angle);
    
    void SetSend(float arg_angle);
    
    void attach(float time);
    void detach();
    
    float Getpos();
    
    void baud(int baudrate);
    void format(int bits, bool parity, int stop_bits);
    
private:
    Serial serial;
    Ticker timer;
    
    void SendPos();

    float send;
    char addr;
    float angle;
    float bef_angle;
};

#endif