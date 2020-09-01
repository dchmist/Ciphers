#include "RSADecryptor.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <string.h>
#include <cmath>
namespace RSA{
    RSADecryptor::RSADecryptor() {
        generateKeys();
        
    }
    
    RSADecryptor::RSADecryptor(const RSADecryptor& orig) {
    }

    RSADecryptor::~RSADecryptor() {
    }
    //public
    uint32_t RSADecryptor::decrypt(std::vector<l_int> &a_encryptedData){
        
        l_int  singleChar, privkey = _d[_keyNumber], k;
        std::vector<l_int> decrypted_message;
        for(auto it : a_encryptedData){
            singleChar = it;
            k = 1;
            for (l_int j = 0; j < privkey; j++){
                k *= singleChar;
                k %= _n;
            }
            singleChar = k + 96;
            decrypted_message.push_back(singleChar);
        }
        a_encryptedData.clear();
        a_encryptedData.insert(a_encryptedData.end(), decrypted_message.begin(), decrypted_message.end());
        
        
        return RETURN_VALUES::SUCCESS;
    }
    MYTYPES::PUBKEY RSADecryptor::getPublicKey(){
        MYTYPES::PUBKEY key;
        key.e = _e[_keyNumber];
        key.n = _n;
        return key;
    }
    //private
    bool RSADecryptor::isPrime(l_int a_var){
        if(a_var < 2) 
            return false; 
        for(unsigned int i = 2; i < a_var; i++) 
            if (a_var % i == 0) 
                return false; 
        return true; 
    }
    void RSADecryptor::computeEandD(l_int a_p, l_int a_q){
        l_int counter = 0,result = 0;
        
        auto l_computeD = [&](l_int x){
            l_int tmp = 1;
            while (1){
                tmp += _phi;
                if (tmp % x == 0)
                    return (tmp / x);
            }
        };
        for (l_int i = 2; i < _phi; i++){
            if (_phi % i == 0)
                continue;
            if (isPrime(i) == 1 && i != a_p && i != a_q){
                _e.push_back(i);
                result = l_computeD(_e[counter]);
                if (result > 0){
                    _d.push_back(result);
                    counter++;
                }else
                    _e.pop_back();
                // i want a 50 key pairs
                if (counter == 50)
                    break;
            }
        }
    }
    uint32_t RSADecryptor::generateKeys(){
        l_int firstPN, secondPN, result;
        //random engine
        std::random_device rand; 
        std::mt19937 engine(rand());
        std::uniform_int_distribution<l_int> distribution(10, 500);
        
        result = distribution(engine);
        while (!isPrime (result))
            result = distribution(engine);
        firstPN = result;
        
        result = distribution (engine);
        while (!isPrime (result))
            result = distribution(engine);
        secondPN = result;
        
        _n = firstPN * secondPN;
        _phi = (firstPN-1) * (secondPN-1);
        computeEandD(firstPN, secondPN);
        _keyNumber = (distribution(engine)) % _d.size();
        
        return RETURN_VALUES::SUCCESS;
    }
} // RSA