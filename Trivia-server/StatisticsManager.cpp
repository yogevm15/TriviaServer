#include "StatisticsManager.h"
StatisticsManager::StatisticsManager(IDatabase* database):database(database) {

}
PlayerStatistics StatisticsManager::getPlayerStatistics(std::string username) {
	return database->getPlayerStats(username);
}

std::vector<PlayerStatistics> StatisticsManager::getBestPlayers(int amount) {
	return database->getTopPlayersStats(amount);
}

void StatisticsManager::addAnswerTime(std::string username, float time) {
	database->addAnswerTime(username, time);
}
void StatisticsManager::addCorrectAnswer(std::string username) {
	database->addCorrectAnswer(username);
}
void StatisticsManager::addWrongAnswer(std::string username) {
	database->addWrongAnswer(username);
}
void StatisticsManager::addGamePlayed(std::string username) {
	database->addGamePlayed(username);
}
