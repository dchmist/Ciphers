#ifndef DES_CODER_H
#define DES_CODER_H

#include "AbstractEncryption.h"
#include "DES/DESKey.h"

namespace DESCipher{
    class DES : public AbstractEncryption{
    public:
        DES() = default;
        DES(const std::string);
        void setInitialKey(const std::string);

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;

    private:
        DESKey setOfKeys;
        enum class keyRound : bool {first , second};
        uint8_t encode_singleByte(const uint8_t, keyRound) const;
        uint8_t permutationP4w8(const uint8_t) const;
        uint8_t SBox(const uint8_t) const;
        uint8_t permutationP4(const uint8_t) const;

        uint8_t initialPermutation(uint8_t) const;
        uint8_t cross(uint8_t) const;
        uint8_t reversePermutation(uint8_t) const;
    };
}
#endif /* DES_CODER_H */