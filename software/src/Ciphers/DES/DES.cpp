#include "DES/DES.h"
#include <iostream>
#include <algorithm>

using namespace DESCipher;

DES::DES(const std::bitset<10> initKey):
initialKey(initKey)
{
}
void DES::setInitialKey(const std::bitset<10> key)
{
    initialKey = key;
}
std::vector<uint8_t> DES::encode(const std::vector<uint8_t> &buffer) const
{
    if(!firstRoundKey.any() || !secondRoundKey.any())
        generateRoundKeys();
    return buffer;
}
std::vector<uint8_t> DES::decode(const std::vector<uint8_t> &buffer) const
{
    return buffer;
}
void DES::generateRoundKeys() const
{
    if(!initialKey.any()){
        return;
        // TODO not inizialized key
    }
    auto p10 = permutationP10();
    auto p10s = p10.to_string();
    permutationSL1(p10s);
    p10 = std::bitset<10>{p10s};
    firstRoundKey = permutationP10w8(p10);
    secondRoundKey = permutationP10w8( permutationSL2(p10) );
}
std::bitset<10> DES::permutationP10() const
{
    std::bitset<10> p10;
    p10.set(0, initialKey[4]);
    p10.set(1, initialKey[2]);
    p10.set(2, initialKey[1]);
    p10.set(3, initialKey[9]);
    p10.set(4, initialKey[0]);
    p10.set(5, initialKey[6]);
    p10.set(6, initialKey[3]);
    p10.set(7, initialKey[8]);
    p10.set(8, initialKey[5]);
    p10.set(9, initialKey[7]);
    return p10;
}
void DES::permutationSL1(std::string &buffer) const
{
    std::rotate(buffer.begin(), buffer.begin()+1, buffer.begin()+4);
    std::rotate(buffer.begin()+5, buffer.begin()+6, buffer.end());
}
std::bitset<8> DES::permutationP10w8(const std::bitset<10> &in) const
{
    std::bitset<8> p8;
    p8.set(0, in[1]);
    p8.set(1, in[0]);
    p8.set(2, in[5]);
    p8.set(3, in[2]);
    p8.set(4, in[6]);
    p8.set(5, in[3]);
    p8.set(6, in[7]);
    p8.set(7, in[4]);
    return p8;
}
std::bitset<10> DES::permutationSL2(const std::bitset<10> &in) const
{
    std::bitset<10> sl2;
    sl2.set(0, in[3]);
    sl2.set(1, in[4]);
    sl2.set(2, in[0]);
    sl2.set(3, in[1]);
    sl2.set(4, in[2]);
    sl2.set(5, in[8]);
    sl2.set(6, in[9]);
    sl2.set(7, in[5]);
    sl2.set(8, in[6]);
    sl2.set(9, in[7]);
    return sl2;
}