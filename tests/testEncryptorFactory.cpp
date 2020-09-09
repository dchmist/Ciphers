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
    EXPECT_EQ(&miniAES, &miniAES_second);
    EXPECT_NE(miniAES, nullptr);
}
TEST_F(encryptionFactoryTest, des_factory_test){
    EncryptorFactory factory;
    const auto &DES = factory.get_encryptor(encryptionTypes::DES);
    const auto &DES_second = factory.get_encryptor(encryptionTypes::DES);
    EXPECT_EQ(&DES, &DES_second);
    EXPECT_NE(DES, nullptr);
}
TEST_F(encryptionFactoryTest, caesar_factory_test){
    EncryptorFactory factory;
    const auto &caesar = factory.get_encryptor(encryptionTypes::Caesar);
    const auto &caesar_second = factory.get_encryptor(encryptionTypes::Caesar);
    EXPECT_EQ(&caesar, &caesar_second);
    EXPECT_NE(&caesar, nullptr);
}