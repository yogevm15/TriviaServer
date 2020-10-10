#pragma once
#include "IRequestHandler.h"
#include "Structs.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
#include "Game.h"
class RequestHandlerFactory;
class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, std::string username, Game* game,int roomId);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
	std::string getUsername();

private:
	std::string username;
	Game* game;
	int roomId;
	RequestHandlerFactory& handlerFactory;
	RequestResult leaveGame(RequestInfo request);
	RequestResult getQuestion(RequestInfo request);
	RequestResult submitAnswer(RequestInfo request);
	RequestResult getResults(RequestInfo request);
};

