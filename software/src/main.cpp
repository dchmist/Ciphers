#include <iostream>
#include <string>
#include "DES/DES.h"
#include "DataConverter.h"
#include "miniAES/MultiplierAES.h"
#include <bitset>
#include "miniAES/MiniAESKey.h"

void testDES()
{
    DESCipher::DES obj(std::string("1100000011"));
    auto plainText = DataConverter::toBytes(std::string{"Test"});
    std::vector<uint8_t> encoded = obj.encode(plainText);
    std::cout << "Encoded : " << DataConverter::toString(encoded) << std::endl;
    plainText = obj.decode(encoded);
    std::cout << "Wynik : " << DataConverter::toString(plainText) << std::endl;
}
void testMultiply()
{
    uint16_t m = 0b0011001000100011;
    uint16_t t = 0b0011000011110001;

    uint16_t test1 = 0b1011001011110110;
    uint16_t test2 = 0b1111000011110000;

    auto res = MultiplierAES::multiply(m, t);
    std::bitset<16> x(res);
    std::cout << "Wynik : "<< x << std::endl;
}
void testKey()
{
    MiniAESKey key;
    key.set_initialKey(0b1011001011110110);

    auto k1 = key.get_firstRoundKey();
    auto k2 = key.get_secondRoundKey();
    
    std::bitset<16> x1(k1);
    std::bitset<16> x2(k2);

    std::cout << "k1 : "<< x1 << std::endl;
    std::cout << "k2 : "<< x2 << std::endl;
}

int main(int argc, char *argv[]){
    testKey();
    return 0;
}