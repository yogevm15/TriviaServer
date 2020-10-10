#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

class WSAInitializer
{
public:
	WSAInitializer();
	~WSAInitializer();
};

