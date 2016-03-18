#ifndef MBED_MAKESHIT
#define MBED_MAKESHIT

#include "mbed.h"
#include "MD.h"
#include "SER.h"

#define temp 18.0
#define hold 2.0
#define DT 3.0
#define open 90
#define close 0

class MAKESHIT{
    public:
    MAKESHIT(PinName ping,PinName elpwm,PinName eldir,PinName hand,PinName belt,PinName sw1,PinName sw2,PinName sw3,PinName cha);
    void boom(void);

    private:
    DigitalInOut _ping;
    MD _el;
    SER _hand;
    DigitalOut _belt;
    InterruptIn _sw1;
    InterruptIn _sw2;
    InterruptIn _sw3;
    InterruptIn _charge;
    DigitalIn _CHA;

    void sonner(void);
    void top(void);
    void middle(void);
    void bottom(void);
    void belser(void);
    void grasp(void);

    Ticker _sn;
    Timer _dist;
    Timer _cabal;
    Timeout _beltstop;
    double _ance;

    unsigned short hirai;

    /*
    What's hirai?
    ~Hirai resister is hirai's resister.
          Use the google honyaku,Please.~

    |bit15|14   |13   |12   |11   |10   |9    |bit8 |
    |sone |stam |midm |botm |open |cath |exam |smfl |

    |bit7 |6    |5    |4    |3    |2    |1    |bit0 |
    |flee |flee |flee |flee |flee |flee |flee |flee |
    */

};

#endif