#include "OTPCryptoAlgorithm.h"
#include <random>
#include <algorithm>
std::string random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}


std::string OTPCryptoAlgorithm::encrypt(std::string message) {
    std::string output = message;
    std::string key = random_string(message.length());
    for (int i = 0; i < message.size(); i++)
        output[i] = message[i] ^ key[i];
    output.append(key);
    return output;
}

std::string OTPCryptoAlgorithm::decrypt(std::string message) {
    std::string output = message.substr(0, message.length() / 2);
    std::string key = message.substr(message.length() / 2);

    for (int i = 0; i < output.size(); i++)
        output[i] = output[i] ^ key[i];

    return output;
}

