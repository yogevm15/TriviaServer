#include "MenuRequestHandler.h"
#include "SignoutException.h"
MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory,std::string username): handlerFactory(handlerFactory){
	this->username = username;
}
bool MenuRequestHandler::isRequestRelevant(RequestInfo request) {
	return request.code == GET_TOP_STATISTICS_REQUEST || request.code== LOGOUT_REQUEST||request.code == CREATE_ROOM_REQUEST || request.code == JOIN_ROOM_REQUEST || request.code == GET_ROOM_DETAILS_REQUEST ||request.code == GET_MY_STATISTICS_REQUEST || request.code == GET_ROOMS_ID_REQUEST;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request) {
	switch (request.code)
	{
		case CREATE_ROOM_REQUEST:
			return createRoom(request);
		case JOIN_ROOM_REQUEST:
			return joinRoom(request);
		case GET_ROOM_DETAILS_REQUEST:
			return getRoomDetails(request);
		case GET_TOP_STATISTICS_REQUEST:
			return getTopStatistics(request);
		case GET_MY_STATISTICS_REQUEST:
			return getStatistics(request);
		case LOGOUT_REQUEST:
			return signout(request);
		case GET_ROOMS_ID_REQUEST:
			return getRoomsId(request);
	}

}
std::string MenuRequestHandler::getUsername() {
	return this->username;
}
RequestResult MenuRequestHandler::signout(RequestInfo request){
	RequestResult result;
	LogoutResponse response;
	LogoutRequest logoutRequest;
	logoutRequest.username = this->username;
	this->handlerFactory.getLoginManager().Logout(logoutRequest);
	response.status = LOGOUT_SUCCESS;
	result.newHandler = handlerFactory.createLoginRequestHandler();
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult MenuRequestHandler::getRoomsId(RequestInfo request){
	RequestResult result;
	GetRoomsIdResponse response;
	response.ids = this->handlerFactory.getRoomManager().getRoomsId();
	if (response.ids.size() > 0) {
		response.status = GET_ALL_ROOMS_ID_SUCCESS;
	}
	else {
		response.status = GET_ALL_ROOMS_ID_NO_ROOM;
	}
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult MenuRequestHandler::getRoomDetails(RequestInfo request){
	RequestResult result;
	GetRoomDetailsResponse response;
	GetRoomDetailsRequest playersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
	Room* room = this->handlerFactory.getRoomManager().getRoom(playersInRoomRequest.roomId);
	if (room == nullptr){
		response.status = GET_ROOM_DETAILS_NOT_EXIST;
	}
	else{
		response.roomData = room->getRoomData();
		response.status = GET_ROOM_DETAILS_SUCCESS;
	}
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult MenuRequestHandler::getStatistics(RequestInfo request){
	RequestResult result;
	GetMyStatisticsResponse response;
	response.status = GET_MY_STATISTICS_SUCCESS;
	response.playerStatistics = handlerFactory.getStatisticsManager().getPlayerStatistics(username);
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult MenuRequestHandler::getTopStatistics(RequestInfo request) {
	RequestResult result;
	GetTopStatisticsResponse response;
	response.status = GET_TOP_STATISTICS_SUCCESS;
	response.topPlayerStatistics = handlerFactory.getStatisticsManager().getBestPlayers(15);
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult MenuRequestHandler::joinRoom(RequestInfo request){
	RequestResult result;
	JoinRoomResponse response;
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);
	Room* room = this->handlerFactory.getRoomManager().getRoom(joinRoomRequest.roomId);
	if (room == nullptr) {
		response.status = JOIN_ROOM_NOT_EXIST;
		result.newHandler = nullptr;
	}
	else {
		response.status = room->addUser(this->username);
		if (response.status == JOIN_ROOM_SUCCESS) {
			result.newHandler = this->handlerFactory.createRoomMemberRequestHandler(this->username, joinRoomRequest.roomId);
		}
		else {
			result.newHandler = nullptr;
		}
	}
	
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult MenuRequestHandler::createRoom(RequestInfo request){
	RequestResult result;
	CreateRoomResponse response;
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer);
	response.status = this->handlerFactory.getRoomManager().createRoom(username, createRoomRequest);
	result.newHandler = handlerFactory.createRoomAdminRequestHandler(this->username, this->handlerFactory.getRoomManager().getRoomIdByAdmin(this->username));
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}