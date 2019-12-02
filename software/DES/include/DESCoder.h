#ifndef DESCODER_H
#define DESCODER_H

#include <vector>
#include <map>
#include "Types.h"

namespace DES{

    class DESCoder {
    public:
        DESCoder();
        DESCoder(const DESCoder& orig);
        virtual ~DESCoder();
        
        void setKey(std::vector<int> a_key);
        void setKey(std::vector<uint8_t> a_key);
        
        uint32_t encrypt(std::vector<int> &a_data);
        uint32_t decrypt(std::vector<int> a_data);
        
    private:
        std::vector<int> xorVector(std::vector<int> vec1, std::vector<int> vec2);
        void generateRoundKeys(std::vector<int>);
        std::vector<int> shift_once(std::vector<int> a_halfOfKey);
        std::vector<int> shift_twice(std::vector<int> a_halfOfKey);
        std::map<int, std::vector<int>> _roundKeys;
        std::vector<int> _key;
        
        //tables
        std::vector<int> _PC1, _PC2, _P, _E, _IP, _IP1;
    };
}// DES

#endif /* DESCODER_H */

