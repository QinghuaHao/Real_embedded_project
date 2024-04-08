#include <stdio.h>
//#include <wiringPi.h>
//#include <softPwm.h>  
#include "pigpio.h"
#include <unistd.h>
#define INPUT_MODE
#define GPIO_PIN 21



#ifdef OUTPUT_MODE 
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
	gpioTerminate();
}
#endif
#ifdef INPUT_MODE 
void callBack(int pin, int level, unsigned int tick)
{
	printf("pin:%d level:%d\n", pin, level);

}
int main( void)
{
    	int ret = 0;
	if (gpioInitialise() < 0)
	{
   		printf("pigpio initialisation failed.\n");
	}
	else
	{
   		printf("pigpio initialisation ok.\n");
	}
	gpioSetMode(GPIO_PIN, PI_INPUT);
    	gpioSetPullUpDown(GPIO_PIN, PI_PUD_DOWN);
	gpioSetAlertFunc(GPIO_PIN, callBack);
	for(int i = 0; i < 20; i++)
	{
		sleep(1);
		ret = gpioRead(GPIO_PIN);
		printf("read data : %d\n", ret);
	}
	gpioTerminate();
}
#endif
