#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>
namespace MYTYPES{
    struct PUBKEY{
        unsigned long int e;
        unsigned long int n;
    };
}// MYTYPES
namespace RETURN_VALUES{

const uint32_t SUCCESS = 0x0000;
const uint32_t E_UNKNOW = 0x0001;
const uint32_t E_INVALID_LENGTH = 0x0002;
const uint32_t E_ = 0x0003;

}// RETURN_VALUES

#endif /* TYPES_H */

