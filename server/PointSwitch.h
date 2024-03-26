#ifndef POINT_SWITCH_H_
#define POINT_SWITCH_H_
#include "pigpio.h"

typedef void (*gpioCallBack) (int level);
class CPointSwitch
{
private:
    int m_PinNumber;
    int m_PinMode;  
    int m_PullAndDown;  
    void* callback(unsigned int level);
    void gpioAlertFunc(int gpio, int level, unsigned int tick);
public:
	CPointSwitch(unsigned int pinNumber, unsigned int pinMode, unsigned int pullAndDown, gpioCallBack fun);
	~CPointSwitch();
public:
    int getValue(unsigned int &value);
    int setValue(unsigned int value);

};



#endif
