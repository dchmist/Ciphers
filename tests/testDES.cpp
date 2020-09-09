#include "gtest/gtest.h"
#include "DES/DES.h"
#include "DES/DESKey.h"
#include "DataConverter.h"
#include "ReturnTypes/EncryptionException.h"
#include <algorithm>

TEST(DES_test, DESKey_success)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1100000011")), static_cast<int>(ERROR_CODE::SUCCESS));
}
TEST(DES_test, DESKey_invalid_key_length_v1)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("")), static_cast<int>(ERROR_CODE::INVALID_KEY_LENGTH));
}
TEST(DES_test, DESKey_invalid_key_length_v2)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("110000001")), static_cast<int>(ERROR_CODE::INVALID_KEY_LENGTH));
}
TEST(DES_test, DESKey_invalid_key_format)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("110000001s")), static_cast<int>(ERROR_CODE::INVALID_KEY_FORMAT));
}

TEST(DES_test, DES_encrypt_success)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1100000011")), static_cast<int>(ERROR_CODE::SUCCESS));

    DESCipher::DES enc;
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
    EXPECT_EQ(result.size(), size_t{11});
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::SUCCESS));
}
TEST(DES_test, DES_encrypt_empty_buffer)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1100000011")), static_cast<int>(ERROR_CODE::SUCCESS));

    DESCipher::DES enc;
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
TEST(DES_test, DES_encrypt_key_not_initialized)
{
    DESCipher::DES enc;

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

TEST(DES_test, DES_decode_success)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1100000011")), static_cast<int>(ERROR_CODE::SUCCESS));

    DESCipher::DES dec;
    dec.setKey(key);

    std::vector<uint8_t> encrypted{0x31, 0xBD, 0xD8, 0x1D, 0x3D, 0x08, 0x34, 0x58, 0xDC, 0x5D, 0x3D};
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
TEST(DES_test, DES_decode_empty_buffer)
{
    auto key = std::make_shared<DESCipher::DESKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1100000011")), static_cast<int>(ERROR_CODE::SUCCESS));

    DESCipher::DES enc;
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
TEST(DES_test, DES_decode_key_not_initialized)
{
    DESCipher::DES enc;

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