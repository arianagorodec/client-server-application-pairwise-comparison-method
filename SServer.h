#pragma once
#include "includes.h"
class SServer
{
public:
	SServer();
	~SServer();
	void startServer();
	void closeServer();
	SOCKET handle();
	unsigned short port;
private:
	SOCKET this_s;
	WSAData wData;
};

