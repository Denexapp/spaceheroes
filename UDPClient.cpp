#include "stdafx.h"
#include "UDPClient.h"
#include <SDL_net.h>
#include <iostream>
#include <string>

UDPClient::UDPClient()
{
	if (SDLNet_Init() == -1)
	{
		std::cout << "Unable to init SDLNet" << std::endl;
	}
	else
	{
		std::cout << "SDLNet init succeed" << std::endl;
	}
		
}

int UDPClient::setupClient()
{
	
	std::cout << "Setting up client" << std::endl;
	//create the socket
	if (!(sd = SDLNet_UDP_Open(0))) {
		printf("Could not create socket\n");
		SDLNet_Quit();
		SDL_Quit();
		exit(1);
	}

	//get my address
	IPaddress* myaddress = SDLNet_UDP_GetPeerAddress(sd, -1);
	if (!myaddress) {
		printf("Could not get own port\n");
		exit(2);
	}

	std::cout << "My Port: " << myaddress->port << std::endl;


	/******************************
	* These are used to recieve
	*******************************/

	UDPpacket * rcvP = SDLNet_AllocPacket(1024);
	if (!rcvP) {
		printf("Could not allocate receiving packet\n");
		exit(3);
	}

	UDPsocket rcvS;
	rcvS = SDLNet_UDP_Open(myaddress->port);
	if (!rcvS)
	{
		printf("Could not allocate receiving socket\n");
		exit(4);
	}

	//resolve the address of the server
	IPaddress srvHost;
	IPaddress * ip = &srvHost;
	SDLNet_ResolveHost(ip, "localhost", 8888);

	//set up the packet
	p = SDLNet_AllocPacket(1024);
	if (!p) {
		printf("Could not allocate packet\n");
		SDLNet_Quit();
		SDL_Quit();
		exit(2);
	}

	//link the server address to our packet
	p->address.host = srvHost.host;
	p->address.port = srvHost.port;


	
}

bool UDPClient::sendMsg(char* msg)
{
	static const char* data = msg;
	p->len = strlen(data) + 1;
	memcpy(p->data, data, p->len);
	SDLNet_UDP_Send(sd, -1, p);
	return 1;
}

UDPClient::~UDPClient()
{
}

