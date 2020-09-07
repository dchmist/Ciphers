#include "miniAES/MiniAESKey.h"
#include "miniAES/MiniAESSBoxes.h"

MiniAESKey::MiniAESKey(uint16_t iKey) : initialKey(iKey)
{

}
void MiniAESKey::set_initialKey(uint16_t iKey)
{
    initialKey = iKey;
    calculateFirstRoundKey();
    calculateSecondRoundKey();
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
        return; //TODO throw NO_INITIAL_KEY
    firstRoundKey = (((initialKey>>12) & 0x0F) ^ MiniAESSBoxes::calculateSBoxE(initialKey & 0x0F) ^ 0x01) << 12;
    firstRoundKey |= (((initialKey>>4) & 0x0F) ^ ((firstRoundKey>>12) & 0x0F)) << 4;
    firstRoundKey |= (((initialKey>>8) & 0x0F) ^ ((firstRoundKey>>4) & 0x0F)) << 8;
    firstRoundKey |= (initialKey & 0x0F) ^ ((firstRoundKey>>8)& 0x0F);
    
}
void MiniAESKey::calculateSecondRoundKey()
{
    if(!firstRoundKey)
        return; //TODO throw NO_FIRST_ROUND_KEY
    secondRoundKey = (((firstRoundKey>>12) & 0x0F) ^ MiniAESSBoxes::calculateSBoxE(firstRoundKey & 0x0F) ^ 0x02) << 12;
    secondRoundKey |= (((firstRoundKey>>4) & 0x0F) ^ ((secondRoundKey>>12) & 0x0F)) << 4;
    secondRoundKey |= (((firstRoundKey>>8) & 0x0F) ^ ((secondRoundKey>>4) & 0x0F)) << 8;
    secondRoundKey |= (firstRoundKey & 0x0F) ^ ((secondRoundKey>>8)& 0x0F);
}