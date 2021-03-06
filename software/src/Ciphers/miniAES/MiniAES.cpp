#include "Ciphers/miniAES/MiniAES.h"
#include "Ciphers/miniAES/MiniAESSBoxes.h"
#include "Ciphers/miniAES/MultiplierAES.h"
#include "ReturnTypes/EncryptionException.h"
#include <memory>

using namespace MiniAESCipher;

void MiniAES::setKey(const std::shared_ptr<AbstractKey> &key)
{
    this->key = std::dynamic_pointer_cast<MiniAESKey>(key);
}
std::vector<uint8_t> MiniAES::encode(const std::vector<uint8_t> &buffer) const
{
    if(key == nullptr)
        throw EncryptionException(std::string("AES key is not initialized."), ERROR_CODE::KEY_NOT_INITIALIZED);
    if(buffer.size() == 0)
        throw EncryptionException(std::string("Empty buffer"), ERROR_CODE::EMPTY_BUFFER);
    uint16_t t{0};
    std::vector<uint8_t> cipher;
    for(size_t i=0; i<buffer.size(); i+=2){
        if(i == buffer.size()-1)
            t = buffer.at(i)<<8 | IV;
        else
            t = buffer.at(i)<<8 | buffer.at(i+1);
        t = t ^ key->get_initialKey();
        F_SBox(SBoxType::E, t);
        ZK(t);
        // t = MultiplierAES::multiply(m, t); // TODO w pewnych przypadkach(np. h,H,V,W) to mnozenie przy dekodowaniu zmienia jeden bajt
        t = t ^ key->get_firstRoundKey();
        F_SBox(SBoxType::E, t);
        ZK(t);
        t = t ^ key->get_secondRoundKey();

        cipher.emplace_back((t>>8) & 0xFF);
        cipher.emplace_back(t & 0xFF);
        t=0;
    }
    return cipher;
}
std::vector<uint8_t> MiniAES::decode(const std::vector<uint8_t> &buffer) const
{
    if(key == nullptr)
        throw EncryptionException(std::string("AES key is not initialized."), ERROR_CODE::KEY_NOT_INITIALIZED);
    if(buffer.size()%2 != 0)
        throw EncryptionException(std::string("Cipher is incorrect."), ERROR_CODE::INVALID_BUFFER);
    if(buffer.size() == 0)
        throw EncryptionException(std::string("Empty buffer"), ERROR_CODE::EMPTY_BUFFER);
    uint16_t s{0};
    std::vector<uint8_t> plaintext;
    for(size_t i=0; i<buffer.size(); i+=2){
        s = buffer.at(i)<<8 | buffer.at(i+1);
        s = s ^ key->get_secondRoundKey();
        ZK(s);
        F_SBox(SBoxType::D, s);
        s = s ^ key->get_firstRoundKey();
        // s = MultiplierAES::multiply(m, s); // TODO w pewnych przypadkach(np. h,H,V,W) to mnozenie przy dekodowaniu zmienia jeden bajt
        ZK(s);
        F_SBox(SBoxType::D, s);
        s = s ^ key->get_initialKey();

        plaintext.emplace_back((s>>8) & 0xFF);
        plaintext.emplace_back(s & 0xFF);
        s=0;
    }
    if(plaintext.back() == IV)
        plaintext.pop_back();
    return plaintext;
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