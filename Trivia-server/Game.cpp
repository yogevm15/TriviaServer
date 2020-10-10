#include "Game.h"

Game::Game(std::vector<Question> questions, std::map<std::string, GameData> players,int id,int questionTime) {
	this->questions = questions;
	this->players = players;
	this->id = id;
	this->questionTime = questionTime;
}
Question* Game::getNextQuestionForUser(std::string username) {
	int currentQuestionIndex = players[username].correctAnswerCount + players[username].wrongAnswerCount;
	if (currentQuestionIndex >= questions.size()) {
		return nullptr;
	}
	
	players[username].begin_time = std::chrono::high_resolution_clock::now();
	players[username].currentQuestion = &questions[currentQuestionIndex];
	return players[username].currentQuestion;
}
int Game::submitAnswer(std::string username,int answerId,StatisticsManager manager) {
	float timeTaken = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - players[username].begin_time).count()/1000;
	players[username].answerTimeSum += timeTaken;
	players[username].answerCount++;
	manager.addAnswerTime(username, timeTaken);
	if (players[username].currentQuestion->submitAnswer(answerId)) {
		players[username].correctAnswerCount++;
		manager.addCorrectAnswer(username);
		return answerId;
	}
	players[username].wrongAnswerCount++;
	manager.addWrongAnswer(username);
	return players[username].currentQuestion->getCorrectIndex();
}
bool Game::removePlayer() {
	playersLeft++;
	return playersLeft >= players.size();
}

std::vector<PlayerResult> Game::getResults() {
	std::vector<PlayerResult> results;

	std::map<std::string, GameData>::iterator it = this->players.begin();

	// Iterate over the map using Iterator till end.
	while (it != this->players.end())
	{
		PlayerResult temp;
		temp.username = it->first;
		temp.averageAnswerTime = it->second.answerTimeSum/it->second.answerCount;
		temp.correctAnswerCount = it->second.correctAnswerCount;
		temp.wrongAnswerCount = it->second.wrongAnswerCount;
		results.push_back(temp);
		// Increment the Iterator to point to next entry
		it++;
	}
	return results;
}

bool Game::isGameFinished() {
	return finished;
}
void Game::finishGame() {
	finished = true;
}
int Game::getId() {
	return id;

}
int Game::getQuestionsAmount() {
	return questions.size();
}

int Game::getQuestionTime() {
	return this->questionTime;
}