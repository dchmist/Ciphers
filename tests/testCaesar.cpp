#include "gtest/gtest.h"
#include "Caesar/Caesar.h"
#include "Caesar/CaesarKey.h"
#include "DataConverter.h"
#include "ReturnTypes/EncryptionException.h"
#include <algorithm>

TEST(caesar_test, caesarKey_success){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("15")), static_cast<int>(ERROR_CODE::SUCCESS));
}
TEST(caesar_test, caesarKey_invalid_key_length){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("")), static_cast<int>(ERROR_CODE::INVALID_KEY_LENGTH));
}
TEST(caesar_test, caesarKey_invalid_key_format){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("1234a")), static_cast<int>(ERROR_CODE::INVALID_KEY_FORMAT));
}
TEST(caesar_test, caesarKey_invalid_key){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("101")), static_cast<int>(ERROR_CODE::INVALID_KEY));
}
TEST(caesar_test, caesar_encrypt_success){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("15")), static_cast<int>(ERROR_CODE::SUCCESS));

    CaesarCipher::Caesar enc;
    enc.setKey(key);

    std::string plainText{"Lorem Ipsum"};
    std::vector<uint8_t> encrypted;
    auto shift = [](char c)->uint8_t{return c+15;};
    std::transform(plainText.begin(), plainText.end(), std::insert_iterator<std::vector<uint8_t>>(encrypted, encrypted.begin()), shift);
    std::vector<uint8_t> result;
    try{
        result = enc.encode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
    }
    EXPECT_EQ(result, encrypted);
}
TEST(caesar_test, caesar_encrypt_empty_message){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("15")), static_cast<int>(ERROR_CODE::SUCCESS));

    CaesarCipher::Caesar enc;
    enc.setKey(key);

    std::string plainText{""};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.encode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cerr<< "ERROR STRING: " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::EMPTY_MESSAGE));
}
TEST(caesar_test, caesar_encrypt_key_not_initialized){
    CaesarCipher::Caesar enc;

    std::string plainText{"Lorem Ipsum"};
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.encode(DataConverter::toBytes(plainText));
    }
    catch(EncryptionException &e){
        std::cerr<< "ERROR STRING: " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::KEY_NOT_INITIALIZED));
}
TEST(caesar_test, caesar_decrypt_success){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("15")), static_cast<int>(ERROR_CODE::SUCCESS));

    CaesarCipher::Caesar enc;
    enc.setKey(key);

    std::string expected{"Lorem Ipsum"};
    std::vector<uint8_t> encrypted;
    auto shift = [](char c)->uint8_t{return c+15;};
    std::transform(expected.begin(), expected.end(), std::insert_iterator<std::vector<uint8_t>>(encrypted, encrypted.begin()), shift);
    std::vector<uint8_t> result;
    try{
        result = enc.decode(encrypted);
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
    }
    EXPECT_EQ(DataConverter::toString(result), expected);
}
TEST(caesar_test, caesar_decrypt_key_not_initialized){
    CaesarCipher::Caesar enc;

    std::string expected{"Lorem Ipsum"};
    std::vector<uint8_t> encrypted;
    auto shift = [](char c)->uint8_t{return c+15;};
    std::transform(expected.begin(), expected.end(), std::insert_iterator<std::vector<uint8_t>>(encrypted, encrypted.begin()), shift);
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.decode(encrypted);
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::KEY_NOT_INITIALIZED));
}
TEST(caesar_test, caesar_decrypt_message_empty){
    auto key = std::make_shared<CaesarCipher::CaesarKey>();
    EXPECT_EQ(key->setInitialKey(std::string("15")), static_cast<int>(ERROR_CODE::SUCCESS));

    CaesarCipher::Caesar enc;
    enc.setKey(key);

    std::string expected{"Lorem Ipsum"};
    std::vector<uint8_t> encrypted;
    std::vector<uint8_t> result;
    int err_code{0};
    try{
        result = enc.decode(encrypted);
    }
    catch(EncryptionException &e){
        std::cout<< "ERROR : " << e.what() << std::endl;
        err_code = e.errorCode();
    }
    EXPECT_EQ(err_code, static_cast<int>(ERROR_CODE::EMPTY_MESSAGE));
}