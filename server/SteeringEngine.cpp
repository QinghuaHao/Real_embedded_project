#include <stdio.h>
#include "SteeringEngine.h"


CSteeringEngine::CSteeringEngine(unsigned int pinNumber ,unsigned int initStatus)
{

	m_PinNumber = pinNumber;
	m_InitStatus = initStatus;

}
CSteeringEngine::~CSteeringEngine()
{


    
}

int CSteeringEngine::init()
{	

	gpioSetMode(m_PinNumber , PI_OUTPUT);
	gpioSetPWMrange(m_PinNumber , 180);
	gpioSetPWMfrequency(m_PinNumber , 50);
	gpioPWM(m_PinNumber, 5+m_InitStatus*17/180);
}
int CSteeringEngine::setStatus(unsigned int value)
{	
	return gpioPWM(m_PinNumber, 5+value*17/180);
}
int CSteeringEngine::setPWMrange(unsigned int value)
{
    return gpioSetPWMrange(m_PinNumber, value);
}

int CSteeringEngine::setPWMfrequency(unsigned int value)
{
    return gpioSetPWMfrequency(m_PinNumber, value);
}
