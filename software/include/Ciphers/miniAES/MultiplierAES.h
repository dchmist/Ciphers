#ifndef MULTIPLIER_AES_H
#define MULTIPLIER_AES_H

#include <cstdint>

class MultiplierAES{
public:
    static uint16_t multiply(uint16_t, uint16_t);
private:
    const static uint8_t polynomial = 0b00010011;
    struct Four4Bits{
        uint8_t part1;
        uint8_t part2;
        uint8_t part3;
        uint8_t part4;
    };
    static Four4Bits divide(uint16_t);
    static int found_first_positive_bit(uint8_t);
};

#endif