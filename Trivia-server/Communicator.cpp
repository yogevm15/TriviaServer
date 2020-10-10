#pragma once

#include "Communicator.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <time.h>
#include <ctime>
#include "LoginRequestHandler.h"
#include "SignoutException.h"
#include "OTPCryptoAlgorithm.h"

std::mutex Mutex;



Communicator::Communicator(RequestHandlerFactory &handlerFactory): handlerFactory(handlerFactory)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try {
		closesocket(_serverSocket);
	}
	catch (std::exception e) {
		std::cout << "exeption thrown in " << __FUNCTION__ << " with " << e.what() << std::endl;
	}
}

void Communicator::serve(int port)
{
    std::cout << "listning to port " << port << std::endl;
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"
	if (bind(_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	while (true)
	{
		accept();
	}

}


void Communicator::accept()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	std::thread thread(&Communicator::handleNewClient, this, client_socket);
	thread.detach();
}


void Communicator::handleNewClient(SOCKET clientSocket)
{
	std::cout << "client connected"<<std::endl;
	IRequestHandler* requestHandler = nullptr;
	ICryptoAlgorithm* cryptoAlgorithm = &OTPCryptoAlgorithm();
	JsonResponsePacketSerializer::setCryptoAlgorithm(cryptoAlgorithm);
	JsonRequestPacketDeserializer::setCryptoAlgorithm(cryptoAlgorithm);
	try {
		RequestInfo requestInfo;
		requestInfo.code = helper.getBinaryIntPartFromSocket(clientSocket, 4);
		
		requestInfo.buffer = helper.getJsonBuffer(clientSocket);
		time_t my_time = time(NULL);
		requestInfo.receivalTime = ctime(&my_time);
		RequestResult result;
		requestHandler = this->handlerFactory.createLoginRequestHandler();
		while (true) {
			if (requestHandler->isRequestRelevant(requestInfo)) {
				result = requestHandler->handleRequest(requestInfo);
				helper.sendBuffer(clientSocket, result.response);
			}
			requestInfo.code = helper.getBinaryIntPartFromSocket(clientSocket, 4);
			time_t my_time = time(NULL);
			requestInfo.receivalTime = ctime(&my_time);
			requestInfo.buffer = helper.getJsonBuffer(clientSocket);;
			if (result.newHandler != nullptr) {
				delete requestHandler;
				requestHandler = result.newHandler;
			}
		}
	}
	catch (std::exception & e2) {
		if (requestHandler != nullptr) {
			LogoutRequest logout;
			logout.username = requestHandler->getUsername();
			handlerFactory.getRoomManager().leaveRoomByUsername(requestHandler->getUsername());
			handlerFactory.getGameManager().leaveGameByUsername(requestHandler->getUsername());
			handlerFactory.getLoginManager().Logout(logout);
		}
		std::string temp = e2.what();
		if (temp.find("socket") != std::string::npos) {
			std::cout << "Client disconnected, socket id: " << clientSocket << std::endl;
		}
		else {
			try {
				errorResponse err;
				err.message = e2.what();
				BUFFER buffer = JsonResponsePacketSerializer::serializeResponse(err);
				helper.sendBuffer(clientSocket, buffer);
				std::cout << "Unknown Exception for client with socket id: " << clientSocket << " Exception: " << e2.what() << std::endl;
			}
			catch (std::exception & e3) {
				std::cout << "Client disconnected, socket id: " << clientSocket << std::endl;
			}
			
		}
		closesocket(clientSocket);
	}
}

