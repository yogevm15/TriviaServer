#pragma once
#include "Structs.h"
#include "ICryptoAlgorithm.h"

class JsonRequestPacketDeserializer
{
public:
	static void setCryptoAlgorithm(ICryptoAlgorithm* cryptoAlgorithm1) { cryptoAlgorithm = cryptoAlgorithm1; }
	static LoginRequest deserializerLoginRequest(BUFFER buffer);
	static SignupRequest deserializerSignupRequest(BUFFER buffer);
	static GetRoomDetailsRequest deserializeGetPlayersRequest(BUFFER buffer);
	static EditRoomRequest deserializeEditRoomRequest(BUFFER buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(BUFFER buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(BUFFER buffer);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(BUFFER buffer);
private:
	static ICryptoAlgorithm* cryptoAlgorithm;
};

