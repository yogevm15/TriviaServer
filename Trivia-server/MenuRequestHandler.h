#pragma once
#include "IRequestHandler.h"
#include "Structs.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"
class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory,std::string username);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
	std::string getUsername();

private:
	std::string username;
	RequestHandlerFactory& handlerFactory;
	RequestResult signout(RequestInfo request);
	RequestResult getRoomsId(RequestInfo request);
	RequestResult getRoomDetails(RequestInfo request);
	RequestResult getStatistics(RequestInfo request);
	RequestResult getTopStatistics(RequestInfo request);
	RequestResult joinRoom(RequestInfo request);
	RequestResult createRoom(RequestInfo request);
};

