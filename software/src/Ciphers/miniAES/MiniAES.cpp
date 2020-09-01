#include "miniAES/MiniAES.h"

using namespace MiniAESCipher;

MiniAES::MiniAES() 
{
}
std::vector<uint8_t> MiniAES::encode(const std::vector<uint8_t> &buffer) const
{
    return buffer;
}
std::vector<uint8_t> MiniAES::decode(const std::vector<uint8_t> &buffer) const
{
    return buffer;
}