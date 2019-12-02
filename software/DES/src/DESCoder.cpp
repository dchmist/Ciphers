#include "DESCoder.h"
#include <bitset>
#include <iostream>
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
    
    uint32_t DESCoder::encrypt(std::vector<int> &data){
        int SBoxes[8][4][16]=  
	{
            { 
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
            }
        };
        std::vector<int> perm; 
	for(int i = 0; i < 64; i++){ 
		perm.push_back(data[_IP[i]]); 
	}  
	std::vector<int> leftHalf; 
	std::vector<int> rigthHalf;
        leftHalf.insert(leftHalf.end(),perm.begin(),perm.begin()+32);
        rigthHalf.insert(rigthHalf.end(),perm.begin()+32,perm.end());
        
        
        
	// The plain text is encrypted 16 times  
	for(int i=0; i<16; i++) { 
            std::vector<int> rightExpanded; 
		// 3.1. The right half of the plain text is expanded
            for(int i = 0; i < 48; i++) { 
      		rightExpanded.push_back(rigthHalf[_E[i]]); 
            };
            
            std::vector<int> xored = xorVector(_roundKeys[i], rightExpanded);  
            std::vector<int> res; 
            for(int i=0;i<8; i++){

                int row = xored[i*6] + xored[i*6 + 5];
                int col = xored[i*6 + 1] + xored[i*6 + 2] + xored[i*6 + 3] + xored[i*6 + 4];
                
                int val = SBoxes[i][row][col];
                std::bitset<8> singleByte(val);
                for(int j=7;j>=0;--j)
                    res.push_back(singleByte[j]);
            } 
            // 3.5. Another permutation is applied
            std::vector<int> perm2; 
            for(int i = 0; i < 32; i++){ 
                    perm2.push_back(res[_P[i]-1]); 
            }
            // 3.6. The result is xored with the left half
            xored = xorVector(perm2, leftHalf);
            // 3.7. The left and the right parts of the plain text are swapped 
            leftHalf = xored;
            std::vector<int> temp;
            if(i < 15){ 
                    temp = rigthHalf;
                    rigthHalf = xored;
                    leftHalf = temp;
            } 
	} 
	// 4. The halves of the plain text are applied
        std::vector<int> combined_text;
        combined_text.insert(combined_text.end(), leftHalf.begin(),leftHalf.end());
        combined_text.insert(combined_text.end(), rigthHalf.begin(),rigthHalf.end());
	std::vector<int> ciphertext; 
	// The inverse of the initial permuttaion is applied
	for(int i = 0; i < 64; i++){ 
		ciphertext.push_back(combined_text[_IP1[i]-1]); 
	}
        data.clear();
        data.insert(data.end(), ciphertext.begin(), ciphertext.end());
        
        return RETURN_VALUES::SUCCESS;
    }
    
    
    uint32_t DESCoder::decrypt(std::vector<int>){
        
        return RETURN_VALUES::SUCCESS;
    }
    void DESCoder::setKey(std::vector<int> a_key){
        if(a_key.size()!=64){
            std::cout<<"Incorrect length of key. You need 64bits key\n";
            exit(1);
        }
        generateRoundKeys(a_key);
    }
    void DESCoder::setKey(std::vector<uint8_t> a_key){
        if(a_key.size()!=8){
            std::cout<<"Incorrect length of key. You need 8bytes key\n";
            exit(1);
        }
        std::vector<int> my_key;
        for(int i=0;i<8;++i){
            std::bitset<8> singleByte(a_key[i]);
            for(int j=7;j>=0;--j)
                my_key.push_back(singleByte[j]);
        }
        generateRoundKeys(my_key);
    }
    
    //private
    std::vector<int> xorVector(std::vector<int> vec1, std::vector<int> vec2){
        std::vector<int> result;
        result.resize(vec1.size());
        for(int i=0;i<vec1.size();++i)
            result[i] = vec1[i]^vec2[i];
        return result;
    }
    void DESCoder::generateRoundKeys(std::vector<int> a_key){
        
        // initialize tables
        
        
        std::vector<int> permutationKey;
        permutationKey.resize(56);
        for (int i =0; i<56; ++i){
            permutationKey.push_back(a_key[_PC1[i]]);
        }
        std::vector<int> C0;
        std::vector<int> D0;
        C0.insert(C0.begin(), permutationKey.begin(), permutationKey.begin()+28);
        D0.insert(D0.begin(), permutationKey.begin()+28, permutationKey.end());
        for(int i=1; i<=16; i++){ 
            if(i == 1 || i == 2 || i==9 || i==16 ){ // for this round shift once
                    C0= shift_once(C0); 
                    D0= shift_once(D0);
            } 
            else{   // for other rounds shift twice
                    C0= shift_twice(C0); 
                    D0= shift_twice(D0);
            }
	std::vector<int> mixedKey;
        mixedKey.insert(mixedKey.end(), C0.begin(), C0.end());
        mixedKey.insert(mixedKey.end(), D0.begin(), D0.end());
        
        std::vector<int> round_key;
        round_key.resize(48);
	for(int i = 0; i < 48; i++){ 
		round_key.push_back(mixedKey[_PC2[i]]); 
	}   
	_roundKeys.insert(std::pair<int,std::vector<int>>(i, round_key));
	}
    }
    std::vector<int> DESCoder::shift_once(std::vector<int> a_halfOfKey){
        std::vector<int> shifted;
        shifted.resize(32);
        for(unsigned int i=0; i<a_halfOfKey.size() ;++i)
            shifted.push_back(a_halfOfKey[i]);
        return shifted;
    }
    std::vector<int> DESCoder::shift_twice(std::vector<int> a_halfOfKey){
        std::vector<int> shifted_once = shift_once(a_halfOfKey);
        return shift_once(shifted_once);
    }
}// DES
