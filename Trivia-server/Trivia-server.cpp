#pragma comment (lib, "ws2_32.lib")
#pragma once
#include "WSAInitializer.h"
#include "Server.h"

#include <exception>

int main()
{
	try{
		WSAInitializer wsaInit;
		Server myServer;
		myServer.run();
	}
	catch (std::exception & e){
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}