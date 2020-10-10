#pragma once

#include "Structs.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "GameManager.h"
#include "StatisticsManager.h"
class MenuRequestHandler;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(std::string username);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(std::string username,int roomId);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(std::string username, int roomId);
	GameRequestHandler* createGameRequestHandler(std::string username, Game* game, int roomId);
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	GameManager& getGameManager();
	StatisticsManager& getStatisticsManager();
private:
	IDatabase* database;
	LoginManager loginManager;
	RoomManager roomManager;
	GameManager gameManager;
	StatisticsManager statisticsManager;
};

