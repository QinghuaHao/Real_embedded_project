#include <stdio.h>
#include "PointSwitch.h"


CPointSwitch::CPointSwitch(unsigned int pinNumber, unsigned int pinMode, unsigned int pullAndDown, gpioCallBack fun)
{

    m_PinNumber = pinNumber;
    m_PinMode = pinMode;
    m_PullAndDown = pullAndDown; 
    gpioSetMode(m_PinNumber, m_PinMode);
    gpioSetPullUpDown(m_PinNumber, pullAndDown);
    gpioSetAlertFunc(m_PinNumber, &gpioAlertFunc);
    callback = fun;
    

}

CPointSwitch::~CPointSwitch()
{



    
}
int CPointSwitch::setValue(unsigned int value)
{
    return gpioWrite(m_PinNumber, value);
}

int CPointSwitch::getValue(unsigned int &value)
{
    value = gpioRead(value);
    return 0;
}
void CPointSwitch::gpioAlertFunc(int gpio, int level, unsigned int tick)
{
    if(callback != NULL)
    {
        callback(level);
    }
}