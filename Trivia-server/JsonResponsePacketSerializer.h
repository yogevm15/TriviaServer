#pragma once
#include "Structs.h"
#include "ICryptoAlgorithm.h"

class JsonResponsePacketSerializer{
public:
	static void setCryptoAlgorithm(ICryptoAlgorithm* cryptoAlgorithm1) { cryptoAlgorithm = cryptoAlgorithm1; }
	static BUFFER serializeResponse(errorResponse response);
	static BUFFER serializeResponse(LoginResponse response);
	static BUFFER serializeResponse(SignupResponse response);
	static BUFFER serializeResponse(GetRoomsIdResponse response);
	static BUFFER serializeResponse(GetRoomDetailsResponse response);
	static BUFFER serializeResponse(JoinRoomResponse response);
	static BUFFER serializeResponse(CreateRoomResponse response);
	static BUFFER serializeResponse(GetStatisticsResponse response);
	static BUFFER serializeResponse(LogoutResponse response);
	static BUFFER serializeResponse(CloseRoomResponse response);
	static BUFFER serializeResponse(LeaveRoomResponse response);
	static BUFFER serializeResponse(GetGameResultsResponse response);
	static BUFFER serializeResponse(GetQuestionResponse response);
	static BUFFER serializeResponse(StartGameResponse response);
	static BUFFER serializeResponse(SubmitAnswerResponse response);
	static BUFFER serializeResponse(EditRoomResponse response);
	static BUFFER serializeResponse(LeaveGameResponse response);
	static BUFFER serializeResponse(NewAdminResponse response);
	static BUFFER serializeResponse(GetMyStatisticsResponse response);
	static BUFFER serializeResponse(GetTopStatisticsResponse response);
private:
	static ICryptoAlgorithm* cryptoAlgorithm;
};

