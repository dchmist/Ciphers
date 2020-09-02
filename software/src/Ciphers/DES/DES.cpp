#include "DES/DES.h"
#include <iostream>
#include <algorithm>

using namespace DESCipher;

DES::DES(const std::string initKey):
setOfKeys(initKey)
{
}
void DES::setInitialKey(const std::string key)
{
    setOfKeys.setInitialKey(key);
}
std::vector<uint8_t> DES::encode(const std::vector<uint8_t> &buffer) const
{
    std::vector<uint8_t> cryptogram(buffer.size());
    std::transform(buffer.begin(), buffer.end(), cryptogram.begin(), [&](uint8_t singleByte){ 
        singleByte = initialPermutation(singleByte);
        singleByte = encode_singleByte(singleByte, keyRound::first);
        singleByte = cross(singleByte);
        singleByte = encode_singleByte(singleByte, keyRound::second);
        singleByte = reversePermutation(singleByte);
        return singleByte;
    });
    return cryptogram;
}
uint8_t DES::encode_singleByte(const uint8_t toEncrypt, keyRound) const
{
    auto copy = toEncrypt & 0x0F;
    copy = permutationP4w8(copy);
    copy ^= static_cast<uint8_t>(setOfKeys.get_firstRoundKey().to_ulong());
    uint8_t resultSBox = SBox(copy);
    resultSBox = permutationP4(resultSBox);
    copy = (toEncrypt & 0xF0) >> 4;
    copy ^= resultSBox;
    copy <<= 4;
    copy |= toEncrypt & 0x0F;
    return copy;
}
uint8_t DES::permutationP4w8(const uint8_t toPerm) const
{
    uint8_t result{0x00};
    result |= ((toPerm >> 3) & 0x01);
    result |= ((toPerm << 1) & 0x0B);
    result |= ((toPerm << 3) & 0x70);
    result |= ((toPerm << 7) & 0x80);
    return result;
}
uint8_t DES::SBox(const uint8_t toSBox) const
{
    uint8_t partSBox1 = (toSBox >> 4) & 0x0F;
    uint8_t partSBox2 = toSBox & 0x0F;
    uint8_t SBox1[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
    uint8_t SBox2[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
    uint8_t row1= (partSBox1>>2 & 0x02) | (partSBox1 & 0x01);
    uint8_t col1 = (partSBox1>>1) & 0x03;
    uint8_t row2 = (partSBox2>>2 & 0x02) | (partSBox2 & 0x01);
    uint8_t col2 = (partSBox2>>1) & 0x03;
    return (SBox1[row1][col1] << 2) | (SBox2[row2][col2]);
}
uint8_t DES::permutationP4(const uint8_t toPerm) const
{
    uint8_t result{0x00};
    result |= ((toPerm >> 7) & 0x01);
    result |= ((toPerm >> 4) & 0x02);
    result |= ((toPerm >> 2) & 0x04);
    result |= ((toPerm >> 3) & 0x08);
    return result;
}
std::vector<uint8_t> DES::decode(const std::vector<uint8_t> &buffer) const
{
    std::vector<uint8_t> cryptogram(buffer.size());
    std::transform(buffer.begin(), buffer.end(), cryptogram.begin(), [&](uint8_t singleByte){ 
        singleByte = initialPermutation(singleByte);
        singleByte = encode_singleByte(singleByte, keyRound::second);
        singleByte = cross(singleByte);
        singleByte = encode_singleByte(singleByte, keyRound::first);
        singleByte = reversePermutation(singleByte);
        return singleByte;
    });
    return cryptogram;
}
uint8_t DES::initialPermutation(uint8_t toPerm) const
{
    uint8_t IP{0x00};
    IP |= ((toPerm >> 1) & 0x09);
    IP |= ((toPerm >> 2) & 0x02);
    IP |= ((toPerm << 2) & 0x04);
    IP |= ((toPerm >> 3) & 0x10);
    IP |= toPerm & 0x20;
    IP |= ((toPerm << 4) & 0x40);
    IP |= ((toPerm << 1) & 0x80);
    return IP;
}
uint8_t DES::cross(uint8_t toCross) const
{
    uint8_t crossed{0x00};
    crossed |= ((toCross << 4) & 0xF0);
    crossed |= ((toCross >> 4) & 0x0F);
    return crossed;
}
uint8_t DES::reversePermutation(uint8_t toPerm) const
{
    uint8_t RP{0x00};
    RP |= ((toPerm >> 2) & 0x01);
    RP |= ((toPerm << 1) & 0x12);
    RP |= ((toPerm >> 4) & 0x04);
    RP |= ((toPerm << 2) & 0x08);
    RP |= toPerm & 0x20;
    RP |= ((toPerm >> 1) & 0x40);
    RP |= ((toPerm << 3) & 0x80);
    return RP;
}