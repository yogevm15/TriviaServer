#pragma once
#include <iostream>
#include <string>
#include <time.h> 
#include <vector>
#include "IRequestHandler.h"
#include "Question.h"
#include <chrono>

class IRequestHandler;
#define BYTE_SIZE 255
#define ERROR_RESPONSE_CODE 0
#define SIGNUP_RESPONSE_CODE 1
#define LOGIN_RESPONSE_CODE 2
#define GET_ROOMS_ID_RESPONSE_CODE 3
#define GET_ROOM_DETAILS_RESPONSE_CODE 4
#define JOIN_ROOM_RESPONSE_CODE 5
#define CREATE_ROOM_RESPONSE_CODE 6
#define GET_MY_STATISTICS_RESPONSE_CODE 7
#define LOGOUT_RESPONSE_CODE 8
#define EDIT_ROOM_RESPONSE_CODE 9
#define CLOSE_ROOM_RESPONSE_CODE 10
#define START_GAME_RESPONSE_CODE 11
#define LEAVE_ROOM_RESPONSE_CODE 12
#define GET_QUESTION_RESPONSE_CODE 13
#define SUBMIT_ANSWER_RESPONSE_CODE 14
#define GET_RESULTS_RESPONSE_CODE 15
#define LEAVE_GAME_RESPONSE_CODE 16
#define NEW_ADMIN_RESPONSE_CODE 17
#define GET_TOP_STATISTICS_RESPONSE_CODE 18

#define SIGNUP_REQUEST_CODE 0
#define LOGIN_REQUEST_CODE 1
#define CREATE_ROOM_REQUEST 2
#define JOIN_ROOM_REQUEST 3
#define GET_ROOM_DETAILS_REQUEST 4
#define GET_MY_STATISTICS_REQUEST 5
#define LOGOUT_REQUEST 6
#define GET_ROOMS_ID_REQUEST 7
#define EDIT_ROOM_REQUEST 8
#define CLOSE_ROOM_REQUEST 9
#define START_GAME_REQUEST 10
#define LEAVE_ROOM_REQUEST 11
#define GET_QUESTION_REQUEST 12
#define SUBMIT_ANSWER_REQUEST 13
#define GET_RESULTS_REQUEST 14
#define LEAVE_GAME_REQUEST 15
#define NEW_ADMIN_REQUEST 16
#define GET_TOP_STATISTICS_REQUEST 17

#define MAXIMUM_ROOMS_AMOUNT 1000

#define LOGIN_SUCCESS 0
#define LOGIN_INCORRECT_PASSWORD 1
#define LOGIN_USERNAME_NOT_EXIST 2
#define LOGIN_UNEXPECTED_ERR 3
#define LOGIN_ALREADY_ONLINE 4


#define SIGNUP_SUCCESS 0
#define SIGNUP_EMAIL_OR_USERNAME_EXIST 1
#define SIGNUP_UNEXPECTED_ERR 2

#define JOIN_ROOM_SUCCESS 0
#define JOIN_ROOM_MAXIMUM_USERS_IN_ROOM 1
#define JOIN_ROOM_NOT_EXIST 2

#define CREATE_ROOM_SUCCESS 0
#define CREATE_ROOM_MAXIMUM_ROOMS_IN_SERVER 1

#define GET_ROOM_DETAILS_SUCCESS 0
#define GET_ROOM_DETAILS_NOT_EXIST 1

#define GET_ALL_ROOMS_ID_SUCCESS 0
#define GET_ALL_ROOMS_ID_NO_ROOM 1

#define LOGOUT_SUCCESS 0

#define EDIT_ROOM_SUCCESS 0
#define EDIT_ROOM_NOT_EXIST 1

#define START_GAME_SUCCESS 0
#define START_GAME_NOT_EXIST 1

#define CLOSE_ROOM_SUCCESS 0

#define LEAVE_ROOM_SUCCESS 0

#define LEAVE_GAME_SUCCESS 0

#define GET_QUESTION_SUCCESS 0
#define GET_QUESTION_FINISHED 1

#define GET_RESULTS_SUCCESS 0
#define GET_RESULTS_ADMIN_STOP 1

#define SUBMIT_ANSWER_SUCCESS 0

#define NEW_ADMIN_SUCCESS 0
#define NEW_ADMIN_NOT_REAL_ADMIN 1

#define GET_MY_STATISTICS_SUCCESS 0

#define GET_TOP_STATISTICS_SUCCESS 0

#define ROOM_NOT_EXIST_ID 12345
typedef unsigned char  BYTE;
typedef std::vector<BYTE> BUFFER;
struct RoomData;
struct PlayerResult {
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};
struct RequestInfo
{
	int code;
	std::string receivalTime;
	BUFFER buffer;
};
struct RequestResult
{
	BUFFER response;
	IRequestHandler* newHandler;
};
struct LoginResponse
{
	unsigned int status;
};
struct SignupResponse
{
	unsigned int status;
};
struct LogoutResponse
{
	unsigned int status;
};
struct GetRoomsIdResponse
{
	unsigned int status;
	std::vector<int> ids;
};

struct GetStatisticsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};
struct JoinRoomResponse
{
	unsigned int status;
};
struct CreateRoomResponse
{
	unsigned int status;
};
struct StartGameResponse
{
	unsigned int status;
};

struct CloseRoomResponse
{
	unsigned int status;
};
struct LeaveRoomResponse
{
	unsigned int status;
};
struct LeaveGameResponse
{
	unsigned int status;
};
struct EditRoomResponse
{
	unsigned int status;
};
struct errorResponse
{
	std::string message;
};
struct GetQuestionResponse {
	unsigned int status;
	std::string question;
	unsigned int totalQuestions;
	unsigned int currentQuestion;
	std::vector<std::string> answers;
	unsigned int questionTime;
};
struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};
struct NewAdminResponse
{
	unsigned int status;
};

struct GetGameResultsResponse {
	unsigned int status;
	std::vector<PlayerResult> results;
};


struct NewAdminRequest
{
	
};

struct LogoutRequest {
	std::string username;
};
struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
};
struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
struct EditRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
struct GetRoomDetailsRequest
{
	unsigned int roomId;
};
struct GetRoomsIdRequest
{
};
struct JoinRoomRequest
{
	unsigned int roomId;
};
struct GetQuestionRequest
{

};
struct SubmitAnswerRequest
{
	int answerId;
};
struct GetResultRequest
{

};
struct GetMyStatisticsRequest
{

};

struct RoomData
{
	unsigned int id;
	std::string admin;
	std::string name;
	unsigned int maxPlayers;
	unsigned int timePerQuestion;
	bool isActive;
	unsigned int questionCount;
	std::vector<std::string> players;
};

struct GetRoomDetailsResponse
{
	unsigned int status;
	RoomData roomData;
};

struct PlayerStatistics {
	float averageAnswerTime;
	unsigned int correctAnswers;
	unsigned int wrongAnswers;
	unsigned int gamesPlayed;
	std::string username;
};

struct GetMyStatisticsResponse
{
	unsigned int status;
	PlayerStatistics playerStatistics;
};
struct GetTopStatisticsResponse
{
	unsigned int status;
	std::vector<PlayerStatistics> topPlayerStatistics;
};