#include "Room.h"
#include <algorithm>

Room::Room(std::string username, CreateRoomRequest request,unsigned int id){
	RoomData temp;
	temp.id = id;
	temp.admin = username;
	temp.isActive = false;
	temp.maxPlayers = request.maxUsers;
	temp.name = request.roomName;
	temp.questionCount = request.questionCount;
	temp.timePerQuestion = request.answerTimeout;
	data = temp;
	users.push_back(username);
}

int Room::addUser(std::string username) {
	if (users.size()<data.maxPlayers) {
		this->users.push_back(username);
		return JOIN_ROOM_SUCCESS;
	}
	return JOIN_ROOM_MAXIMUM_USERS_IN_ROOM;
	
}

bool Room::removeUser(std::string username) {
	this->users.erase(std::remove(this->users.begin(), this->users.end(), username), this->users.end());
	return this->getAllUsers().size() == 0;

}

std::vector<std::string> Room::getAllUsers() {
	return this->users;
}

RoomData Room::getRoomData() {
	data.players = users;
	return data;
}
void Room::newAdmin() {
	this->data.admin = users[0];
}
void Room::setRoomData(EditRoomRequest request) {
	data.maxPlayers = request.maxUsers;
	data.name = request.roomName;
	data.questionCount = request.questionCount;
	data.timePerQuestion = request.answerTimeout;
}

void Room::start() {
	this->data.isActive = true;
}