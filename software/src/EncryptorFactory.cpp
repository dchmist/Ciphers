#include "EncryptorFactory.h"
#include "miniAES/MiniAES.h"
#include "Caesar/Caesar.h"
#include "DES/DES.h"
#include "ReturnTypes/EncryptionException.h"

EncryptorFactory::EncryptorFactory()
{
}
const std::unique_ptr<AbstractEncryption> & EncryptorFactory::get_encryptor(encryptionTypes && type)
{
    if(encryptors.count(type) > 0)
        return encryptors.at(type);
    else if(type == encryptionTypes::Caesar){
        encryptors[encryptionTypes::Caesar] = std::make_unique<CaesarCipher::Caesar>();
        return encryptors.at(type);
    }
    else if(type == encryptionTypes::miniAES){
        encryptors[encryptionTypes::miniAES] = std::make_unique<MiniAESCipher::MiniAES>();
        return encryptors.at(type);
    }
    else if(type == encryptionTypes::DES){
        encryptors[encryptionTypes::DES] = std::make_unique<DESCipher::DES>();
        return encryptors.at(type);
    }
    else 
        throw EncryptionException(std::string("Unrecognize ecryptor type"), ERROR_CODE::UNKNOW);
}