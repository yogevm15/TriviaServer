#pragma once
#include <iostream>
#include <string>

class ICryptoAlgorithm
{
public:
	virtual std::string encrypt(std::string message) = 0;
	virtual std::string decrypt(std::string cypher) = 0;

};

