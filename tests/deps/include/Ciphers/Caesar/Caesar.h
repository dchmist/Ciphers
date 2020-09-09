#ifndef CAESAR_H
#define CAESAR_H

#include "Ciphers/Abstractions/AbstractEncryption.h"
#include "Ciphers/Caesar/CaesarKey.h"

namespace CaesarCipher{
    class Caesar : public AbstractEncryption{
    public:
        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;
        void setKey(const std::shared_ptr<AbstractKey>&) override;
    private:
        std::shared_ptr<CaesarKey> key = nullptr;
    };
}
#endif