#include <stdio.h>
#include "SteeringEngine.h"


CSteeringEngine::CSteeringEngine(unsigned int pinNumber, unsigned int dutycycle)
{

    m_PinNumber = pinNumber;
    gpioPWM(m_PinNumber, pinNumber);

}
CSteeringEngine::~CSteeringEngine()
{


    
}
int CSteeringEngine::setPWMrange(unsigned int value)
{
    return gpioSetPWMrange(m_PinNumber, value);
}

int CSteeringEngine::setPWMfrequency(unsigned int value)
{
    return gpioSetPWMfrequency(m_PinNumber, value);
}
