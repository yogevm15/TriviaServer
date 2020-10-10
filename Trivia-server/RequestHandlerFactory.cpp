#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	return new LoginRequestHandler(*this);
}
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(std::string username) {
	return new MenuRequestHandler(*this,username);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(std::string username, int roomId) {
	return new RoomAdminRequestHandler(*this, username,roomId);
}
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(std::string username, int roomId) {
	return new RoomMemberRequestHandler(*this, username, roomId);
}
GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(std::string username, Game* game, int roomId) {
	return new GameRequestHandler(*this, username, game, roomId);
}

LoginManager& RequestHandlerFactory::getLoginManager() {
	return this->loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager() {
	return this->roomManager;
}
GameManager& RequestHandlerFactory::getGameManager() {
	return this->gameManager;
}
StatisticsManager& RequestHandlerFactory::getStatisticsManager() {
	return this->statisticsManager;
}
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :loginManager(this->database), database(database), gameManager(this->database), statisticsManager(database) {

}

