#include "DESCoder.h"

namespace DES{
    DESCoder::DESCoder() {
        _PC1 = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
        _PC2 = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
        _P   = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
        _E   = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1}; 
        _IP  = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7}; 
        _IP1 = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
    }
    DESCoder::DESCoder(const DESCoder& orig) {
    }
    DESCoder::~DESCoder() {
    }
    std::vector<int> DESCoder::shift_once(std::vector<int> *a_vec){
        std::vector<int> shifted;
        for(int i=1;i<29;++i)
            shifted.push_back(a_vec->at(i%28));
        return shifted;
    }
    std::vector<int> DESCoder::shift_twice(std::vector<int> *a_vec){
        std::vector<int> tmp = shift_once(a_vec);
        return shift_once(&tmp);
    }
    std::array<std::vector<int>, 16> DESCoder::generate_keys(const std::vector<int> *C0, const std::vector<int> *D0){
        std::array<std::vector<int>, 17> C;
        std::array<std::vector<int>, 17> D;
        std::array<std::vector<int>, 16> K; // round keys
        std::vector<int> tmp;
        tmp.reserve(57);
        C[0].insert(C[0].begin(), C0->begin(), C0->end());
        D[0].insert(D[0].begin(), D0->begin(), D0->end());
        for(int i=1; i<=16; i++){ 
            if(i == 1 || i == 2 || i==9 || i==16 ){ // for this round shift once
                C.at(i) = shift_once(&C.at(i-1)); 
                D.at(i) = shift_once(&D.at(i-1));
            } 
            else{// for other rounds shift twice
                C.at(i) = shift_twice(&C.at(i-1)); 
                D.at(i) = shift_twice(&D.at(i-1));
            }

            tmp.insert(tmp.end(), C.at(i).begin(), C.at(i).end());
            tmp.insert(tmp.end(), D.at(i).begin(), D.at(i).end());

            for(int j=0;j<48;++j){
                K.at(i-1).push_back( tmp.at(_PC2[j]-1) );
            }
            tmp.clear();
        }
        for(int i=0;i<16;++i){
            for(auto it : K.at(i))
                std::cout<< it ;
        }
        return K;
    }
    std::vector<byte> func(std::vector<byte> *a_key, std::vector<byte> *a_data){
        std::array<std::vector<int>, 16> K;
        std::vector<int> keyBits;
        // cast a key to bits
        for(int i = 0; i<8;++i){
            std::bitset<8> singleBitValueOfKey(a_key->at(i));
            for(int j = 7; j>=0;--j){
                keyBits.push_back(singleBitValueOfKey[j]);
            }
        }
        std::vector<int> afterPC1;
        afterPC1.reserve(56);
        for (int i=0; i<56;++i)     // permutation pc1
            afterPC1.push_back(keyBits[_PC1[i]-1]);
        
        std::vector<int> C0,D0;
        C0.insert(C0.end(), afterPC1.begin(), afterPC1.begin()+28);
        D0.insert(D0.end(), afterPC1.begin()+28, afterPC1.end());

        K = generate_keys(&C0, &D0);        // generate a round keys 

        std::vector<byte> cipher;

        return cipher;
    }

}//DES