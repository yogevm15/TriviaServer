#pragma once
#include "SqliteDatabase.h"
class StatisticsManager{
public:
	StatisticsManager(IDatabase* database);
	PlayerStatistics getPlayerStatistics(std::string username);
	std::vector<PlayerStatistics> getBestPlayers(int amount);
	void addAnswerTime(std::string username, float time);
	void addCorrectAnswer(std::string username);
	void addWrongAnswer(std::string username);
	void addGamePlayed(std::string username);
private:

	IDatabase* database;
};

