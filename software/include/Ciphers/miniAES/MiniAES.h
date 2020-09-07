#ifndef MINI_AES_H
#define MINI_AES_H

#include "AbstractEncryption.h"
#include "miniAES/MiniAESKey.h"

namespace MiniAESCipher{
    class MiniAES : public AbstractEncryption{
    public:
        MiniAES() = default;
        void setKey(const MiniAESKey &);

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;
    private:
        const uint8_t IV = 0xEB;
        const int16_t m = 0b0011001000100011;
        mutable MiniAESKey key;

        enum class SBoxType{D, E};
        void F_SBox(SBoxType &&, uint16_t &) const;
        void ZK(uint16_t &) const;
    };
}
#endif /* MINI_AES_H */