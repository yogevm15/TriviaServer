#pragma once
#include "Structs.h"
#include "SqliteDatabase.h"
#include <iostream>
#include <vector>
#include <algorithm>
class LoginManager
{
public:
	LoginManager(IDatabase* database) {
		this->database = database;
		this->database->open();
	}
	int Signup(SignupRequest request);
	int Login(LoginRequest request);
	void Logout(LogoutRequest request);
private:
	std::vector<std::string> onlineUsers;
	IDatabase* database;
};

