#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "Structs.h"
#include <algorithm>
#include <random>
class SqliteDatabase :
	public IDatabase
{
public:
	std::vector<PlayerStatistics> getTopPlayersStats(int amount);
	PlayerStatistics getPlayerStats(std::string username);
	void addAnswerTime(std::string username, float time);
	void addCorrectAnswer(std::string username);
	void addWrongAnswer(std::string username);
	void addGamePlayed(std::string username);
	std::vector<Question> getRandomQuestions(int amount);
	int Signup(SignupRequest request);
	int Login(LoginRequest request);
	void Logout(LogoutRequest request);
	float getPlayerSumAnswerTime(std::string username);
	int getPlayerTotalAnswers(std::string username);
	int getNumOfCorrectAnswer(std::string username);
	int getNumOfWrongAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);
	void addAnswer(std::string username);
	bool open();
	void close();
	void clear();
private:
	bool isEmailExist(std::string email);
	bool isUsernameExist(std::string username);
	sqlite3* db;
};

