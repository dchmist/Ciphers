#include "Caesar/Caesar.h"
#include "Types.h"
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
        return {};
    std::vector<uint8_t> output(buffer.size());
    try{
        auto _encryptor = [&](uint8_t x){return (x + shift)%255;};
        std::transform(buffer.cbegin(), buffer.cend(), output.begin(), _encryptor);
    }
    catch(const std::exception &e){
        std::cerr<<e.what()<<std::endl;
        return {};
    }
    return output;   
}
std::vector<uint8_t> Caesar::decode(const std::vector<uint8_t> &buffer) const{
    if(buffer.size() == 0)
        return {};
    std::vector<uint8_t> output(buffer.size());
    try{
        auto _decryptor = [&](uint8_t x){return (x - shift)%255;};
        std::transform(buffer.begin(), buffer.end(), output.begin(), _decryptor);
    }
    catch(const std::exception &e){
        std::cerr<<e.what()<<std::endl;
        return {};
    }
    return output;
}