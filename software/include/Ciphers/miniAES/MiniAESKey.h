#ifndef MINI_AES_KEY_H
#define MINI_AES_KEY_H

#include <cstdint>

class MiniAES;

class MiniAESKey{
public:
    MiniAESKey() = default;
    MiniAESKey(uint16_t);

    void set_initialKey(uint16_t);

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

#endif