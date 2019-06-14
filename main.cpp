#pragma once
#include "SServer.h"
#include "class.h"

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	SServer* server = new SServer();
	server->port = 3487;
	server->startServer();

	return 0;
}
