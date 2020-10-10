#include "GameManager.h"


GameManager::GameManager(IDatabase* database) {
	this->database = database;
}
Game* GameManager::createGame(Room room) {
	std::vector<Question> questions = database->getRandomQuestions(room.getRoomData().questionCount);
	std::map<std::string, GameData> players;
	for (int i = 0; i < room.getAllUsers().size(); i++) {
		GameData data = GameData();
		data.correctAnswerCount = 0;
		data.wrongAnswerCount = 0;
		data.currentQuestion = &questions[0];
		data.answerTimeSum = 0;
		data.answerCount = 0;
		players[room.getAllUsers()[i]] = data;
	}
	Game* game = new Game(questions,players, room.getRoomData().id,room.getRoomData().timePerQuestion);
	games[room.getRoomData().id] = game;
	return game;
}
Game* GameManager::getGame(int id) {
	return games[id];
}
void GameManager::deleteGame(int id) {
	delete games[id];
	games.erase(id);
}
void GameManager::leaveGameByUsername(std::string username) {
	for (std::map<int, Game*>::iterator it = this->games.begin(); it != this->games.end(); ++it) {
		if (it->second->removePlayer()) {
			deleteGame(it->first);
			return;
		}
	}
}