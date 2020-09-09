#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EncryptorFactory.h"
#include "DataConverter.h"
#include "Caesar/Caesar.h"
#include "DES/DES.h"
#include "DES/DESKey.h"
#include "miniAES/MiniAES.h"
#include "miniAES/MiniAESKey.h"
#include "miniAES/MultiplierAES.h"
#include "ReturnTypes/EncryptionException.h"
#include <vector>
#include <string>


class encryptionFactoryTest : public ::testing::Test {
public:
    void SetUp(){}
    void TearDown(){}
};
TEST_F(encryptionFactoryTest, miniAES_factory_test){
    EncryptorFactory factory;
    const auto &miniAES = factory.get_encryptor(encryptionTypes::miniAES);
    const auto &miniAES_second = factory.get_encryptor(encryptionTypes::miniAES);
    EXPECT_EQ(&miniAES,&miniAES_second);
    
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    try
    {
    key->setInitialKey("1011001011110110");
    }
    catch(const EncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    miniAES->setKey(key);

    std::string plainText{"Lorem ipsum testowanko"};
    std::vector<uint8_t> encrypted, res_plainText;
    try
    {
        encrypted = miniAES->encode(DataConverter::toBytes(plainText));
        res_plainText = miniAES->decode(encrypted);
    }
    catch(const EncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
    }

    EXPECT_EQ(DataConverter::toString(res_plainText), plainText);
}
TEST_F(encryptionFactoryTest, des_factory_test){
    EncryptorFactory factory;
    const auto &DES = factory.get_encryptor(encryptionTypes::DES);
    const auto &DES_second = factory.get_encryptor(encryptionTypes::DES);
    EXPECT_EQ(&DES, &DES_second);
    
    auto key = std::make_shared<DESCipher::DESKey>();
    try{
        key->setInitialKey("1100000011");
    }
    catch(const EncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    DES->setKey(key);

    std::string plainText{"Lorem ipsum testowanko"};
    std::vector<uint8_t> encrypted, res_plainText;
    try{
        encrypted = DES->encode(DataConverter::toBytes(plainText));
        res_plainText = DES->decode(encrypted);
    }
    catch(const EncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
    }

    EXPECT_EQ(DataConverter::toString(res_plainText), plainText);
}
TEST_F(encryptionFactoryTest, caesar_factory_test){
    EncryptorFactory factory;
    const auto &caesar = factory.get_encryptor(encryptionTypes::Caesar);
    const auto &caesar_second = factory.get_encryptor(encryptionTypes::Caesar);
    EXPECT_EQ(&caesar, &caesar_second);
    
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    try{
        key->setInitialKey("10");
    }
    catch(const EncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    caesar->setKey(key);

    std::string plainText{"Lorem ipsum testowanko"};
    std::vector<uint8_t> encrypted, res_plainText;
    try{
        encrypted = caesar->encode(DataConverter::toBytes(plainText));
        res_plainText = caesar->decode(encrypted);
    }
    catch(const EncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
    }

    EXPECT_EQ(DataConverter::toString(res_plainText), plainText);
}