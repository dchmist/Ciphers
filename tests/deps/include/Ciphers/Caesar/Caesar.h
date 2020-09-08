#ifndef CAESAR_H
#define CAESAR_H

#include "Abstractions/AbstractEncryption.h"

namespace CaesarCipher{
    class Caesar : public AbstractEncryption{
    public:
        Caesar(int shift=5);

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;
        void setKey(const std::shared_ptr<AbstractKey>&){}
    private:
        int shift;
    };
}
#endif