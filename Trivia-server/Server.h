#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include "Helper.h"
#include <vector>
#include <map>
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
class Server
{
public:
	Server();
	
	void run();
private:
	IDatabase* database;
	RequestHandlerFactory handleFactory;
	Communicator m_comunicator;
};

