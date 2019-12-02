#include "Caesar.h"
#include "Types.h"
#include <iostream>
namespace CaesarCipher{
    Caesar::Caesar() {
        _encryptor = [](uint8_t &x){x = (x + 15)%255;};
        _decryptor = [](uint8_t &x){x = (x - 15)%255;};
    }

    Caesar::Caesar(const Caesar& orig) {
    }

    Caesar::~Caesar() {
    }
    uint32_t Caesar::encrypt(std::vector<uint8_t> &a_publicData){
        if(a_publicData.size()==0)
            return RETURN_VALUES::E_INVALID_LENGTH;
        try{
            for_each(a_publicData.begin(), a_publicData.end(), _encryptor);
        }
        catch(const std::exception &e){
            std::cerr<<e.what()<<std::endl;
            return RETURN_VALUES::E_UNKNOW;
        }
        return RETURN_VALUES::SUCCESS;
        
    }
    uint32_t Caesar::decrypt(std::vector<uint8_t> &a_encryptedData){
        if(a_encryptedData.size()==0)
            return RETURN_VALUES::E_INVALID_LENGTH;
        try{
            for_each(a_encryptedData.begin(), a_encryptedData.end(), _decryptor);
        }
        catch(const std::exception &e){
            std::cerr<<e.what()<<std::endl;
            return RETURN_VALUES::E_UNKNOW;
        }
        return RETURN_VALUES::SUCCESS;
    }
    

}// namespace