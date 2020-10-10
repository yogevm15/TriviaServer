#pragma once
#include "Structs.h"

class Room
{
public:
	Room(std::string username, CreateRoomRequest request,unsigned int id);
	int addUser(std::string username);
	bool removeUser(std::string username);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData();
	void setRoomData(EditRoomRequest request);
	void start();
	void newAdmin();
private:
	RoomData data;
	std::vector<std::string> users;
};

