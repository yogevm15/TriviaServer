#pragma once
#include "Structs.h"
class SignoutException :
	public std::exception
{
    

public:
    SignoutException(const char* msg) : std::exception(msg){}
};

