#include "Caesar/Caesar.h"
#include "Types.h"
#include <iostream>

using namespace CaesarCipher;

Caesar::Caesar() {
    _encryptor = [](uint8_t &x){x = (x + 15)%255;};
    _decryptor = [](uint8_t &x){x = (x - 15)%255;};
}
std::vector<uint8_t> Caesar::encode(const std::vector<uint8_t> &buffer) const{
    if(buffer.size() == 0)
        return {};
    try{
        std::for_each(buffer.begin(), buffer.end(), _encryptor);
    }
    catch(const std::exception &e){
        std::cerr<<e.what()<<std::endl;
        return {};
    }
    return buffer;   
}
std::vector<uint8_t> Caesar::decode(const std::vector<uint8_t> &buffer) const{
    if(buffer.size() == 0)
        return {};
    try{
        for_each(buffer.begin(), buffer.end(), _decryptor);
    }
    catch(const std::exception &e){
        std::cerr<<e.what()<<std::endl;
        return {};
    }
    return buffer;
}