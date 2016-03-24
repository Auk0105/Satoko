#ifndef _QUADROPED_H_
#define _QUADROPED_H_

#include "mbed.h"
#include "leg.h"

// http://marupeke296.com/TIPS_No13_ClassArrayInitialize.html
// 引数付きコンストラクタを持つメンバクラス配列の初期化
#include <new>

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define servo_tx p13
#define servo_rx p14

#define LF 0
#define LB 1
#define RF 2
#define RB 3

#define Irq_Cycle 0.01
#define Irq_Interval 0.00125    // cycle/8

#define Interval 0.25
#define RotaGain 1
#define SlowGain 3

#define MAX_xy 512

void Walk(int x_, int y_, bool sw1_, bool sw2_);

class Quadroped{
public:
    Quadroped();
    
    void attach();
    void detach();
    
    void SetStand();
    void SetDrive();
    void SetBack();
    void SetLeft();
    void SetRight();
    void SetTurn_R();
    void SetTurn_L();
    
    void SetRota();
    void SetSlow();
    void SetStd();
    
    void (Quadroped::*Irq)();
    
private:
    Leg leg[4];
    Ticker timer;
    
    void CallIrq();

    void Stand();
    void Drive();
    void Back();
    void Left();
    void Right();
    void Turn_R();
    void Turn_L();
    
    float interval;
    int interval_gain;
    int call_count;
    int flg[7];
};

#endif
