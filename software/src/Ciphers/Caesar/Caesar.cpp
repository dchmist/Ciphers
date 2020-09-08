#include "Caesar/Caesar.h"
#include "ReturnTypes/EncryptionException.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace CaesarCipher;

Caesar::Caesar(int s):
shift(s)
{
}
std::vector<uint8_t> Caesar::encode(const std::vector<uint8_t> &buffer) const{
    if(buffer.size() == 0)
        throw EncryptionException(std::string("Empty Message"), ERROR_CODE::EMPTY_MESSAGE);

    std::vector<uint8_t> output(buffer.size());
    auto _encryptor = [&](uint8_t x){return (x + shift)%255;};
    std::transform(buffer.cbegin(), buffer.cend(), output.begin(), _encryptor);

    return output;   
}
std::vector<uint8_t> Caesar::decode(const std::vector<uint8_t> &buffer) const{
    if(buffer.size() == 0)
        throw EncryptionException(std::string("Empty Message"), ERROR_CODE::EMPTY_MESSAGE);

    std::vector<uint8_t> output(buffer.size());
    auto _decryptor = [&](uint8_t x){return (x - shift)%255;};
    std::transform(buffer.begin(), buffer.end(), output.begin(), _decryptor);
    
    return output;
}