#include <stdio.h>
//#include <wiringPi.h>
//#include <softPwm.h>  
#include "pigpio.h"
#include <unistd.h>

#define PWM_MODE_2500US
#define GPIO_PIN 21



#ifdef PWM_MODE_2500US
int main( void)
{
    
	if (gpioInitialise() < 0)
	{
   		printf("pigpio initialisation failed.\n");
	}
	else
	{
   		printf("pigpio initialisation ok.\n");
	}
	gpioSetMode(GPIO_PIN, PI_OUTPUT);
	gpioWrite(GPIO_PIN, 1);
	gpioSetPWMrange(GPIO_PIN, 180);
	gpioSetPWMfrequency(GPIO_PIN, 50);
	for(int i = 0; i < 10; i++)
	{
	
		gpioPWM(GPIO_PIN, 22);
		sleep(4);
		gpioPWM(GPIO_PIN, 5);
		sleep(4);
	}
    //gpioSetPullUpDown(2, pullAndDown);

	gpioTerminate();
}
#endif

#ifdef PWM_MODE_500US
int main( void)
{
    
	if (gpioInitialise() < 0)
	{
   		printf("pigpio initialisation failed.\n");
	}
	else
	{
   		printf("pigpio initialisation ok.\n");
	}
	gpioSetMode(GPIO_PIN, PI_OUTPUT);
	gpioWrite(GPIO_PIN, 1);
	gpioSetPWMrange(GPIO_PIN, 180);
	gpioSetPWMfrequency(GPIO_PIN, 50);
	gpioPWM(GPIO_PIN, 5);

    //gpioSetPullUpDown(2, pullAndDown);
	sleep(10);
	gpioTerminate();
}
#endif

