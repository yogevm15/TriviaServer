#pragma once
#include "Structs.h"
#include "Question.h"
#include <map>
#include <ctime>
#include "StatisticsManager.h"
struct GameData;
struct PlayerResult;
class Question;
class Game
{
public:
	
	Game(std::vector<Question> questions, std::map<std::string, GameData> players,int id,int questionTime);
	Question* getNextQuestionForUser(std::string username);
	int submitAnswer(std::string username, int answerId, StatisticsManager manager);
	bool removePlayer();
	std::vector<PlayerResult> getResults();
	bool isGameFinished();
	void finishGame();
	int getId();
	int getQuestionsAmount();
	int getQuestionTime();
private:
	int id;
	int playersLeft = 0;
	int questionTime;
	bool finished = false;
	std::vector<Question> questions;
	std::map<std::string, GameData> players;
};

struct GameData
{

	std::chrono::time_point<std::chrono::steady_clock> begin_time;
	Question* currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float answerTimeSum;
	unsigned int answerCount;
};

