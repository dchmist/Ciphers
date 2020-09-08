#ifndef DES_KEY_H
#define DES_KEY_H

#include <bitset>
#include "Abstractions/AbstractKey.h"

namespace DESCipher{
    class DESKey : public AbstractKey{
    public:
        int setInitialKey(const std::string) override;

        std::bitset<8> get_firstRoundKey() const;
        std::bitset<8> get_secondRoundKey() const;
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
#endif