#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, std::string username,int roomId) : handlerFactory(handlerFactory) {
	this->username = username;
	this->roomId = roomId;
}
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request) {
	return request.code == EDIT_ROOM_REQUEST || request.code == CLOSE_ROOM_REQUEST || request.code == START_GAME_REQUEST || request.code == GET_ROOM_DETAILS_REQUEST;

}
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request) {
	switch (request.code)
	{
		case CLOSE_ROOM_REQUEST:
			return leaveRoom(request);
		case START_GAME_REQUEST:
			return startGame(request);
		case EDIT_ROOM_REQUEST:
			return editRoom(request);
		case GET_ROOM_DETAILS_REQUEST:
			return getRoomDetails(request);
	}

}
std::string RoomAdminRequestHandler::getUsername() {
	return this->username;
}


RequestResult RoomAdminRequestHandler::leaveRoom(RequestInfo request){
	RequestResult result;
	CloseRoomResponse response;

	this->handlerFactory.getRoomManager().leaveRoomByUsername(this->username);
	response.status = CLOSE_ROOM_SUCCESS;


	result.newHandler = handlerFactory.createMenuRequestHandler(this->username);
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult RoomAdminRequestHandler::startGame(RequestInfo request) {
	RequestResult result;
	StartGameResponse response;
	Room* room = this->handlerFactory.getRoomManager().getRoom(this->roomId);
	if (room == nullptr) {
		response.status = START_GAME_NOT_EXIST;
		result.newHandler = handlerFactory.createMenuRequestHandler(username);
	}
	else {
		
		result.newHandler = handlerFactory.createGameRequestHandler(username, handlerFactory.getGameManager().createGame(*room), roomId);
		room->start();
		response.status = START_GAME_SUCCESS;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult RoomAdminRequestHandler::editRoom(RequestInfo request) {
	RequestResult result;
	EditRoomResponse response;
	EditRoomRequest editRoomRequest = JsonRequestPacketDeserializer::deserializeEditRoomRequest(request.buffer);
	Room *room = this->handlerFactory.getRoomManager().getRoom(this->roomId);
	if (room == nullptr) {
		response.status = EDIT_ROOM_NOT_EXIST;
	}
	else {
		room->setRoomData(editRoomRequest);
		response.status = EDIT_ROOM_SUCCESS;
	}
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomDetails(RequestInfo request) {
	RequestResult result;
	GetRoomDetailsResponse response;
	GetRoomDetailsRequest playersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
	Room* room = this->handlerFactory.getRoomManager().getRoom(this->roomId);
	if (room == nullptr) {
		response.status = GET_ROOM_DETAILS_NOT_EXIST;
		RoomData tempRoomData;
		tempRoomData.admin = "";
		tempRoomData.id = 0;
		tempRoomData.isActive = 0;
		tempRoomData.maxPlayers = 0;
		tempRoomData.name = "";
		tempRoomData.questionCount = 0;
		tempRoomData.timePerQuestion = 0;
		response.roomData = tempRoomData;
		result.newHandler = handlerFactory.createMenuRequestHandler(this->username);
	}
	else {
		response.roomData = room->getRoomData();
		response.status = GET_ROOM_DETAILS_SUCCESS;
		result.newHandler = nullptr;
	}
	
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}