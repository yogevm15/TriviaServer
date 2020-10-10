#pragma once
#include "Structs.h"
#include "Room.h"
#include <map>
class RoomManager
{
public:
	int createRoom(std::string username, CreateRoomRequest request);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<int> getRoomsId();
	RoomData getRoomData(int ID);
	Room* getRoom(int ID);
	int getRoomIdByAdmin(std::string admin);
	void deleteRoomByAdmin(std::string admin);
	void leaveRoomByUsername(std::string username);
private:
	std::map<int, Room*> rooms;
};

