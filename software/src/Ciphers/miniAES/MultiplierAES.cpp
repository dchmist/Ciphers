#include "miniAES/MultiplierAES.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <bitset>
#include <iostream>

uint16_t MultiplierAES::multiply(uint16_t m, uint16_t t)
{
    
    Four4Bits dividedM = divide(m);
    Four4Bits dividedT = divide(t);
    Four4Bits result;

    result.part1 = specific_multiply(dividedM.part1, dividedM.part2, dividedT.part1);
    result.part2 = specific_multiply(dividedM.part1, dividedM.part2, dividedT.part2);
    result.part3 = specific_multiply(dividedM.part3, dividedM.part4, dividedT.part3);
    result.part4 = specific_multiply(dividedM.part3, dividedM.part4, dividedT.part4);

    printf("Result.part1 : %02X\n", result.part1);
    printf("Result.part2 : %02X\n", result.part2);
    printf("Result.part3 : %02X\n", result.part3);
    printf("Result.part4 : %02X\n", result.part4);

    uint16_t returnVal = (result.part4 << 12) & 0xF000;
    returnVal |= (result.part3 << 8) & 0x0F00;
    returnVal |= (result.part2 << 4) & 0x00F0;
    returnVal |= result.part1 & 0x000F;

    return returnVal;
}
MultiplierAES::Four4Bits MultiplierAES::divide(uint16_t x)
{
    Four4Bits result; 
    result.part1 = (x >> 12) & 0x0F;
    result.part2 = (x >> 8) & 0x0F;
    result.part3 = (x >> 4) & 0x0F;
    result.part4 = x & 0x0F;
    return result;
}
uint8_t MultiplierAES::specific_multiply(uint8_t matrix1_part1, uint8_t matrix1_part2, uint8_t matrix2_part)
{
    std::cout << "matrix2_part : " << std::bitset<4>(matrix2_part) << std::endl;
    std::cout << "matrix1_part1 : " << std::bitset<4>(matrix1_part1) << std::endl;
    std::cout << "matrix1_part2 : " << std::bitset<4>(matrix1_part2) << std::endl;
    auto ret1 = specific_multiply_with_two_components(matrix1_part1, matrix2_part);
    auto ret2 = specific_multiply_with_two_components(matrix1_part2, matrix2_part);
    std::cout << "Result : " << std::bitset<4>(ret1) << " ^ " << std::bitset<4>(ret2) << " = " << std::bitset<4>(ret1 ^ ret2) << std::endl << std::endl;
    return  ret1 ^ ret2;
}
uint8_t MultiplierAES::specific_multiply_with_two_components(uint8_t part1, uint8_t part2)
{
    auto make_polynomial = [](uint8_t bits){
        std::vector<int> vec;
        for(int i=3; i>=0; --i){
            if((bits>>i) & 0x01){
                vec.push_back(i);
            }
        }
        return vec;
    };
    auto polynomial1 = make_polynomial(part1);
    auto polynomial2 = make_polynomial(part2);
    std::vector<int> multiplied_polynomial;
    multiplied_polynomial.reserve(8);
    if(polynomial1.size() == size_t(0))
        multiplied_polynomial = polynomial2;
    else if(polynomial2.size() == size_t(0))
        multiplied_polynomial = polynomial1;
    else{
        for(const auto node1 : polynomial1){
            for(const auto node2 : polynomial2){
                multiplied_polynomial.emplace_back(node1+node2);
            }
        }
    }
    std::sort(multiplied_polynomial.begin(), multiplied_polynomial.end(), std::greater<int>());
    uint8_t result{0x00};
    std::for_each(multiplied_polynomial.begin(), multiplied_polynomial.end(), [&result](int x){result ^= 0x01 << x;});
    return divide_by_reduce_polynomial(result);
}
uint8_t MultiplierAES::divide_by_reduce_polynomial(uint8_t input)
{
    int bit_position{7};
    while(bit_position > 4){
        bit_position = found_first_positive_bit(input);
        if(bit_position < 4)
            break;
        input ^= reduction_polynomial << (bit_position - 4);
    }
    return input;
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