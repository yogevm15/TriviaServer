#include <WinSock2.h>
#include <Windows.h>
#include "Helper.h"
#include <vector>
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class Communicator {
public:
	
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void serve(int port);
	Helper helper;

private:
	void accept();
	void handleNewClient(SOCKET clientSocket);
	RequestHandlerFactory& handlerFactory;
	std::map<SOCKET, IRequestHandler*> clients;
	SOCKET _serverSocket;
};