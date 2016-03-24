#include "Quadroped.h"

void Walk(int x_, int y_, bool sw1_, bool sw2_)
{
    static Quadroped Satoko;

    if(x_ == 0 && y_ == 0 && !( sw1_ ^ sw2_ ) ){
        Satoko.SetStd();
        Satoko.SetStand();
    }
    else{
        float angle = atan2((double) y_, (double) x_);
        while(angle < 0)
            angle += 2 * M_PI;

        if (sw1_ && !sw2_)
            Satoko.SetTurn_L();
        else if (!sw1_ && sw2_)
            Satoko.SetTurn_R();
        else{
            if(sw1_ && sw2_)
                Satoko.SetSlow();
            else
                Satoko.SetStd();

            // 45~135[deg]
            if( M_PI / 4.0 <= angle && angle < 3.0 * M_PI / 4.0 )
                Satoko.SetDrive();
            // 135~225[deg]
            else if( 3.0 * M_PI / 4.0 <= angle && angle < 5.0 * M_PI / 4.0)
            	Satoko.SetLeft();
            // 225~315[deg]
            else if( 5.0 * M_PI / 4.0 <= angle && angle < 7.0 * M_PI / 4.0 )
                Satoko.SetBack();
            // 315~45[deg]
            else
            	Satoko.SetRight();
        }
    }
}

Quadroped::Quadroped()
{
    new(leg    ) Leg(0x00, 0x01, servo_tx, servo_rx, 240, 180, 200, 135);
    new(leg + 1) Leg(0x02, 0x03, servo_tx, servo_rx, 240, 180,  70, 135);
    new(leg + 2) Leg(0x04, 0x05, servo_tx, servo_rx,  30,  90,  70, 135);
    new(leg + 3) Leg(0x06, 0x07, servo_tx, servo_rx,  30,  90, 200, 135);
    
    for(int i = 0; i < 4; i++){
        leg[i].SetMiddle();
        leg[i].SetStretch();
        leg[i].attach(Irq_Cycle, Irq_Interval);
        wait(Irq_Interval);
    }
    
    for(int i = 0; i < 7; i++){
    	flg[i] = 0;
    }

    interval = Interval;
    interval_gain = 1;
    call_count = 0;
    SetStand();
    attach();
}

void Quadroped::attach()
{
	detach();
    timer.attach(this, &Quadroped::CallIrq, interval);
}

void Quadroped::detach()
{
    timer.detach();
}

void Quadroped::SetStand()
{
    Irq = &Quadroped::Stand;
}

void Quadroped::SetDrive()
{
    Irq = &Quadroped::Drive;
}

void Quadroped::SetBack()
{
    Irq = &Quadroped::Back;
}

void Quadroped::SetLeft()
{
	Irq = &Quadroped::Left;
}

void Quadroped::SetRight()
{
	Irq = &Quadroped::Right;
}

void Quadroped::SetTurn_R()
{
    SetRota();
    Irq = &Quadroped::Turn_R;
}

void Quadroped::SetTurn_L()
{
    SetRota();
    Irq = &Quadroped::Turn_L;
}
/*
void Quadroped::SetRota()
{
    if(interval != Interval / RotaGain){
        interval = Interval / RotaGain;
        attach();
    }
}

void Quadroped::SetSlow()
{
    if(interval != Interval / SlowGain){
        interval = Interval / SlowGain;
        attach();
    }
}

void Quadroped::SetStd()
{
    if(interval != Interval){
        interval = Interval;
        attach();
    }
}
*/
void Quadroped::SetRota()
{
	if(interval_gain != RotaGain)
		interval_gain = RotaGain;
}

void Quadroped::SetSlow()
{
	if(interval_gain != SlowGain)
		interval_gain = SlowGain;
}

void Quadroped::SetStd()
{
	if(interval_gain != 1)
		interval_gain = 1;
}

void Quadroped::CallIrq()
{
	if( !(++call_count % interval_gain) ){
		(this->*Irq)();
		call_count = 0;
	}
}

void Quadroped::Stand()
{
	for(int i = 0; i < 7; i++)
		flg[i] = 0;
    for(int i = 0; i < 4; i++){
        leg[i].SetMiddle();
        leg[i].SetStretch();
    }
}
        
void Quadroped::Drive()
{
    switch(flg[1]){
    case 0:
    	for(int i = 0; i < 7; i++)
    		flg[i] = 0;

    	leg[RF].StepIn();
    	leg[RB].StepIn();

    	flg[1]++;
    	break;
    case 1:
        leg[LF].SetInside();
        leg[LB].StepIn();
        leg[RF].StepMiddle();
        leg[RB].SetMiddle();
        flg[1]++;
        break;
    case 2:
        leg[LF].StepMiddle();
        leg[LB].SetMiddle();
        leg[RF].SetInside();
        leg[RB].StepIn();
        flg[1]--;
        break;
    }
}

void Quadroped::Back()
{
    switch(flg[2]){
    case 0:
    	for(int i = 0; i < 7; i++)
    		flg[i] = 0;

    	leg[RF].StepIn();
    	leg[RB].StepIn();

    	flg[2]++;
    case 1:
        leg[LF].StepIn();
        leg[LB].SetInside();
        leg[RF].SetMiddle();
        leg[RB].StepMiddle();
        flg[2]++;
        break;
    case 2:
        leg[LF].SetMiddle();
        leg[LB].StepMiddle();
        leg[RF].StepIn();
        leg[RB].SetInside();
        flg[2]--;
        break;
    }
}

void Quadroped::Left()
{
    switch(flg[3]){
    case 0:
    	for(int i = 0; i < 7; i++)
    		flg[i] = 0;

    	leg[LB].StepOut();
    	leg[RB].StepOut();

    	flg[3]++;
    case 1:
        leg[LF].SetOutside();
        leg[LB].StepMiddle();
        leg[RF].StepOut();
        leg[RB].SetMiddle();
        flg[3]++;
        break;
    case 2:
        leg[LF].StepMiddle();
        leg[LB].SetOutside();
        leg[RF].SetMiddle();
        leg[RB].StepOut();
        flg[3]--;
        break;
    }
}

void Quadroped::Right()
{
    switch(flg[4]){
    case 0:
    	for(int i = 0; i < 7; i++)
    		flg[i] = 0;

    	leg[LF].StepOut();
    	leg[RF].StepOut();

    	flg[4]++;
    case 1:
        leg[LF].SetMiddle();
        leg[LB].StepOut();
        leg[RF].StepMiddle();
        leg[RB].SetOutside();
        flg[4]++;
        break;
    case 2:
        leg[LF].StepOut();
        leg[LB].SetMiddle();
        leg[RF].SetOutside();
        leg[RB].StepMiddle();
        flg[4]--;
        break;
    }
}
void Quadroped::Turn_R()
{
    switch(flg[5]){
    case 0:
    	for(int i = 0; i < 7; i++)
    		flg[i] = 0;
        for(int i = 0; i < 4; i++){
            leg[i].SetMiddle();
            leg[i].SetStretch();
        }
    	flg[5]++;
    case 1:
        leg[LF].StepOut();
        leg[LB].SetMiddle();
        leg[RF].SetMiddle();
        leg[RB].StepOut();
        flg[5]++;
        break;
    case 2:
        leg[LF].SetMiddle();
        leg[LB].StepIn();
        leg[RF].StepIn();
        leg[RB].SetMiddle();
        flg[5]--;
        break;
    }
}

void Quadroped::Turn_L()
{
    switch(flg[6]){
    case 0:
    	for(int i = 0; i < 7; i++)
    		flg[i] = 0;
        for(int i = 0; i < 4; i++){
            leg[i].SetMiddle();
            leg[i].SetStretch();
        }
    	flg[6]++;
    case 1:
        leg[LF].StepIn();
        leg[LB].SetMiddle();
        leg[RF].SetMiddle();
        leg[RB].StepIn();
        flg[6]++;
        break;
    case 2:
        leg[LF].SetMiddle();
        leg[LB].StepOut();
        leg[RF].StepOut();
        leg[RB].SetMiddle();
        flg[6]--;
        break;
    }
}
