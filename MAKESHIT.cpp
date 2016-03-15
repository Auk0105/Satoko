#include "MAKESHIT.h"
#include "mbed.h"
#include "MD.h"
#include "SER.h"

MAKESHIT::MAKESHIT( PinName ping,PinName elpwm,PinName eldir,PinName hand,PinName belt,
                    PinName sw1,PinName sw2,PinName sw3,PinName cha)
                    : _ping(ping),_el(elpwm,eldir),_hand(hand),_belt(belt),_sw1(sw1),_sw2(sw2),_sw3(sw3),_charge(cha),_CHA(cha)
{
    _ance = 0;
    hirai = 0x8000;

    _sw1.rise(this,&MAKESHIT::top);
    _sw2.rise(this,&MAKESHIT::middle);
    _sw3.rise(this,&MAKESHIT::bottom);
    _charge.rise(this,&MAKESHIT::grasp);
    _hand.deg(0);

}

void MAKESHIT::boom(void)
{
    if((hirai>>15) & 1) { //sone1
        _ping.output();
        _ping = 1;
        wait_us(5);
        _ping = 0;
        _ping.input();
        while(!_ping);
        _dist.start();
        while(_ping);
        _dist.stop();
        _ance = (_dist.read()/2)*(331.5+(temp*0.6));
        _dist.reset();

        if((_ance < 0.15) && (!((hirai>>9) & 1))) {//exam0
            _cabal.start();
            hirai |= 0x0200;//exam1
        }

        if((_ance > 0.15)&&((hirai>>9) & 1)) {//exam1
            _cabal.stop();
            _cabal.reset();
            hirai &= 0xFDFF;//exam0
        }

        if((hirai>>9) & 1) {//exam
            if(_cabal.read() > hold) {
                //hirai |= 0x0400;//cath1
                hirai &= 0x7FFF;//sone0
                hirai &= 0xFDFF;//exam0
                _cabal.stop();
                _cabal.reset();
                hirai |= 0x4000;//stam1

                _el.rotate(0.5);
            }

        }
    }
}
void MAKESHIT::top(void)
{
    if((hirai>>13) & 1) {//midm1
        hirai &=0xDFFF;//midm0
        _el.rotate(0);
        //hirai &= 0xFBFF;//cath0
        hirai |= 0x8000;//sone1
    }
}

void MAKESHIT::middle(void)
{
    if((hirai>>12) & 1) {//botm1
        hirai &=0xEFFF;//botm0
        _el.rotate(0);
        _belt = 1;
        _beltstop.attach(this,&MAKESHIT::belser,DT);

    }
}


void MAKESHIT::bottom()
{
    if((hirai>>14) & 1) {//stam1
        hirai &=0xBFFF;//stam0
        wait_ms(10);
        _el.rotate(-0.9);
        hirai |= 0x1000;//botm1
    }
}

void MAKESHIT::belser()
{
    _belt = 0;
    //if(!((hirai>>7)&1)) {
        _hand.deg(open);
        //hirai |=0x0080;
    //}
    _el.rotate(-0.9);
    hirai |=0x2000;//midm1
}

void MAKESHIT::grasp()
{
    wait_ms(50);
    if(_CHA) {
        hirai = hirai^0x0040;
        if(((hirai>>6)&1)) {
            _hand.deg(open);
        } else if(!((hirai>>6)&1)) {
            _hand.deg(close);
        }
    }
}
