#include "SqliteDatabase.h"
std::vector<Question> SqliteDatabase::getRandomQuestions(int amount) {
	std::string allQuestions = "SELECT * FROM QUESTIONS ORDER BY RANDOM()";
	char* errMessage = nullptr;
	std::vector<Question> questions;
	int res = sqlite3_exec(this->db, allQuestions.c_str(), [](void* questions, int argc, char** argv, char** azColName)->int {
			std::vector<Question>*  temp = static_cast<std::vector<Question>*>(questions);
			std::vector<std::string> answers;
			for (int j = 2; j < 6; j++) {
				std::string ans(argv[j]);
				answers.push_back(ans);
			}
			temp->push_back(Question(argv[1], answers, atoi(argv[6]), temp->size()));
			return 0;
		}, &questions, &errMessage);
	if (amount > questions.size()) {
		return questions;
	}
	else {
		int toslice = questions.size() - amount;
		return std::vector<Question>(questions.begin(), questions.end() - toslice);
	}
	
}
int SqliteDatabase::Signup(SignupRequest request) {
	std::string toReturn = "";
	if (isEmailExist(request.email)||isUsernameExist(request.username)) {
		return SIGNUP_EMAIL_OR_USERNAME_EXIST;
	}
	 
	if (toReturn=="") {
		std::string checkEmailStatement = "INSERT INTO USERS (USERNAME, EMAIL, PASSWORD) VALUES(\"" + request .username + "\", \"" + request.email + "\", \"" + request.password +"\"); ";
		std::string addToStatistics = "INSERT INTO STATISTICS (USERNAME, NUM_OF_GAMES, NUM_OF_WRONG_ANSWERS, NUM_OF_CORRECT_ANSWERS, NUM_OF_TOTAL_ANSWERS, SUM_OF_ANSWERS_TIME) VALUES(\"" + request.username + "\", 0,0,0,0,0); ";
		char* errMessage = nullptr;
		int res1 = sqlite3_exec(this->db, addToStatistics.c_str(), nullptr, nullptr, &errMessage);
		int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), nullptr, nullptr, &errMessage);
		if (res != SQLITE_OK) {
			return SIGNUP_UNEXPECTED_ERR;
		}
		else {
			return SIGNUP_SUCCESS;
		}
	}

	
}

int SqliteDatabase::Login(LoginRequest request) {
	if (!isUsernameExist(request.username)) {
		return LOGIN_USERNAME_NOT_EXIST;
	}
	else{ 
		std::string checkPasswordStatement = "SELECT * FROM USERS WHERE USERNAME = \"" + request.username + "\" AND PASSWORD = \"" + request.password + "\";";
		char* errMessage = nullptr;
		bool correctPassword = false;
		int res = sqlite3_exec(this->db, checkPasswordStatement.c_str(), [](void* correctPassword, int argc, char** argv, char** azColName)->int {
			if (argc > 0) {
				*static_cast<bool*>(correctPassword) = true;
			}
			return 0;
		}, & correctPassword, &errMessage);
		if (correctPassword) {
			return LOGIN_SUCCESS;
		}
		else {
			return LOGIN_INCORRECT_PASSWORD;
		}
	}

}

void SqliteDatabase::Logout(LogoutRequest request) {

}

bool SqliteDatabase::isEmailExist(std::string email) {
	std::string checkEmailStatement = "SELECT * FROM USERS WHERE EMAIL = \"" + email + "\";";
	char* errMessage = nullptr;
	bool isExist = false;
	int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), [](void* isExist, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			*static_cast<bool*>(isExist) = true;
		}
		return 0;
	}, &isExist, &errMessage);
	return isExist;

}

bool SqliteDatabase::isUsernameExist(std::string username) {
	std::string checkUsernameStatement = "SELECT * FROM USERS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	bool isExist = false;
	int res = sqlite3_exec(this->db, checkUsernameStatement.c_str(), [](void* isExist, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			*static_cast<bool*>(isExist) = true;
		}
		return 0;
	}, &isExist, &errMessage);
	return isExist;
}

bool SqliteDatabase::open() {
	std::string dbFileName = "trivia.db";
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	if (res != SQLITE_OK)
	{
		db = nullptr;
		return false;
	}
	return true;
}

void SqliteDatabase::close() {
	sqlite3_close(db);
	db = nullptr;
}

void SqliteDatabase::clear() {

}

float SqliteDatabase::getPlayerSumAnswerTime(std::string username) {
	std::string checkEmailStatement = "SELECT SUM_OF_ANSWERS_TIME FROM STATISTICS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	float AVG = false;
	int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), [](void* AVG, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			*static_cast<float*>(AVG) = atof(argv[0]);
		}
		return 0;
	}, &AVG, &errMessage);
	return AVG;
}

int SqliteDatabase::getPlayerTotalAnswers(std::string username) {
	std::string checkEmailStatement = "SELECT NUM_OF_TOTAL_ANSWERS FROM STATISTICS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	float AVG = false;
	int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), [](void* AVG, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			*static_cast<float*>(AVG) = atof(argv[0]);
		}
		return 0;
		}, &AVG, &errMessage);
	return AVG;
}

int SqliteDatabase::getNumOfCorrectAnswer(std::string username) {
	std::string checkEmailStatement = "SELECT NUM_OF_CORRECT_ANSWERS FROM STATISTICS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	float AVG = false;
	int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), [](void* AVG, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			*static_cast<float*>(AVG) = atof(argv[0]);
		}
		return 0;
	}, &AVG, &errMessage);
	return AVG;
}
int SqliteDatabase::getNumOfWrongAnswers(std::string username) {
	std::string checkEmailStatement = "SELECT NUM_OF_WRONG_ANSWERS FROM STATISTICS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	float AVG = false;
	int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), [](void* AVG, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			*static_cast<float*>(AVG) = atof(argv[0]);
		}
		return 0;
	}, &AVG, &errMessage);
	return AVG;
}
int SqliteDatabase::getNumOfPlayerGames(std::string username) {
	std::string checkEmailStatement = "SELECT NUM_OF_GAMES FROM STATISTICS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	float AVG = false;
	int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), [](void* AVG, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			*static_cast<float*>(AVG) = atof(argv[0]);
		}
		return 0;
	}, &AVG, &errMessage);
	return AVG;
}


std::vector<PlayerStatistics> SqliteDatabase::getTopPlayersStats(int amount) {
	std::string checkEmailStatement = "SELECT USERNAME FROM STATISTICS ORDER BY NUM_OF_CORRECT_ANSWERS DESC, NUM_OF_WRONG_ANSWERS ASC  LIMIT " + std::to_string(amount) + ";";
	char* errMessage = nullptr;
	std::vector<std::string> topUsernames;
	int res = sqlite3_exec(this->db, checkEmailStatement.c_str(), [](void* topUsernames, int argc, char** argv, char** azColName)->int {
		if (argc > 0) {
			(*static_cast<std::vector<std::string>*>(topUsernames)).push_back(argv[0]);
		}
		return 0;
		}, & topUsernames, &errMessage);
	std::vector<PlayerStatistics> topPlayerStatistics;
	for (int i = 0; i < topUsernames.size(); i++) {
		topPlayerStatistics.push_back(getPlayerStats(topUsernames[i]));
	}
	return topPlayerStatistics;
}
PlayerStatistics SqliteDatabase::getPlayerStats(std::string username) {
	PlayerStatistics ps = PlayerStatistics();
	if (this->getPlayerTotalAnswers(username) == 0) {
		ps.averageAnswerTime = 0;
	}
	else {
		ps.averageAnswerTime = this->getPlayerSumAnswerTime(username) / this->getPlayerTotalAnswers(username);
	}
	ps.username = username;
	ps.correctAnswers = getNumOfCorrectAnswer(username);
	ps.wrongAnswers = getNumOfWrongAnswers(username);
	ps.gamesPlayed = getNumOfPlayerGames(username);
	return ps;
}
void SqliteDatabase::addAnswerTime(std::string username, float time) {
	addAnswer(username);
	std::string addAnswerTime = "UPDATE STATISTICS SET SUM_OF_ANSWERS_TIME = (SUM_OF_ANSWERS_TIME + " + std::to_string(time) + ") WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, addAnswerTime.c_str(), nullptr, nullptr, &errMessage);
}
void SqliteDatabase::addCorrectAnswer(std::string username) {
	std::string addCorrectAnswer = "UPDATE STATISTICS SET NUM_OF_CORRECT_ANSWERS = NUM_OF_CORRECT_ANSWERS + 1 WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, addCorrectAnswer.c_str(), nullptr, nullptr, &errMessage);
}
void SqliteDatabase::addWrongAnswer(std::string username) {
	std::string addWrongAnswer = "UPDATE STATISTICS SET NUM_OF_WRONG_ANSWERS = NUM_OF_WRONG_ANSWERS + 1 WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, addWrongAnswer.c_str(), nullptr, nullptr, &errMessage);
}
void SqliteDatabase::addAnswer(std::string username) {
	std::string addAnswer = "UPDATE STATISTICS SET NUM_OF_TOTAL_ANSWERS = NUM_OF_TOTAL_ANSWERS + 1 WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, addAnswer.c_str(), nullptr, nullptr, &errMessage);
}
void SqliteDatabase::addGamePlayed(std::string username) {
	std::string addGame = "UPDATE STATISTICS SET NUM_OF_GAMES = NUM_OF_GAMES + 1 WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, addGame.c_str(), nullptr, nullptr, &errMessage);
}
