#include "gtest/gtest.h"
#include "miniAES/MiniAES.h"
#include "miniAES/MiniAESKey.h"
#include "miniAES/MultiplierAES.h"
#include "DataConverter.h"
#include "ReturnTypes/EncryptionException.h"
#include <algorithm>

TEST(miniAES_test, miniAESKey_success)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1011001011110110")), static_cast<int>(ERROR_CODE::SUCCESS));
}
TEST(miniAES_test, miniAESKey_invalid_key_length_v1)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("")), static_cast<int>(ERROR_CODE::INVALID_KEY_LENGTH));
}
TEST(miniAES_test, miniAESKey_invalid_key_length_v2)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("10110010111101101")), static_cast<int>(ERROR_CODE::INVALID_KEY_LENGTH));
}
TEST(miniAES_test, miniAESKey_invalid_key_format)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("101100101111011s")), static_cast<int>(ERROR_CODE::INVALID_KEY_FORMAT));
}
TEST(miniAES_test, multiply)
{
    uint16_t m = 0b0011001000100011;
    uint16_t t = 0b0011000011110001;

    auto res = MiniAESCipher::MultiplierAES::multiply(m, t);
    uint16_t expectedResult = 0b0011000111110001;
    EXPECT_EQ(res, expectedResult);
}
TEST(miniAES_test, miniAES_encrypt_success)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1011001011110110")), static_cast<int>(ERROR_CODE::SUCCESS));

    MiniAESCipher::MiniAES enc;
    enc.setKey(key);

    std::string plainText{"Lorem Ipsum"};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.encode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    std::vector<uint8_t> encrypted{0xE2, 0x5F, 0x7A, 0x5A, 0x6B, 0xA2, 0xE9, 0x12, 0x74, 0x1A, 0x6B, 0xB5};
    EXPECT_EQ(result.size(), size_t{12});
    EXPECT_EQ(result, encrypted);
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::SUCCESS));
}
TEST(miniAES_test, miniAES_encrypt_empty_buffer)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1011001011110110")), static_cast<int>(ERROR_CODE::SUCCESS));

    MiniAESCipher::MiniAES enc;
    enc.setKey(key);

    std::string plainText{""};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.encode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(result.size(), size_t{0});
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::EMPTY_BUFFER));
}
TEST(miniAES_test, miniAES_encrypt_key_not_initialized)
{
    MiniAESCipher::MiniAES enc;

    std::string plainText{""};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.encode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(result.size(), size_t{0});
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::KEY_NOT_INITIALIZED));
}

TEST(miniAES_test, miniAES_decode_success)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1011001011110110")), static_cast<int>(ERROR_CODE::SUCCESS));

    MiniAESCipher::MiniAES dec;
    dec.setKey(key);

    std::vector<uint8_t> encrypted{0xE2, 0x5F, 0x7A, 0x5A, 0x6B, 0xA2, 0xE9, 0x12, 0x74, 0x1A, 0x6B, 0xB5};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = dec.decode(encrypted);
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    std::string expected{"Lorem Ipsum"};
    EXPECT_EQ(DataConverter::toString(result), expected);
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::SUCCESS));
}
TEST(miniAES_test, miniAES_decode_empty_buffer)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1011001011110110")), static_cast<int>(ERROR_CODE::SUCCESS));

    MiniAESCipher::MiniAES enc;
    enc.setKey(key);

    std::string plainText{""};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.decode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(result.size(), size_t{0});
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::EMPTY_BUFFER));
}
TEST(miniAES_test, miniAES_decode_invalid_buffer)
{
    auto key = std::make_shared<MiniAESCipher::MiniAESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1011001011110110")), static_cast<int>(ERROR_CODE::SUCCESS));

    MiniAESCipher::MiniAES enc;
    enc.setKey(key);

    std::vector<uint8_t> encrypted{0xE2, 0x5F, 0x7A, 0x5A, 0x6B, 0xA2, 0xE9, 0x12, 0x74, 0x1A, 0x6B};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.decode(encrypted);
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(result.size(), size_t{0});
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::INVALID_BUFFER));
}
TEST(miniAES_test, miniAES_decode_key_not_initialized)
{
    MiniAESCipher::MiniAES enc;

    std::string plainText{""};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.decode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(result.size(), size_t{0});
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::KEY_NOT_INITIALIZED));
}