#pragma once
#include "Structs.h"
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(IDatabase* database);
	Game* createGame(Room room);
	Game* getGame(int id);
	void deleteGame(int id);
	void leaveGameByUsername(std::string username);
private:
	IDatabase* database;
	std::map<int,Game*> games;
};

