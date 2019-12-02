#include <iostream>
//#include "MyAES.h"
#include "Caesar.h"
#include "RSADecryptor.h"
#include "RSAEncryptor.h"
#include <vector>
#include <string>
#include <algorithm>
#include <deque>


void func_Caesar(){
    std::string myStr= "This is Lorem Ipsum Caesar";
    std::vector<uint8_t> data;
    for_each(myStr.begin(),myStr.end(), [&data](char x){data.push_back(static_cast<uint8_t>(x));});
    CaesarCipher::Caesar CeasarObj;
    CeasarObj.encrypt(data);
    std::cout<<"After encryption\n";
    for_each(data.begin(),data.end(), [](uint8_t x){std::cout<<x<<" ";});
    CeasarObj.decrypt(data);
    std::cout<<"\nAfter decryption\n";
    for_each(data.begin(),data.end(), [](uint8_t x){std::cout<<x<<" ";});
}
void func_RSA(){
    std::string myStr= "This is Lorem Ipsum RSA";
    std::vector<long int> data;
    for_each(myStr.begin(),myStr.end(), [&data](char x){data.push_back(static_cast<long int>(x));});
    RSA::RSAEncryptor objEnc;
    RSA::RSADecryptor objDec;
    decltype(objDec.getPublicKey()) key = objDec.getPublicKey();
    objEnc.setKey(key);
    objEnc.encrypt(data);
    objDec.decrypt(data);
    std::cout<<"Decrypted: ";
    for_each(data.begin(), data.end(), [](long int x){std::cout<<static_cast<char>(x);});
    std::cout<<std::endl;
}

int main(int argc, char *argv[]){
    
    func_RSA();
    
    return 0;
}