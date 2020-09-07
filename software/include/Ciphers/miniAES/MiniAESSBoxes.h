#ifndef MINI_AES_SBOXES_H
#define MINI_AES_SBOXES_H

#include <cstdint>
#include <map>

namespace MiniAESCipher{
    class MiniAESSBoxes{
    public:
        static uint8_t calculateSBoxE(uint8_t);
        static uint8_t calculateSBoxD(uint8_t);
    private:
        static const std::map<uint8_t, uint8_t> SBoxE;
        static const std::map<uint8_t, uint8_t> SBoxD;
    };
}

#endif