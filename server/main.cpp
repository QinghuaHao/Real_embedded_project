#include <stdio.h>
#include "pigpio.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
//#include "PointSwitch.h"
//#include "SteeringEngine.h"

#define SERVER_PORT		10000
#define SERVER_IP		"192.168.137.4"



int listen_fd = -1;
void signal_handler(int arg)
{

	printf("close listen_fd(signal = %d)\n", arg);
	close(listen_fd);
	exit(0);
}
 


void CallBack(int level)
{
    if(level == PI_PUD_UP)
    {

    }
}
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
/*
	CPointSwitch pointSwitch1(8, PI_INPUT, PI_PUD_UP, &CallBack);
	CPointSwitch pointSwitch2(9, PI_INPUT, PI_PUD_UP, &CallBack);
	CSteeringEngine steeringEngine1(10, 250);
	CSteeringEngine steeringEngine2(10, 250);
*/

   	int ret = 0;
	int new_fd  = -1;
	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t saddrlen = sizeof(server);
	socklen_t caddrlen = sizeof(client);
	signal(SIGINT, signal_handler);
 
	memset(&server, 0, sizeof(server));
	memset(&client, 0, sizeof(client));
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
	{
		printf("socket error!\n");
		return -1;
	}
 	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	if (bind(listen_fd, (struct sockaddr *)&server, saddrlen) < 0)
	{
		printf("bind error!\n");
		return -1;
	}
 	if (listen(listen_fd, 5) < 0)
	{
		printf("listen error!\n");
		return -1;
	}
 	unsigned int rbuf[256] = {0};
	int size = 0;
	while (1)
	{
		new_fd = accept(listen_fd, (struct sockaddr *)&client, &caddrlen);
		if (new_fd < 0)
		{
			perror("accept");
			return -1;
		}
 		printf("new client connected.IP:%s,port:%u\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		while (1)
		{
			size = read(new_fd, (char*)rbuf, sizeof(rbuf));
			if (size < 0)
			{
				printf("read error!\n");
				continue;
			}
			else if (size == 0)
			{
				printf("client (%d) is closed!\n", new_fd);
				close(new_fd);
				break;
			}
			if(rbuf[0] == 1) //receive tcp and opend door
			{
				ret = 0;
				printf("open the door \n");
            		}
			else if(rbuf[0] == 0)//receive tcp and close door
			{
				printf("close the door \n");
				ret = 0;
			}
			else
			{
				ret = 1;
				printf("data error %x\n", rbuf[0]);
			}
			size = write(new_fd, &ret, 4);
			if (size < 0)
			{
				printf("write error!\n");
				continue;
			}
        }
    }

	gpioTerminate();

}
