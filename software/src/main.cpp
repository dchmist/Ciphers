#include "DES/DES.h"
#include "DataConverter.h"
#include "EncryptionFactory.h"
#include "miniAES/MiniAESKey.h"
#include "miniAES/MiniAES.h"
#include <iostream>
#include <string>
#include <bitset>

// void testMultiply()
// {
//     using namespace MiniAESCipher;

//     uint16_t m = 0b0011001000100011;
//     uint16_t t = 0b0011000011110001;

//     auto res = MultiplierAES::multiply(m, t);
//     uint16_t expectedResult = 0b1000001001000011;
//     if(res == expectedResult)
//         std::cout<<"Udalo sie\n";
//     else{
//         std::cout << "Result : \t"<< std::bitset<16>(res) << std::endl;
//         std::cout << "Expected : \t"<< std::bitset<16>(expectedResult) << std::endl;
//     }
// }
void testKey()
{
    using namespace MiniAESCipher;
    MiniAESKey key;
    key.setInitialKey(std::string("1011001011110110"));

    auto k1 = key.get_firstRoundKey();
    auto k2 = key.get_secondRoundKey();
    
    std::bitset<16> x1(k1);
    std::bitset<16> x2(k2);

    std::cout << "k1 : "<< x1 << std::endl;
    std::cout << "k2 : "<< x2 << std::endl;
}
EncryptorFactory factory;
void testDES()
{
    const auto & desCryptor = factory.get_encryptor(encryptionTypes::DES);
    auto key =std::make_shared<DESCipher::DESKey>();
    if(key->setInitialKey(std::string("1100000011")) != 0)
    {
        std::cout<<"Klucz jest do dupy\n";
        return;
    }
    desCryptor->setKey(key);
    auto plainText = DataConverter::toBytes(std::string{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"});
    std::vector<uint8_t> encoded;
    try{
        encoded = desCryptor->encode(plainText);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return;
    }
    std::cout << "Encoded : " << DataConverter::toString(encoded) << std::endl;
    try{
        plainText = desCryptor->decode(encoded);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return;
    }
    std::cout << "PlainText : " << DataConverter::toString(plainText) << std::endl;
}
#include <algorithm>
void testMiniAES()
{
    const auto & aesEncryptor = factory.get_encryptor(encryptionTypes::miniAES);
    auto key =std::make_shared<MiniAESCipher::MiniAESKey>();
    if(key->setInitialKey(std::string("1011001011110110")) != 0)
    {
        std::cout<<"Klucz AES jest do dupy\n";
        return;
    }
    aesEncryptor->setKey(key);
    auto plainText = DataConverter::toBytes(std::string{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"});
    std::vector<uint8_t> encoded;
    try{
        encoded = aesEncryptor->encode(plainText);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return;
    }
    std::cout << "Encoded : " << DataConverter::toString(encoded) << std::endl;
    try{
        plainText = aesEncryptor->decode(encoded);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return;
    }
    std::cout << "PlainText : " << DataConverter::toString(plainText) << std::endl;
}

int main(int argc, char *argv[]){
    testDES();
    testMiniAES();
    return 0;
}