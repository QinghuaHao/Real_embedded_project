#include <stdio.h>
#include "PointSwitch.h"


CPointSwitch::CPointSwitch(unsigned int pinNumber, unsigned int pinMode, unsigned int pullAndDown, gpioAlertFunc_t callBackFun)
{

    m_PinNumber = pinNumber;
    m_PinMode = pinMode;
    m_PullAndDown = pullAndDown; 
    printf("pin:%d mode:%d pullOrDown:%d\n", pinNumber, pinMode, pullAndDown);
    gpioSetMode(m_PinNumber, m_PinMode);
    gpioSetPullUpDown(m_PinNumber, pullAndDown);
    gpioSetAlertFunc(m_PinNumber, callBackFun);

    

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

