#ifndef MINI_AES_KEY_H
#define MINI_AES_KEY_H

#include "Ciphers/Abstractions/AbstractKey.h"

namespace MiniAESCipher{
    class MiniAESKey : public AbstractKey{
    public:
        MiniAESKey() = default;

        int setInitialKey(const std::string) override;

        uint16_t get_initialKey();
        uint16_t get_firstRoundKey();
        uint16_t get_secondRoundKey();
    private:
        void calculateFirstRoundKey();
        void calculateSecondRoundKey();
        uint16_t initialKey = 0;
        uint16_t firstRoundKey = 0;
        uint16_t secondRoundKey = 0;
    };
}
#endif