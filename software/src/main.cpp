#include <iostream>
#include <string>
#include "DES/DES.h"
#include "DataConverter.h"

int main(int argc, char *argv[]){
    DESCipher::DES obj(std::string("1100000011"));
    auto plainText = DataConverter::toBytes(std::string{"Test"});
    std::vector<uint8_t> encoded = obj.encode(plainText);
    std::cout << "Encoded : " << DataConverter::toString(encoded) << std::endl;
    plainText = obj.decode(encoded);
    std::cout << "Wynik : " << DataConverter::toString(plainText) << std::endl;
    return 0;
}