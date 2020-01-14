#include <vector>

#include "DESCoder.h"

const int BLOCK_SIZE = 64;
#define PACKAGE_SIZE 100

namespace DES{
    DESCoder::DESCoder() {
        _PC1 = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
        _PC2 = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
        _P   = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
        _E   = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1}; 
        _IP  = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7}; 
        _IP1 = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
        
        _convertToBits = [](const std::shared_ptr< std::vector<uint8_t> > a_data){
            std::vector<int> bitString;
            for(unsigned int i = 0; i<a_data->size();++i){
                std::bitset<8> bits(a_data->at(i));
                for(int j = 7; j>=0;--j){
                    bitString.push_back(bits[j]);
                }
            }
            return bitString;
        };
    }
    DESCoder::DESCoder(const DESCoder& orig) {
    }
    DESCoder::~DESCoder() {
    }
    std::vector<int> DESCoder::shift_once(std::vector<int> &a_vec){
        std::vector<int> shifted;
        for(int i=1;i<29;++i)
            shifted.push_back(a_vec.at(i%28));
        return shifted;
    }
    std::vector<int> DESCoder::shift_twice(std::vector<int> &a_vec){
        std::vector<int> tmp = shift_once(a_vec);
        return shift_once(tmp);
    }
    void DESCoder::generate_keys(const std::shared_ptr< byteVec > a_key) {
        std::vector<int> keyBits = _convertToBits(a_key);
        std::vector<int> afterPC1;
        afterPC1.reserve(56);
        for (int i=0; i<56;++i)     // permutation pc1
            afterPC1.push_back(keyBits[_PC1[i]-1]);
        
        std::array<std::vector<int>, 17> C;
        std::array<std::vector<int>, 17> D;
        std::vector<int> tmp;
        tmp.reserve(57);
        C[0].insert(C[0].begin(), afterPC1.begin(), afterPC1.begin()+28);
        D[0].insert(D[0].begin(), afterPC1.begin()+28, afterPC1.end());
        for(int i=1; i<=16; i++){ 
            if(i == 1 || i == 2 || i==9 || i==16 ){ // for this round shift once
                C.at(i) = shift_once(C.at(i-1)); 
                D.at(i) = shift_once(D.at(i-1));
            } 
            else{// for other rounds shift twice
                C.at(i) = shift_twice(C.at(i-1)); 
                D.at(i) = shift_twice(D.at(i-1));
            }

            tmp.insert(tmp.end(), C.at(i).begin(), C.at(i).end());
            tmp.insert(tmp.end(), D.at(i).begin(), D.at(i).end());

            for(int j=0;j<48;++j){
                _roundKeys.at(i-1).push_back( tmp.at(_PC2[j]-1) );
            }
            tmp.clear();
        }
    }
    void DESCoder::add_padding(std::shared_ptr< byteVec > a_data){
        int modulo = a_data->size()%8;
        for(int i=modulo;i<8;++i){
            a_data->push_back( static_cast<byte>(8-modulo) );

        }
    }
    void DESCoder::delete_padding(byteVec &a_data){
        int modulo = a_data.back();
        if(modulo>8){
            return;
        }
        for(int i=0;i<modulo;++i){
            a_data.pop_back();
        }
    }
    std::vector<block> DESCoder::split_message_into_blocks(std::shared_ptr< byteVec > a_data){
        
        std::vector<int> tmp = _convertToBits(a_data);
        std::vector<block> messageBlocks;
        messageBlocks.reserve(tmp.size()/BLOCK_SIZE);
        block singleBlock;
        for(unsigned int i =0; i < (tmp.size()/BLOCK_SIZE); ++i){
            for(int j =0; j < BLOCK_SIZE; ++j)
                singleBlock[j] = tmp[i*BLOCK_SIZE+j];
            messageBlocks.push_back(singleBlock);
        }
        return messageBlocks;
    }
    std::vector<int> DESCoder::XOR_tables(std::vector<int> a_A, std::vector<int> a_B, int size){
        std::vector<int> result;
        result.reserve(size);    
        for(int i=0; i<size; ++i)
            result.push_back(a_A.at(i)^a_B.at(i));
        return result;
    }
    std::vector<int> DESCoder::magic_function(std::vector<int> a_bitBlock, int a_key_number){
        int s[8][4][16]=
        {{
            14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
            0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
            4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
            15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
        },
        {
            15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
            3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
            0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
            13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
        },


        {
            10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
            13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
            13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
            1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
        },
        {
            7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
            13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
            10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
            3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
        },
        {
            2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
            14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
            4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
            11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
        },
        {
            12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
            10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
            9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
            4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
        },
        {
            4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
            13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
            1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
            6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
        },
        {
            13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
            1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
            7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
            2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
        }};
        
        std::vector<int> expandedBlock;
        expandedBlock.reserve(48);
        for(int i=0; i<48; ++i){
            expandedBlock.push_back(a_bitBlock.at(_E.at(i)-1));
        }

        std::vector<int> XORResult = XOR_tables(_roundKeys.at(a_key_number), expandedBlock, 48);
        expandedBlock.clear();
        expandedBlock.shrink_to_fit();

        int row, col;
        std::vector<int> SBoxResult;
        for(int i=0; i<8; ++i){
            row = XORResult[i*6]*2 + XORResult[i*6+5];
            col = XORResult[i*6+1]*8 + XORResult[i*6+2]*4 + XORResult[i*6+3]*2 + XORResult[i*6+4];
            SBoxResult.push_back(s[i][row][col]);
        }
        XORResult.clear();
        XORResult.shrink_to_fit();
        std::vector<int> SBoxResultBits;
        for(auto it : SBoxResult){
            std::bitset<4> x(it);
            for(int j=3;j>=0;--j)
                SBoxResultBits.push_back(x[j]);
        }
        SBoxResult.clear();
        SBoxResult.shrink_to_fit();
        std::vector<int> permutedSBoxResult;
        for(int i=0; i<32; ++i)
            permutedSBoxResult.push_back(SBoxResultBits[_P[i]-1]);
        SBoxResultBits.clear();
        SBoxResultBits.shrink_to_fit();
        return permutedSBoxResult;
    }
    byteVec DESCoder::des(const std::shared_ptr< byteVec > a_key, const std::shared_ptr< byteVec > a_data){
        generate_keys(a_key);
        byteVec cipher;
        std::vector<block> messageBlocks = split_message_into_blocks(a_data);
        
        std::vector<block> encryptedBlocks;
        encryptedBlocks.reserve(messageBlocks.size());
        block singleBlock;
        for(auto it : messageBlocks){
            for(int i=0;i<BLOCK_SIZE;++i){
                singleBlock.at(i) = it.at(_IP[i]-1);
            }
            std::array<std::vector<int>, 17> L;
            std::array<std::vector<int>, 17> R;
            L[0].insert(L[0].end(), singleBlock.begin(), singleBlock.begin()+32);
            R[0].insert(R[0].end(), singleBlock.begin()+32, singleBlock.end());
                                    
            for(int i=1; i<=16; ++i){
                L.at(i) = R.at(i-1);
                R.at(i) = XOR_tables(L.at(i-1), magic_function(R.at(i-1), i-1));
            }
            std::vector<int> RL;
            RL.assign(R[16].begin(), R[16].end());
            RL.insert(RL.end(), L[16].begin(), L[16].end());
            
//            std::cout<<"RL: \t\t";
//            for_each(RL.begin(), RL.end(), [](int x){std::cout<<x;});
//            std::cout<<std::endl;
            
            block permutationRL;
            for(unsigned int i=0; i<RL.size(); ++i){
                permutationRL[i] = RL.at(_IP1[i]-1);
            }
            encryptedBlocks.push_back(permutationRL);
            
        }
        std::bitset<8> bits;
        for(auto it : encryptedBlocks){
            for(int i=0;i<8;++i){
                for(int j=0;j<8;++j){
                    bits.set(7-j,it.at(i*8+j));
                }
                cipher.push_back(static_cast<byte>(bits.to_ulong()));
                bits.reset();
            }
        }
        
        return cipher;
    }
    void DESCoder::reverse_RoundKeys(){
        std::reverse(_roundKeys.begin(),_roundKeys.end());
    }
    byteVec DESCoder::decrypt(std::shared_ptr< byteVec > a_key, std::shared_ptr< byteVec > a_data){
        reverse_RoundKeys();
//        int sizeOfData = a_data->size();
        int amountOfPackages = a_data->size() / PACKAGE_SIZE;
        ++amountOfPackages;     // rest of divide
        for(int i=0; i<amountOfPackages; ++i){
            // TODO : Threads
        }
        byteVec result = des(a_key, a_data);
        delete_padding(result);
        return result;
    }
        byteVec DESCoder::encrypt(const std::shared_ptr< byteVec > a_key, const std::shared_ptr< byteVec > a_data){
        add_padding(a_data);
        
        return des(a_key, a_data);
    }
    
}//DES