#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EncryptionFactory.h"
#include "Caesar/Caesar.h"
#include "DES/DES.h"
#include "DES/DESKey.h"
#include "miniAES/MiniAES.h"
#include "miniAES/MiniAESKey.h"
#include "miniAES/MultiplierAES.h"
#include <vector>
#include <string>


class encryptionFactoryTest : public ::testing::Test {
public:
    void SetUp(){}
    void TearDown(){}
};
TEST_F(encryptionFactoryTest, letsStart){

}