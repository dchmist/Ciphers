#ifndef DESCODER_H
#define DESCODER_H

#include "Types.h"
#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>

namespace DES{
    typedef std::array<int, 64> block;
    typedef unsigned char byte;
    typedef std::vector<byte> byteVec;
    class DESCoder {
    public:
        DESCoder();
        DESCoder(const DESCoder& orig);
        virtual ~DESCoder();
        
        byteVec encrypt(std::shared_ptr< byteVec > a_key, std::shared_ptr< byteVec > a_data);
        byteVec decrypt(std::shared_ptr< byteVec > a_key, std::shared_ptr< byteVec > a_data);
    private:
        void reverse_RoundKeys(); // necessary to decryption
        byteVec des(std::shared_ptr< byteVec > a_key, std::shared_ptr< byteVec > a_data);
        std::vector<int> XOR_tables(std::vector<int> a_A, std::vector<int> a_B, int size=32);
        std::vector<int> magic_function(std::vector<int> a_bitBlock, int a_key_number);
        std::vector<block> split_message_into_blocks(const std::shared_ptr< byteVec > a_data);
        void add_padding(std::shared_ptr< byteVec > a_data);
        void delete_padding(byteVec &a_data);
        std::vector<int> xorVector(std::vector<int> vec1, std::vector<int> vec2);
        void generate_keys(const std::shared_ptr< byteVec > a_key);
        std::vector<int> shift_once(std::vector<int> &a_vec);
        std::vector<int> shift_twice(std::vector<int> &a_vec);
        std::vector<int> _key;
        
        std::function< std::vector<int>(const std::shared_ptr< byteVec >)> _convertToBits;
        //tables
        std::vector<int> _PC1, _PC2, _P, _E, _IP, _IP1;
        std::array<std::vector<int>, 16> _roundKeys;
    };
}// DES

#endif /* DESCODER_H */

