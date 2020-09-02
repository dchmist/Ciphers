#include <iostream>
#include <string>
#include "DES/DES.h"

int main(int argc, char *argv[]){
    DESCipher::DES obj(std::bitset<10>{std::string("1100000011")});
    return 0;
}