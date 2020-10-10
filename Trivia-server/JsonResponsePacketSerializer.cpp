#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include <string.h>
// for convenience
using json = nlohmann::json;

ICryptoAlgorithm* JsonResponsePacketSerializer::cryptoAlgorithm = nullptr;
std::vector<unsigned char> intToBytes(int paramInt)
{
    std::vector<BYTE> arrayOfByte(4);
    for (int i = 0; i < 4; i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(errorResponse response) {
    json Json;
    BUFFER buffer;
    BYTE code = ERROR_RESPONSE_CODE;
    buffer.push_back(code);
    Json["messege"] = response.message;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(LogoutResponse response) {
    json Json;
    BUFFER buffer;
    BYTE code = LOGOUT_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(SignupResponse response) {
    json Json;
    BUFFER buffer;
    BYTE code = SIGNUP_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = (cryptoAlgorithm->encrypt(Json.dump()));
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(LoginResponse response) {
    json Json;
    BUFFER buffer;
    BYTE code = LOGIN_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}


BUFFER JsonResponsePacketSerializer::serializeResponse(GetRoomsIdResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = GET_ROOMS_ID_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    Json["ids"] = response.ids;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(GetRoomDetailsResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = GET_ROOM_DETAILS_RESPONSE_CODE;
    buffer.push_back(code);
    Json["isActive"] = response.roomData.isActive;
    Json["status"] = response.status;
    Json["players"] = response.roomData.players;
    Json["id"] = response.roomData.id;
    Json["admin"] = response.roomData.admin;
    Json["maxPlayers"] = response.roomData.maxPlayers;
    Json["questionsCount"] = response.roomData.questionCount;
    Json["secondsForQuestions"] = response.roomData.timePerQuestion;
    Json["name"] = response.roomData.name;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = JOIN_ROOM_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = CREATE_ROOM_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse response) {
    BUFFER buffer;
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = CLOSE_ROOM_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse response) {
	json Json;
	json roomsJson;
	BUFFER buffer;
	BYTE code = LEAVE_ROOM_RESPONSE_CODE;
	buffer.push_back(code);
	Json["status"] = response.status;
	std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
	BUFFER content(json_string.begin(), json_string.end());
	int len = content.size();
	BUFFER sizeBuffer = intToBytes(len);
	buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
	buffer.insert(buffer.end(), content.begin(), content.end());
	return buffer;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = LEAVE_GAME_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(StartGameResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = START_GAME_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}
BUFFER JsonResponsePacketSerializer::serializeResponse(EditRoomResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = EDIT_ROOM_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = GET_QUESTION_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    Json["question"] = response.question;
    Json["answers"] = response.answers;
    Json["currentQuestion"] = response.currentQuestion;
    Json["totalQuestions"] = response.totalQuestions;
    Json["questionTime"] = response.questionTime;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = SUBMIT_ANSWER_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    Json["correctAnswerId"] = response.correctAnswerId;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse response) {
    json Json;
    json roomsJson;
    BUFFER buffer;
    BYTE code = GET_RESULTS_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    Json["results"] = std::vector<json>();
    for (int i = 0; i < response.results.size();i++) {
        json temp;
        temp["username"] = response.results[i].username;
        temp["correctAnswerCount"] = response.results[i].correctAnswerCount;
        temp["wrongAnswerCount"] = response.results[i].wrongAnswerCount;
        temp["averageAnswerTime"] = response.results[i].averageAnswerTime;
        Json["results"].push_back(temp);
    }
    
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(NewAdminResponse response) {
    json Json;
    BUFFER buffer;
    BYTE code = NEW_ADMIN_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(GetMyStatisticsResponse response) {
    json Json;
    BUFFER buffer;
    BYTE code = GET_MY_STATISTICS_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    Json["gamesPlayed"] = response.playerStatistics.gamesPlayed;
    Json["averageAnswerTime"] = response.playerStatistics.averageAnswerTime;
    Json["correctAnswers"] = response.playerStatistics.correctAnswers;
    Json["wrongAnswers"] = response.playerStatistics.wrongAnswers;
    Json["username"] = response.playerStatistics.username;
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}

BUFFER JsonResponsePacketSerializer::serializeResponse(GetTopStatisticsResponse response) {
    json Json;
    BUFFER buffer;
    BYTE code = GET_MY_STATISTICS_RESPONSE_CODE;
    buffer.push_back(code);
    Json["status"] = response.status;
    Json["topPlayerStatistics"] = std::vector<json>();
    for (int i = 0; i < response.topPlayerStatistics.size(); i++) {
        json temp;

        temp["gamesPlayed"] = response.topPlayerStatistics[i].gamesPlayed;
        temp["averageAnswerTime"] = response.topPlayerStatistics[i].averageAnswerTime;
        temp["correctAnswers"] = response.topPlayerStatistics[i].correctAnswers;
        temp["wrongAnswers"] = response.topPlayerStatistics[i].wrongAnswers;
        temp["username"] = response.topPlayerStatistics[i].username;
        Json["topPlayerStatistics"].push_back(temp);
    }
    std::string json_string = cryptoAlgorithm->encrypt(Json.dump());
    BUFFER content(json_string.begin(), json_string.end());
    int len = content.size();
    BUFFER sizeBuffer = intToBytes(len);
    buffer.insert(buffer.end(), sizeBuffer.begin(), sizeBuffer.end());
    buffer.insert(buffer.end(), content.begin(), content.end());
    return buffer;
}