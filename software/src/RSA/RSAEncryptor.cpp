#include "RSAEncryptor.h"
namespace RSA{
    RSAEncryptor::RSAEncryptor() {
    }

    RSAEncryptor::RSAEncryptor(const RSAEncryptor& orig) {
    }

    RSAEncryptor::~RSAEncryptor() {
    }
    uint32_t RSAEncryptor::encrypt(std::vector<l_int> &a_publicData){
        l_int singleChar, k;
        std::vector<l_int> encrypted_message;
        for(auto it : a_publicData){
            singleChar = it;
            singleChar = singleChar - 96;
            k = 1;
            for (l_int j = 0; j < _e; j++){
                k *= singleChar;
                k %= _n;
            }
            encrypted_message.push_back(k);
        }
        a_publicData.clear();
        a_publicData.insert(a_publicData.end(), encrypted_message.begin(), encrypted_message.end());
        
        return RETURN_VALUES::SUCCESS;
    }
    uint32_t RSAEncryptor::setKey(MYTYPES::PUBKEY a_key){
        _e = a_key.e;
        _n = a_key.n;
        return RETURN_VALUES::SUCCESS;
    }
}// RSA