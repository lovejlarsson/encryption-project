#include <iostream>
#include "helper.h"

std::string xorEncryptDecrypt(const std::string& input, const std::string& key) {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key.size()];
    }

    return output;
}
