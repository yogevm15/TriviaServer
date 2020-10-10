#include "Question.h"

Question::Question(std::string question, std::vector<std::string> answers, int correctIndex,int id) {
	this->id = id;
	this->question = question;
	this->answers = answers;
	this->correctIndex = correctIndex;
}
std::string Question::getQuestion() {
	return this->question;
}
std::vector<std::string> Question::getAnswers() {
	return this->answers;
}
int Question::getCorrectIndex() {
	return this->correctIndex;
}

bool Question::submitAnswer(int answerId) {
	return answerId == correctIndex;
}

int Question::getQuestionId() {
	return this->id;
}