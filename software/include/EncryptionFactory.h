#ifndef ENCRYPTOR_FACTORY_H
#define ENCRYPTOR_FACTORY_H

#include "Abstractions/AbstractEncryption.h"
#include <memory>
#include <map>

enum class encryptionTypes{
    Caesar,
    DES,
    miniAES,
};

class EncryptorFactory{
public:
    EncryptorFactory();
    const std::unique_ptr<AbstractEncryption> & get_encryptor(encryptionTypes &&);
private:
    std::map< encryptionTypes, std::unique_ptr<AbstractEncryption>> encryptors;
};
#endif