#ifndef MULTIPLIER_AES_H
#define MULTIPLIER_AES_H

#include <cstdint>

namespace MiniAESCipher{
    class MultiplierAES{
    public:
        static uint16_t multiply(uint16_t, uint16_t);
    private:
        const static uint8_t reduction_polynomial = 0b00010011;
        struct Four4Bits{
            uint8_t part1 = 0;
            uint8_t part2 = 0;
            uint8_t part3 = 0;
            uint8_t part4 = 0;
        };
        static Four4Bits divide(uint16_t);
        static uint8_t specific_multiply(uint8_t, uint8_t, uint8_t);
        static uint8_t specific_multiply_with_two_components(uint8_t, uint8_t);
        static uint8_t divide_by_reduce_polynomial(uint8_t);
        static int found_first_positive_bit(uint8_t);
    };
}

#endif