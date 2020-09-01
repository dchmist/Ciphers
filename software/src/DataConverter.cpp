#include "DataConverter.h"
#include <algorithm>
#include <iterator>

std::vector<uint8_t> DataConverter::toBytes(const std::string &str)
{
    std::vector<uint8_t> result;
    auto castToByte = [](const char x){return static_cast<uint8_t>(x);};
    std::transform(str.begin(), str.end(), std::insert_iterator< std::vector<uint8_t> >(result, result.begin()), castToByte);
    return result;
}
std::vector<uint8_t> DataConverter::toBytes(const char *data, size_t size)
{
    std::vector<uint8_t> result;
    auto castToByte = [](const char x){return static_cast<uint8_t>(x);};
    std::transform(data, data+size, std::insert_iterator< std::vector<uint8_t> >(result, result.begin()), castToByte);
    return result;
}
std::string DataConverter::toString(const std::vector<uint8_t> &buffer)
{
    std::string str;
    auto castToChar = [](const uint8_t x){return static_cast<char>(x);};
    std::transform(buffer.begin(), buffer.end(), std::insert_iterator< std::string >(str, str.begin()), castToChar);
    return str;
}