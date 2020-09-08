#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#include <cstdint>
enum class ERROR_CODE : int{
    SUCCESS = 0,
    UNKNOW = -1,
    INVALID_KEY_LENGTH = -2,
    INVALID_KEY_FORMAT = -3,
    INVALID_KEY = -3,
    KEY_NOT_INITIALIZED = -4,
    EMPTY_MESSAGE = -5,
};
#endif