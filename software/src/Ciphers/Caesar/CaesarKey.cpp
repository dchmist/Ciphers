#include "Caesar/CaesarKey.h"
#include "ReturnTypes/ErrorCodes.h"
#include <algorithm>

using namespace CaesarCipher;
int CaesarKey::setInitialKey(const std::string key)
{
    if(key.size() == size_t{0})
        return (int)ERROR_CODE::INVALID_KEY_LENGTH;
    
    auto isDig = [](char c){ return !static_cast<bool>(isdigit(c)); };
    auto ptr = std::find_if(key.begin(), key.end(), isDig);
    if(ptr != key.end())
        return (int)ERROR_CODE::INVALID_KEY_FORMAT;
    shift = atoi(key.c_str());
    if(shift > 100){
        return (int)ERROR_CODE::INVALID_KEY;
    }
    return (int)ERROR_CODE::SUCCESS;
}
int CaesarKey::getShift() const
{
    return shift;
}