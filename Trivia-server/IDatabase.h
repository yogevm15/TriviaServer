#pragma once
#include <iostream>
#include <string>
#include "Structs.h"

class IDatabase
{
public:
	virtual int Signup(SignupRequest request) = 0;
	virtual int Login(LoginRequest request) = 0;
	virtual void Logout(LogoutRequest request) = 0;
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void clear() = 0;
	virtual std::vector<Question> getRandomQuestions(int amount) = 0;
	virtual std::vector<PlayerStatistics> getTopPlayersStats(int amount) = 0;
	virtual PlayerStatistics getPlayerStats(std::string username) = 0;
	virtual void addAnswerTime(std::string username,float time) = 0;
	virtual void addCorrectAnswer(std::string username) = 0;
	virtual void addWrongAnswer(std::string username) = 0;
	virtual void addGamePlayed(std::string username) = 0;
};

