#include "miniAES/MiniAES.h"
#include "miniAES/MiniAESSBoxes.h"
#include "miniAES/MultiplierAES.h"
#include <bitset>
#include <iostream>

using namespace MiniAESCipher;

void MiniAES::setKey(const MiniAESKey &inKey)
{
    key = inKey;
}
std::vector<uint8_t> MiniAES::encode(const std::vector<uint8_t> &plaintext) const
{
    uint16_t t{0};
    std::vector<uint8_t> cipher;
    for(size_t i=0; i<plaintext.size(); i+=2){
        if(i == plaintext.size()-1)
            t = plaintext.at(i)<<8 | IV;
        else
            t = plaintext.at(i)<<8 | plaintext.at(i+1);
        t = t ^ key.get_initialKey();
        F_SBox(SBoxType::E, t);
        ZK(t);
        t = MultiplierAES::multiply(m, t);
        t = t ^ key.get_firstRoundKey();
        F_SBox(SBoxType::E, t);
        ZK(t);
        t = t ^ key.get_secondRoundKey();

        cipher.emplace_back((t>>8) & 0xFF);
        cipher.emplace_back(t & 0xFF);
        t=0;
    }
    return cipher;
}
std::vector<uint8_t> MiniAES::decode(const std::vector<uint8_t> &cipher) const
{
    uint16_t t{0};
    std::vector<uint8_t> plaintext;
    for(size_t i=0; i<cipher.size(); i+=2){
        if(i == cipher.size()-1)
            t = cipher.at(i)<<8 | IV;
        else
            t = cipher.at(i)<<8 | cipher.at(i+1);
        t = t ^ key.get_secondRoundKey();
        ZK(t);
        F_SBox(SBoxType::D, t);
        t = t ^ key.get_firstRoundKey();
        t = MultiplierAES::multiply(m, t);
        ZK(t);
        F_SBox(SBoxType::D, t);
        t = t ^ key.get_initialKey();

        plaintext.emplace_back((t>>8) & 0xFF);
        plaintext.emplace_back(t & 0xFF);
        t=0;
    }
    return cipher;
}
void MiniAES::F_SBox(SBoxType && type, uint16_t &val) const
{
    if(type == SBoxType::E){
        uint8_t hi = MiniAESSBoxes::calculateSBoxE((val>>12) & 0x0F);
        hi <<= 4;
        hi |= MiniAESSBoxes::calculateSBoxE((val>>8) & 0x0F);
        uint8_t low = MiniAESSBoxes::calculateSBoxE((val>>4) & 0x0F);
        low <<= 4;
        low |= MiniAESSBoxes::calculateSBoxE(val & 0x0F);
        val = (hi << 8) | low;
    }
    else{
        uint8_t hi = MiniAESSBoxes::calculateSBoxD((val>>12) & 0x0F);
        hi <<= 4;
        hi |= MiniAESSBoxes::calculateSBoxD((val>>8) & 0x0F);
        uint8_t low = MiniAESSBoxes::calculateSBoxD((val>>4) & 0x0F);
        low <<= 4;
        low |= MiniAESSBoxes::calculateSBoxD(val & 0x0F);
        val = (hi << 8) | low;
    }
}
void MiniAES::ZK(uint16_t &val) const
{
    uint8_t low = val & 0x000F;
    uint8_t high = (val & 0x00F0) >> 4;
    val =  (val & 0xFF00) | (((low << 4) & 0x00F0) | (high & 0x000F));
}