#include "miniAES/MultiplierAES.h"

uint16_t MultiplierAES::multiply(uint16_t a, uint16_t b)
{
    uint8_t shifted;
    Four4Bits dividedA = divide(a);
    Four4Bits dividedB = divide(b);
    Four4Bits result;
    result.part1 = dividedA.part1 * dividedB.part1;
    int bit_position{7};
    while(bit_position > 6){
        bit_position = found_first_positive_bit(result.part1);
        if(bit_position < 6)
            break;
        shifted = polynomial << bit_position - 4;
        result.part1 = result.part1^shifted;
    }

    return;
}
MultiplierAES::Four4Bits MultiplierAES::divide(uint16_t x)
{
    Four4Bits result; 
    result.part1 = (x >> 12) | 0x0F;
    result.part2 = (x >> 8) | 0x0F;
    result.part3 = (x >> 4) | 0x0F;
    result.part4 = x | 0x0F;
    return result;
}
int MultiplierAES::found_first_positive_bit(uint8_t byte)
{
    uint8_t testByte = 0b10000000;
    int bit_position{7};
    while(bit_position > 0){
        if(byte & testByte){
            break;
        }else{
            testByte >>= 1;
            --bit_position;
        }
    }
    return bit_position;
}