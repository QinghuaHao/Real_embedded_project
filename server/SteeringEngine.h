#ifndef STEERING_ENGINE_H_
#define STEERING_ENGINE_H_
#include "pigpio.h"

class CSteeringEngine
{
private:
    int m_Frequency;
    int m_Range;  
    int m_PinNumber;  
    int m_InitStatus;  
public:
	CSteeringEngine(unsigned int pinNumber, unsigned int dutycycle);
	~CSteeringEngine();
public:
    int setStatus(unsigned int value);
    int init();
    int setPWMrange(unsigned int value);
    int setPWMfrequency(unsigned int value);

};

#endif
