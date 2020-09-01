#include "EncryptionFactory.h"
#include "miniAES/MiniAES.h"
#include "Caesar/Caesar.h"
#include "DES/DES.h"

EncryptorFactory::EncryptorFactory()
{
    encryptors[encryptionTypes::Caesar] = std::make_unique<CaesarCipher::Caesar>();
    encryptors[encryptionTypes::miniAES] = std::make_unique<MiniAESCipher::MiniAES>();
    encryptors[encryptionTypes::DES] = std::make_unique<DESCipher::DES>();
}
const std::unique_ptr<AbstractEncryption> & EncryptorFactory::get_encryptor(encryptionTypes && type)
{
    if(encryptors.count(type) > 0)
        return encryptors.at(type);
    else 
        return nullptr;
}