#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"
class RequestHandlerFactory;
class LoginRequestHandler :public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory &handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
	std::string getUsername();

private:
	std::string username;
	RequestHandlerFactory& handlerFactory;
	RequestResult login(RequestInfo request);
	RequestResult signup(RequestInfo request);
};

