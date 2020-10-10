#include "RoomManager.h"

int RoomManager::createRoom(std::string username,CreateRoomRequest request) {
    for (int i = 0; i < MAXIMUM_ROOMS_AMOUNT; i++) {
        if (rooms.find(i) == rooms.end()) {
            Room* temp = new Room(username, request,i);
            rooms[i] = temp;
            return CREATE_ROOM_SUCCESS;
        }
    }
    return CREATE_ROOM_MAXIMUM_ROOMS_IN_SERVER;
}

void RoomManager::deleteRoom(int ID) {
    delete rooms[ID];
    rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(int ID) {
    return rooms[ID]->getRoomData().isActive;
}

std::vector<int> RoomManager::getRoomsId() {
    std::vector<int> v;

    for (std::map<int,Room*>::iterator it = this->rooms.begin(); it != this->rooms.end(); ++it) {
        if (!it->second->getRoomData().isActive) {
            v.push_back(it->first);
        }
        
    }
    return v;
}
RoomData RoomManager::getRoomData(int ID) {

    for (std::map<int, Room*>::iterator it = this->rooms.begin(); it != this->rooms.end(); ++it) {
        if (it->first==ID) {
            return it->second->getRoomData();
        }
    }
    RoomData roomData;
    roomData.id = ROOM_NOT_EXIST_ID;
    return roomData;
}
Room* RoomManager::getRoom(int ID) {
    if (rooms.find(ID) == rooms.end()) {
        return nullptr;
    }
    return rooms[ID];
}
void RoomManager::deleteRoomByAdmin(std::string admin) {
    for (std::map<int, Room*>::iterator it = this->rooms.begin(); it != this->rooms.end(); ++it) {
        if (it->second->getRoomData().admin==admin) {
            this->deleteRoom(it->first);
            return;
        }
    }
}
void RoomManager::leaveRoomByUsername(std::string username) {
    for (std::map<int, Room*>::iterator it = this->rooms.begin(); it != this->rooms.end(); ++it) {
        
        if (it->second->removeUser(username)) {
            deleteRoom(it->first);
            return;
        }
        if (username == it->second->getRoomData().admin) {
            it->second->newAdmin();
        }
        
    }
}
int RoomManager::getRoomIdByAdmin(std::string admin) {
    for (std::map<int, Room*>::iterator it = this->rooms.begin(); it != this->rooms.end(); ++it) {
        if (it->second->getRoomData().admin == admin) {
            return it->first;
        }
    }
}