#pragma once
#include <SDL_net.h>
#include <string>
class UDPClient
{
public:
	UDPClient();
	~UDPClient();
	int setupClient();
	bool sendMsg(char* msg);
private:
	bool quit;
	UDPpacket * p;
	UDPsocket sd;
};

