#include "DES/DES.h"
#include "DataConverter.h"
#include "miniAES/MultiplierAES.h"
#include "miniAES/MiniAESKey.h"
#include "miniAES/MiniAES.h"
#include <iostream>
#include <string>
#include <bitset>

void testDES()
{
    DESCipher::DES obj(std::string("1100000011"));
    auto plainText = DataConverter::toBytes(std::string{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"});
    std::vector<uint8_t> encoded = obj.encode(plainText);
    std::cout << "Encoded : " << DataConverter::toString(encoded) << std::endl;
    plainText = obj.decode(encoded);
    std::cout << "Wynik : " << DataConverter::toString(plainText) << std::endl;
}
void testMultiply()
{
    using namespace MiniAESCipher;

    // std::cout << "Test : "<< std::bitset<4>(MultiplierAES::specific_multiply_with_two_components(0x02, 0x00)) << std::endl;

    uint16_t m = 0b0011001000100011;
    uint16_t t = 0b0011000011110001;

    uint16_t kp = 0b1011001011110110;
    uint16_t f = 0b1111000011110000;

    auto res = MultiplierAES::multiply(m, t);
    // auto res = MultiplierAES::multiply(kp, f);
    std::bitset<16> x(res);
    std::cout << "Wynik : "<< x << std::endl;
}
void testKey()
{
    using namespace MiniAESCipher;
    MiniAESKey key;
    key.set_initialKey(0b1011001011110110);

    auto k1 = key.get_firstRoundKey();
    auto k2 = key.get_secondRoundKey();
    
    std::bitset<16> x1(k1);
    std::bitset<16> x2(k2);

    std::cout << "k1 : "<< x1 << std::endl;
    std::cout << "k2 : "<< x2 << std::endl;
}
#include <algorithm>
void testMiniAES()
{
    MiniAESCipher::MiniAES obj;
    MiniAESCipher::MiniAESKey key{0b1011001011110110};
    obj.setKey(key);
    auto plainText = DataConverter::toBytes(std::string{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"});
    std::vector<uint8_t> encoded = obj.encode(plainText);
    std::cout << "Encoded : " << DataConverter::toString(encoded) << std::endl;
    plainText = obj.decode(encoded);
    std::cout << "Wynik : " << DataConverter::toString(plainText) << std::endl;
    std::cout << "Wynik HEX : ";
    std::for_each(plainText.begin(), plainText.end(), [](uint8_t x){printf("%02X ",x);});
    std::cout << std::endl;
}

int main(int argc, char *argv[]){
    // testMultiply();
    testMiniAES();
    testDES();
    return 0;
}