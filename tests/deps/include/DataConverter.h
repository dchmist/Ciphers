#ifndef DATA_CONVERTER_H
#define DATA_CONVERTER_H

#include <cstdint>
#include <vector>
#include <string>

class DataConverter{
public:
    static std::vector<uint8_t> toBytes(const std::string&);
    static std::vector<uint8_t> toBytes(const char* , size_t);
    static std::string toString(const std::vector<uint8_t>&);
};
#endif