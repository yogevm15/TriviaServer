#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <string.h>
using json = nlohmann::json;

ICryptoAlgorithm* JsonRequestPacketDeserializer::cryptoAlgorithm = nullptr;
LoginRequest JsonRequestPacketDeserializer::deserializerLoginRequest(BUFFER buffer) {
	std::string stringJson(buffer.begin(), buffer.end());
	json Json = json::parse(cryptoAlgorithm->decrypt(stringJson));
	LoginRequest request;
	Json.at("username").get_to(request.username);
	Json.at("password").get_to(request.password);
	return request;

}
SignupRequest JsonRequestPacketDeserializer::deserializerSignupRequest(BUFFER buffer) {
	std::string stringJson(buffer.begin(), buffer.end());
	json Json = json::parse(cryptoAlgorithm->decrypt(stringJson));
	SignupRequest request;
	Json.at("username").get_to(request.username);
	Json.at("password").get_to(request.password);
	Json.at("email").get_to(request.email);
	return request;
}

GetRoomDetailsRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(BUFFER buffer) {
	std::string stringJson(buffer.begin(), buffer.end());
	json Json = json::parse(cryptoAlgorithm->decrypt(stringJson));
	GetRoomDetailsRequest request;
	Json.at("roomId").get_to(request.roomId);
	return request;
}
EditRoomRequest JsonRequestPacketDeserializer::deserializeEditRoomRequest(BUFFER buffer) {
	std::string stringJson(buffer.begin(), buffer.end());
	json Json = json::parse(cryptoAlgorithm->decrypt(stringJson));
	EditRoomRequest request;
	Json.at("roomName").get_to(request.roomName);
	Json.at("maxUsers").get_to(request.maxUsers);
	Json.at("questionCount").get_to(request.questionCount);
	Json.at("answerTimeout").get_to(request.answerTimeout);
	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(BUFFER buffer) {
	std::string stringJson(buffer.begin(), buffer.end());
	json Json = json::parse(cryptoAlgorithm->decrypt(stringJson));
	JoinRoomRequest request;
	Json.at("roomId").get_to(request.roomId);
	return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(BUFFER buffer) {
	std::string stringJson(buffer.begin(), buffer.end());
	json Json = json::parse(cryptoAlgorithm->decrypt(stringJson));
	CreateRoomRequest request;
	Json.at("answerTimeout").get_to(request.answerTimeout);
	Json.at("maxUsers").get_to(request.maxUsers);
	Json.at("questionCount").get_to(request.questionCount);
	Json.at("roomName").get_to(request.roomName);
	return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(BUFFER buffer) {
	std::string stringJson(buffer.begin(), buffer.end());
	json Json = json::parse(cryptoAlgorithm->decrypt(stringJson));
	SubmitAnswerRequest request;
	Json.at("answerId").get_to(request.answerId);
	return request;
}