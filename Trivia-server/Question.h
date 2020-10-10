#pragma once
#include "Structs.h"


class Question
{
public:
	Question(std::string question, std::vector<std::string> answers, int correctIndex,int id);
	std::string getQuestion();
	std::vector<std::string> getAnswers();
	int getCorrectIndex();
	bool submitAnswer(int index);
	int getQuestionId();
private:
	std::string question;
	std::vector<std::string> answers;
	int correctIndex;
	int id;
};

