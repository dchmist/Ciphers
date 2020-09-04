#ifndef MINI_AES_H
#define MINI_AES_H

#include "AbstractEncryption.h"

namespace MiniAESCipher{
    
    class MiniAES  : public AbstractEncryption{
    public:
        MiniAES();

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;
    private:
        const uint8_t iv = 0xEB;
        void apendIV();
        void checkAndRemoveIV();
    };
}
#endif /* MINI_AES_H */