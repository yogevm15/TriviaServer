#pragma once
#include "IRequestHandler.h"
#include "Structs.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, std::string username, int roomId);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
	std::string getUsername();

private:
	std::string username;
	int roomId;
	RequestHandlerFactory& handlerFactory;
	RequestResult leaveRoom(RequestInfo request);
	RequestResult getRoomDetails(RequestInfo request);
	RequestResult newAdmin(RequestInfo request);
};

