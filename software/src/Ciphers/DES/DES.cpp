#include "DES/DES.h"

using namespace DESCipher;

DES::DES()
{

}
std::vector<uint8_t> DES::encode(const std::vector<uint8_t> &buffer) const
{
    return buffer;
}
std::vector<uint8_t> DES::decode(const std::vector<uint8_t> &buffer) const
{
    return buffer;
}