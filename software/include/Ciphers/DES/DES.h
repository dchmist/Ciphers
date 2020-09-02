#ifndef DES_CODER_H
#define DES_CODER_H

#include "Types.h"
#include "AbstractEncryption.h"
#include <bitset>

namespace DESCipher{
    class DES : public AbstractEncryption{
    public:
        DES() = default;
        DES(const std::bitset<10>);
        void setInitialKey(const std::bitset<10>);

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;

    private:
        std::bitset<10> initialKey;
        mutable std::bitset<8> firstRoundKey;
        mutable std::bitset<8> secondRoundKey;

        void generateRoundKeys() const;
        std::bitset<10> permutationP10() const;
        std::bitset<8> permutationP10w8(const std::bitset<10>&) const;
        void permutationSL1(std::string&) const;
        std::bitset<10> permutationSL2(const std::bitset<10> &) const;

    };
}
#endif /* DES_CODER_H */