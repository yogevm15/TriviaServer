#pragma once
#include "ICryptoAlgorithm.h"
class OTPCryptoAlgorithm :
    public ICryptoAlgorithm
{
public:
    OTPCryptoAlgorithm() {  }
    std::string encrypt(std::string message);
    std::string decrypt(std::string message);
};

