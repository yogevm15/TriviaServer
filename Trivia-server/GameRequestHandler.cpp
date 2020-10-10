#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, std::string username, Game* game, int roomId) : handlerFactory(handlerFactory) {
	this->username = username;
	this->roomId = roomId;
	this->game = game;
}
bool GameRequestHandler::isRequestRelevant(RequestInfo request) {
	return request.code == LEAVE_GAME_REQUEST || request.code == GET_QUESTION_REQUEST || request.code == SUBMIT_ANSWER_REQUEST || request.code == GET_RESULTS_REQUEST;

}
RequestResult GameRequestHandler::handleRequest(RequestInfo request) {
	switch (request.code)
	{
	case LEAVE_GAME_REQUEST:
		return leaveGame(request);
	case GET_QUESTION_REQUEST:
		return getQuestion(request);
	case SUBMIT_ANSWER_REQUEST:
		return submitAnswer(request);
	case GET_RESULTS_REQUEST:
		return getResults(request);
	}

}
std::string GameRequestHandler::getUsername() {
	return this->username;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo request) {
	RequestResult result;
	LeaveGameResponse response;
	handlerFactory.getRoomManager().leaveRoomByUsername(username);
	handlerFactory.getGameManager().leaveGameByUsername(username);
	response.status = LEAVE_GAME_SUCCESS;
	result.newHandler = handlerFactory.createMenuRequestHandler(this->username);
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult GameRequestHandler::getQuestion(RequestInfo request) {
	RequestResult result;
	GetQuestionResponse response;
	Question* q = game->getNextQuestionForUser(username);
	if (q != nullptr) {
		response.totalQuestions = game->getQuestionsAmount();
		response.currentQuestion = q->getQuestionId()+1;
		response.answers = q->getAnswers();
		response.question = q->getQuestion();
		response.questionTime = game->getQuestionTime();
		response.status = GET_QUESTION_SUCCESS;
	}
	else{
		response.totalQuestions = game->getQuestionsAmount();
		response.currentQuestion = game->getQuestionsAmount();
		response.answers = std::vector<std::string>();
		response.question ="";
		response.questionTime = game->getQuestionTime();
		response.status = GET_QUESTION_FINISHED;
		handlerFactory.getStatisticsManager().addGamePlayed(username);
	}
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult GameRequestHandler::submitAnswer(RequestInfo request) {
	RequestResult result;
	SubmitAnswerResponse response;
	SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(request.buffer);
	int correct = game->submitAnswer(username, submitAnswerRequest.answerId,handlerFactory.getStatisticsManager());
	response.correctAnswerId = correct;
	response.status = SUBMIT_ANSWER_SUCCESS;
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
RequestResult GameRequestHandler::getResults(RequestInfo request) {
	RequestResult result;
	GetGameResultsResponse response;
	
	std::vector<PlayerResult> results = game->getResults();
	response.status = GET_RESULTS_SUCCESS;
	response.results = results;
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
