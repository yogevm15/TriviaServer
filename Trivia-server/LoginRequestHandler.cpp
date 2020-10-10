#include "LoginRequestHandler.h"



RequestResult LoginRequestHandler::handleRequest(RequestInfo request){
	
	if (request.code == SIGNUP_REQUEST_CODE) {
		return signup(request);

	}
	else if (request.code == LOGIN_REQUEST_CODE) {
		return login(request);
	}
	RequestResult result;
	return result;

}

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.code == SIGNUP_REQUEST_CODE || request.code == LOGIN_REQUEST_CODE);
}
std::string LoginRequestHandler::getUsername() {
	return this->username;
}
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory &handlerFactory) :handlerFactory(handlerFactory){
	username = "";
}
RequestResult LoginRequestHandler::signup(RequestInfo request) {
	RequestResult result;
	SignupResponse response;
	SignupRequest signup = JsonRequestPacketDeserializer::deserializerSignupRequest(request.buffer);
	response.status = this->handlerFactory.getLoginManager().Signup(signup);
	if (response.status == SIGNUP_SUCCESS) {
		username = signup.username;
		result.newHandler = handlerFactory.createMenuRequestHandler(signup.username);
	}
	else {
		result.newHandler = nullptr;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult LoginRequestHandler::login(RequestInfo request) {
	RequestResult result;
	LoginResponse response;
	LoginRequest login = JsonRequestPacketDeserializer::deserializerLoginRequest(request.buffer);
	response.status = this->handlerFactory.getLoginManager().Login(login);
	if (response.status == LOGIN_SUCCESS) {
		username = login.username;
		result.newHandler = handlerFactory.createMenuRequestHandler(login.username);
	}
	else {
		result.newHandler = nullptr;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}