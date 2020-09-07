#include "miniAES/MiniAES.h"
#include "miniAES/MiniAESSBoxes.h"

using namespace MiniAESCipher;

MiniAES::MiniAES() 
{
}
std::vector<uint8_t> MiniAES::encode(const std::vector<uint8_t> &buffer) const
{
    //1 Dodanie klucza poczatkowego
    //2 zastosowanie funkcji f_SBox(E, t)
    //3 Zastosowanie funkcji ZK(t)
    //4 Przemnozenie t = t * m
    //5 dodanie klucza pierwszej rundy
    //6 zastowoanie funkcji F_SBox(E, t)
    //7 Zastosowanie funkcji ZK(t)
    //8 Dodawanie klucza rundy drugiej
    return buffer;
}
std::vector<uint8_t> MiniAES::decode(const std::vector<uint8_t> &buffer) const
{
    //1 Dodawanie klucza rundy drugiej
    //2 Zastosowanie funkcji ZK(t)
    //3 zastowoanie funkcji F_SBox(D, t)
    //4 dodanie klucza pierwszej rundy
    //5 Przemnozenie t = t * m
    //6 Zastosowanie funkcji ZK(t)
    //7 zastowoanie funkcji F_SBox(D, t)
    //8 Dodanie klucza poczatkowego
    return buffer;
}
void MiniAES::F_SBox(SBoxType && type, uint16_t &val) const
{
    if(type == SBoxType::E){
        uint8_t hi = MiniAESSBoxes::calculateSBoxE((val>>12) & 0x0F);
        hi <<= 4;
        hi = MiniAESSBoxes::calculateSBoxE((val>>8) & 0x0F);
        uint8_t low = MiniAESSBoxes::calculateSBoxE((val>>8) & 0x0F);
        low <<= 4;
        low = MiniAESSBoxes::calculateSBoxE((val>>4) & 0x0F);
        val = (hi << 8) | low;
    }
    else{
        uint8_t hi = MiniAESSBoxes::calculateSBoxD((val>>12) & 0x0F);
        hi <<= 4;
        hi = MiniAESSBoxes::calculateSBoxD((val>>8) & 0x0F);
        uint8_t low = MiniAESSBoxes::calculateSBoxD((val>>8) & 0x0F);
        low <<= 4;
        low = MiniAESSBoxes::calculateSBoxD((val>>4) & 0x0F);
        val = (hi << 8) | low;
    }
        
}
void MiniAES::ZK(uint16_t &val) const
{
    uint8_t low = val & 0x000F;
    uint8_t high = (val & 0x00F0) >> 4;
    val =  (val & 0xFF00) | (((low << 4) & 0x00F0) | (high & 0x000F));
}