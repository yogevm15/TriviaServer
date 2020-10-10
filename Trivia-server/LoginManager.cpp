#include "LoginManager.h"
#include <algorithm>

int LoginManager::Signup(SignupRequest request) {
	int code = this->database->Signup(request);
	if (code == SIGNUP_SUCCESS) {
		this->onlineUsers.push_back(request.username);
		std::cout << "New signup, username: " << request.username << std::endl;
		return code;
	}
	else {
		return code;
	}
	
}

int LoginManager::Login(LoginRequest request){
	int code = this->database->Login(request);
	if (code == LOGIN_SUCCESS) {
		if (std::find(onlineUsers.begin(), onlineUsers.end(), request.username) == onlineUsers.end()) {
			this->onlineUsers.push_back(request.username);
			std::cout << "New Login, username: "<< request.username << std::endl;
			return code;
		}
		else {
			std::cout << "Username: " << request.username <<" Tried to login but already in..."<< std::endl;
			return LOGIN_ALREADY_ONLINE;
		}
		
	}
	else {
		return code;
	}
}

void LoginManager::Logout(LogoutRequest request) {
	std::cout << "Username: " << request.username << " Logged out." << std::endl;
	this->database->Logout(request);
	this->onlineUsers.erase(std::remove(this->onlineUsers.begin(), this->onlineUsers.end(), request.username), this->onlineUsers.end());
}


