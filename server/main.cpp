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
#include "PointSwitch.h"
#include "SteeringEngine.h"
#include <sys/statfs.h>
#include <string>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "parseXmlApi.h"
#include "pthread.h"
/// get executable path
std::string get_cur_executable_path_()
{
    char *p                 = NULL;

    const int len           = 256;
    /// to keep the absolute path of executable's path
    char arr_tmp[len]       = {0};

    int n                   = readlink("/proc/self/exe", arr_tmp, len);
    if (NULL != (p = strrchr(arr_tmp,'/')))
        *p = '\0';
    else
    {
        return std::string("");
    }

    return std::string(arr_tmp);
}
#define BUFFER_SIZE 256
typedef struct msgBuffer
{
	unsigned int writePos;
	unsigned int readPos;
	std::string msg[BUFFER_SIZE];

}TY_MSG_BUFFER;
unsigned int runFlag = 0;
TY_MSG_BUFFER msgBuffer;
int listen_fd = -1;
void signal_handler(int arg)
{
	runFlag = 0;
	printf("close listen_fd(signal = %d)\n", arg);
	close(listen_fd);
	exit(0);
}
 




CSteeringEngine steeringEngine1(26, 40);//left
CSteeringEngine steeringEngine2(19, 150);//right




int getBufferLen()
{
	if(msgBuffer.writePos >= msgBuffer.readPos)
		return msgBuffer.writePos - msgBuffer.readPos;
	else
		return msgBuffer.writePos + BUFFER_SIZE - msgBuffer.readPos;
	return 0;
}

int readBuffer(std::string &msg)
{
	msg = msgBuffer.msg[msgBuffer.writePos];
	msgBuffer.readPos = (msgBuffer.readPos+1) % BUFFER_SIZE;
	return 0;
}
int writeBuffer(std::string msg)
{

	msgBuffer.msg[msgBuffer.writePos] = msg;
	msgBuffer.writePos = (msgBuffer.writePos+1) % BUFFER_SIZE;
	return 0;
}
void callBackFun(int pin, int level, unsigned int tick)
{
	std::string tmpStr;
	if(level == 1)
    	{
		tmpStr = "switch:open the door \n";
		printf("%s \n", tmpStr.c_str());
		writeBuffer(tmpStr);
		steeringEngine1.setStatus(40);
		steeringEngine2.setStatus(150);

   	}
   	else
   	{
    
	}
	//printf("pin:%d level:%d\n", pin, level);
}
void *msgSend(void *args)
{
	int new_fd;
	int size = 0;
	int bufferLen = 0;
	while(runFlag)
	{
		new_fd = *(int *)(args);
		bufferLen = getBufferLen();
		while(bufferLen--)
		{

			size = write(new_fd, msgBuffer.msg[msgBuffer.readPos].c_str(), msgBuffer.msg[msgBuffer.readPos].length());
			if (size < 0)
			{
//				printf("write error!\n");
				break;
			}
			printf("msgSend:%s\n", msgBuffer.msg[msgBuffer.readPos].c_str());
			msgBuffer.readPos = (msgBuffer.readPos+1) % BUFFER_SIZE;

		}
		usleep(1000);
	}


	return NULL;
}
int main( void)
{
	pthread_t pthreadFd;
	if (gpioInitialise() < 0)
	{
   		printf("pigpio initialisation failed.\n");
	}
	else
	{
   		printf("pigpio initialisation ok.\n");
	}
	std::string tmpStr;
	std::string ip;
 	std::string port;
	std::string execStr = get_cur_executable_path_();
	execStr = execStr + "/config.xml";
	std::cout << "str=" << execStr << "\n\n";
	TiXmlDocument * doc = NULL;	
	doc = load_xml(execStr.c_str(), FROM_FILE);
	TiXmlElement *pRoot = doc->RootElement();
	TiXmlElement *pConfig = pRoot->FirstChildElement("TCPCONFIG");
	TiXmlAttribute* pAttribute = pConfig->FirstAttribute();
	for(; pAttribute != NULL; pAttribute = pAttribute->Next())
	{
		tmpStr = pAttribute->Name();	
		printf("\nname:%s\n", tmpStr.c_str());
		if(tmpStr == "Ip")
		{
      			ip=pAttribute->Value();
			printf("IP:%s \n", pAttribute->Value());
		}
		else if(tmpStr == "Port")
		{
      			port=pAttribute->Value();
			printf("Port:%s \n", pAttribute->Value());
		}
	}

	CPointSwitch pointSwitch1(15, PI_INPUT, PI_PUD_DOWN, callBackFun);
	CPointSwitch pointSwitch2(16, PI_INPUT, PI_PUD_DOWN, callBackFun);
	CPointSwitch pointSwitch3(21, PI_INPUT, PI_PUD_DOWN, callBackFun);
	CPointSwitch pointSwitch4(20, PI_INPUT, PI_PUD_DOWN, callBackFun);

	steeringEngine1.init();
	steeringEngine2.init();
	
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
	pthread_create(&pthreadFd, NULL, msgSend, &new_fd);
 	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(port.c_str()));
	server.sin_addr.s_addr = inet_addr(ip.c_str());
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
 	unsigned char rbuf[256] = {0};
	int size = 0;
	runFlag = 1;
	while (runFlag)
	{
		new_fd = accept(listen_fd, (struct sockaddr *)&client, &caddrlen);
		if (new_fd < 0)
		{
			perror("accept");
			return -1;
		}
 		printf("new client connected.IP:%s,port:%u\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		while (runFlag)
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
			if(rbuf[0] == '1') //receive tcp and opend door
			{
				tmpStr = "cmd:open the door \n";
				printf("%s \n", tmpStr.c_str());
				writeBuffer(tmpStr);
				steeringEngine1.setStatus(40);
				steeringEngine2.setStatus(150);


            		}
			else if(rbuf[0] == '0')//receive tcp and close door
			{
				tmpStr = "cmd:close the door \n";
				printf("%s \n", tmpStr.c_str());
				writeBuffer(tmpStr);
				
				steeringEngine1.setStatus(106);
				steeringEngine2.setStatus(90);
			}
			else
			{
				tmpStr = "cmd:data error \n";
				printf("%s %d\n", tmpStr.c_str(), rbuf[0]);
				writeBuffer(tmpStr);

			}

			/*
			printf("new_fd:%d \n", new_fd);
			size = write(new_fd, &ret, 4);
			if (size < 0)
			{
				printf("write error!\n");
				continue;
			}
			*/
        }
    }

	gpioTerminate();

}
