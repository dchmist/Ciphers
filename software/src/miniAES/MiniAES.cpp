#include <iostream>

#include "MyAES.h"
//TODO Dokonczyc 
namespace AES{

    MyAES::MyAES() {
        _secretKey.clear();
    }

    MyAES::MyAES(const MyAES& orig) {
    }

    MyAES::~MyAES() {
    }
    
    Result MyAES::setSecretKey(const ByteArray* a_key){
        _secretKey.clear();
        int length_of_key = a_key->size();
        switch(length_of_key){
            case(16):
                _aesType = AES_128;
                break;
            case(24):
                _aesType = AES_192;
                break;
            case(32):
                _aesType = AES_256;
                break;
            default:
                return RETURN_VALUES::E_INVALID_LENGTH;
        }
        _secretKey.insert(_secretKey.end(), a_key->begin(),a_key->end());
        return RETURN_VALUES::SUCCESS;
    }
    
    Result MyAES::ecryptText(const ByteArray* a_publicText){
        
    }
    Result MyAES::decryptText(const ByteArray* a_encryptedText){
        
    }
    
    //private
    void MyAES::generate_intermediate_keys(){
        if(_secretKey.size()==0){
            std::cerr<<"Invalid length of secretKey\n";
            return;
        }
        int i=0, j=0;
        Byte tmp;
        uint32_t previousKey;
        for(i=0; i<8; ++i)
            for(j=0;j<4;++j)
                _intermediateKeys[i][j] = _secretKey[j+4*i];
        for(i=8; i<60; ++i){
            previousKey = (static_cast<uint32_t>(_intermediateKeys[i-1][0])<<24) + (static_cast<uint32_t>(_intermediateKeys[i-1][1])<<16 ) + (static_cast<uint32_t>(_intermediateKeys[i-1][2])<<8 ) + static_cast<uint32_t>(_intermediateKeys[i-1][3]);
            if(previousKey%8==0){
                //przesuniecie bitów << 8 cyklicznie
                tmp                       = _intermediateKeys[i-1][0];
                _intermediateKeys[i-1][0] = _intermediateKeys[i-1][1];
                _intermediateKeys[i-1][1] = _intermediateKeys[i-1][2];
                _intermediateKeys[i-1][3] = tmp;
                        
            }
        }
    }
}