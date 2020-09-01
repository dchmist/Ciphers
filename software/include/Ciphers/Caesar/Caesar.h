#ifndef CAESAR_H
#define CAESAR_H

#include "AbstractEncryption.h"
#include <functional>
#include <algorithm>

namespace CaesarCipher{
    class Caesar : public AbstractEncryption{
    public:
        Caesar();

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;

    private:
        std::function<void(uint8_t&)> _encryptor;
        std::function<void(uint8_t&)> _decryptor;
    };
}
#endif /* CAESAR_H */