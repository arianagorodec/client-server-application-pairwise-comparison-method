#pragma once
#include "SClient.h"
#include "Class.h"


SClient::SClient(SOCKET s, SOCKADDR_IN sock_in)
{

	c_sock = s;
	c_addr = sock_in;
	printf("Client created\n");
	handle();
}


SClient::~SClient()
{
}

void SClient::handle()
{

	while (true)
	{
		USER user;
		for (;;) {
			recv(c_sock, buffer, sizeof(buffer), NULL);
			int k = atoi(buffer);
			switch (k) {
			case 0: Menu_For_Admin(c_sock); break;
			case 1: Menu_For_User(c_sock); break;
			case 2: user.Add_user(c_sock); break;
			case 3: return;
			}
		}
	}
}
