#include "miniAES/MiniAESKey.h"
#include "miniAES/MiniAESSBoxes.h"
#include "ReturnTypes/EncryptionException.h"
#include <bitset>
#include <algorithm>

using namespace MiniAESCipher;

int MiniAESKey::setInitialKey(const std::string key)
{
    if(key.size() != size_t{16})
        return (int)ERROR_CODE::INVALID_KEY;
    auto ptr = std::find_if(key.begin(), key.end(), [](char c){return (c =='0' || c =='1') ? false : true;});
    if(ptr != key.end())
        return (int)ERROR_CODE::INVALID_KEY_FORMAT;
    initialKey = std::bitset<16>{key}.to_ulong() & 0xFFFF;
    calculateFirstRoundKey();
    calculateSecondRoundKey();
    return (int)ERROR_CODE::SUCCESS;
}
uint16_t MiniAESKey::get_initialKey()
{
    return initialKey;
}
uint16_t MiniAESKey::get_firstRoundKey()
{
    if(firstRoundKey == 0)
        calculateFirstRoundKey();
    return firstRoundKey;
}
uint16_t MiniAESKey::get_secondRoundKey()
{
    if(secondRoundKey == 0)
        calculateSecondRoundKey();
    return secondRoundKey;
}
void MiniAESKey::calculateFirstRoundKey()
{
    if(!initialKey)
        throw EncryptionException("The initial AES key is not initialized", ERROR_CODE::KEY_NOT_INITIALIZED);
    firstRoundKey = (((initialKey>>12) & 0x0F) ^ MiniAESSBoxes::calculateSBoxE(initialKey & 0x0F) ^ 0x01) << 12;
    firstRoundKey |= (((initialKey>>4) & 0x0F) ^ ((firstRoundKey>>12) & 0x0F)) << 4;
    firstRoundKey |= (((initialKey>>8) & 0x0F) ^ ((firstRoundKey>>4) & 0x0F)) << 8;
    firstRoundKey |= (initialKey & 0x0F) ^ ((firstRoundKey>>8)& 0x0F);
    
}
void MiniAESKey::calculateSecondRoundKey()
{
    if(!firstRoundKey)
        calculateFirstRoundKey();
    secondRoundKey = (((firstRoundKey>>12) & 0x0F) ^ MiniAESSBoxes::calculateSBoxE(firstRoundKey & 0x0F) ^ 0x02) << 12;
    secondRoundKey |= (((firstRoundKey>>4) & 0x0F) ^ ((secondRoundKey>>12) & 0x0F)) << 4;
    secondRoundKey |= (((firstRoundKey>>8) & 0x0F) ^ ((secondRoundKey>>4) & 0x0F)) << 8;
    secondRoundKey |= (firstRoundKey & 0x0F) ^ ((secondRoundKey>>8)& 0x0F);
}