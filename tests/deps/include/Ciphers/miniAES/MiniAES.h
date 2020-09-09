#ifndef MINI_AES_H
#define MINI_AES_H

#include "Abstractions/AbstractEncryption.h"
#include "miniAES/MiniAESKey.h"

namespace MiniAESCipher{
    class MiniAES : public AbstractEncryption{
    public:
        void setKey(const std::shared_ptr<AbstractKey>&) override;

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;
    private:
        const uint8_t IV = 0xEB;
        const int16_t m = 0b0011001000100011;
        mutable std::shared_ptr<MiniAESKey> key = nullptr;

        enum class SBoxType{D, E};
        void F_SBox(SBoxType &&, uint16_t &) const;
        void ZK(uint16_t &) const;
    };
}
#endif