#include "Ciphers/miniAES/MiniAESSBoxes.h"

using namespace MiniAESCipher;

const std::map<uint8_t, uint8_t> MiniAESSBoxes::SBoxE{ 
    {0x00, 0x0E}, {0x01, 0x04}, {0x02, 0x0D}, {0x03, 0x01},
    {0x04, 0x02}, {0x05, 0x0F}, {0x06, 0x0B}, {0x07, 0x08},
    {0x08, 0x03}, {0x09, 0x0A}, {0x0A, 0x06}, {0x0B, 0x0C},
    {0x0C, 0x05}, {0x0D, 0x09}, {0x0E, 0x00}, {0x0F, 0x07}
};
const std::map<uint8_t, uint8_t> MiniAESSBoxes::SBoxD{ 
    {0x00, 0x0E}, {0x01, 0x03}, {0x02, 0x04}, {0x03, 0x08},
    {0x04, 0x01}, {0x05, 0x0C}, {0x06, 0x0A}, {0x07, 0x0F},
    {0x08, 0x07}, {0x09, 0x0D}, {0x0A, 0x09}, {0x0B, 0x06},
    {0x0C, 0x0B}, {0x0D, 0x02}, {0x0E, 0x00}, {0x0F, 0x05}
};
uint8_t MiniAESSBoxes::calculateSBoxE(uint8_t x)
{
    if(SBoxE.count(x))
        return SBoxE.at(x);
    else
        return uint8_t(0xFF);
}
uint8_t MiniAESSBoxes::calculateSBoxD(uint8_t x)
{
    if(SBoxD.count(x))
        return SBoxD.at(x);
    else
        return uint8_t(0xFF);
}