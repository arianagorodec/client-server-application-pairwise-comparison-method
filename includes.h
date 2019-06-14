#pragma once

#define _CRT_SECURE_NO_WARNINGS 

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <iostream>
#include <WinSock2.h>
#include <winsock.h>
#include "SClient.h"

using namespace std;

template <class T>
bool Ñompare_Name(T l_s, T r_s);


template <class T>
bool Ñompare_Name(T l_s, T r_s) {
	if (strcmp(l_s.Get_lastname(), r_s.Get_lastname()) == 0) {
		if (strcmp(l_s.Get_firstname(), r_s.Get_firstname()) == 0) {
			if (strcmp(l_s.Get_otchestvo(), r_s.Get_otchestvo()) < 0) {
				return 1;
			}
			else
				return 0;
		}
		else {
			if (strcmp(l_s.Get_firstname(), r_s.Get_firstname()) < 0) {
				return 1;
			}
			else
				return 0;
		}
	}
	else {
		if (strcmp(l_s.Get_lastname(), r_s.Get_lastname()) < 0) {
			return 1;
		}
		else
			return 0;
	}
}