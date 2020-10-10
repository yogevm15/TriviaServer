#pragma once
#include <iostream>
#include <string>
#include "Structs.h"
struct RequestInfo;
struct RequestResult;

class IRequestHandler
{
public:

	virtual bool isRequestRelevant(RequestInfo request) = 0;
	virtual RequestResult handleRequest(RequestInfo  request) = 0;
	virtual std::string getUsername() = 0;
};

