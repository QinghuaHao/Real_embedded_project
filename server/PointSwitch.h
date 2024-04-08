#ifndef POINT_SWITCH_H_
#define POINT_SWITCH_H_
#include "pigpio.h"


class CPointSwitch
{
private:
    int m_PinNumber;
    int m_PinMode;  
    int m_PullAndDown;  
    void* callback(unsigned int level);

public:
	CPointSwitch(unsigned int pinNumber, unsigned int pinMode, unsigned int pullAndDown,  gpioAlertFunc_t callBackFun);
	~CPointSwitch();
public:
    int getValue(unsigned int &value);
    int setValue(unsigned int value);

};



#endif
