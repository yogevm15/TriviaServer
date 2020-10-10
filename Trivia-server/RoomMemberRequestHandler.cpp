#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, std::string username, int roomId) : handlerFactory(handlerFactory) {
	this->username = username;
	this->roomId = roomId;
}
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo request) {
	return request.code == LEAVE_ROOM_REQUEST || request.code == GET_ROOM_DETAILS_REQUEST || request.code == NEW_ADMIN_REQUEST;

}
RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo request) {
	switch (request.code)
	{
		case LEAVE_ROOM_REQUEST:
			return leaveRoom(request);
		case GET_ROOM_DETAILS_REQUEST:
			return getRoomDetails(request);
		case NEW_ADMIN_REQUEST:
			return newAdmin(request);
	}

}
std::string RoomMemberRequestHandler::getUsername() {
	return this->username;
}


RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo request) {
	RequestResult result;
	LeaveRoomResponse response;
	this->handlerFactory.getRoomManager().leaveRoomByUsername(this->username);


	response.status = LEAVE_ROOM_SUCCESS;


	result.newHandler = handlerFactory.createMenuRequestHandler(this->username);
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}


RequestResult RoomMemberRequestHandler::getRoomDetails(RequestInfo request) {
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
		if (response.roomData.isActive == true) {
			result.newHandler = handlerFactory.createGameRequestHandler(this->username, handlerFactory.getGameManager().getGame(roomId),roomId);
		}
		else {
			result.newHandler = nullptr;
		}
	}
	
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult RoomMemberRequestHandler::newAdmin(RequestInfo request) {
	RequestResult result;
	NewAdminResponse response;
	
	Room* room = this->handlerFactory.getRoomManager().getRoom(this->roomId);
	if (room->getRoomData().admin == username) {
		response.status = NEW_ADMIN_SUCCESS;
		result.newHandler = handlerFactory.createRoomAdminRequestHandler(username, roomId);
	}
	else {
		response.status = NEW_ADMIN_NOT_REAL_ADMIN;
		result.newHandler = nullptr;
	}
	
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}