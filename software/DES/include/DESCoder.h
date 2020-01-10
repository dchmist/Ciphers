#ifndef DESCODER_H
#define DESCODER_H

#include "Types.h"
#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <algorithm>


namespace DES{

    typedef unsigned char byte;
    class DESCoder {
    public:
        DESCoder();
        DESCoder(const DESCoder& orig);
        virtual ~DESCoder();
        
        std::vector<byte> encrypt(std::vector<byte> *a_key, std::vector<byte> *a_data);
        
    private:
        void add_padding(std::vector<byte> *a_data);
        void delete_padding(std::vector<byte> *a_data);
        std::vector<int> xorVector(std::vector<int> vec1, std::vector<int> vec2);
        void generate_keys(const std::vector<byte> *a_key);
        std::vector<int> shift_once(std::vector<int> *a_vec);
        std::vector<int> shift_twice(std::vector<int> *a_vec);
        std::vector<int> _key;
        
        //tables
        std::vector<int> _PC1, _PC2, _P, _E, _IP, _IP1;
        std::array<std::vector<int>, 16> _roundKeys;
    };
}// DES

#endif /* DESCODER_H */

