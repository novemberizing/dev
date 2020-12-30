#ifndef   __X__TYPE__HH__
#define   __X__TYPE__HH__

#include <x/core.hh>

namespace x
{
    typedef __INT8_TYPE__       int8;
    typedef __INT16_TYPE__      int16;
    typedef __INT32_TYPE__      int32;
    typedef __INT64_TYPE__      int64;
    typedef __UINT8_TYPE__      uint8;
    typedef __UINT16_TYPE__     uint16;
    typedef __UINT32_TYPE__     uint32;
    typedef __UINT64_TYPE__     uint64;
    typedef float               float32;
    typedef double              float64;
    typedef unsigned char       byte;
    typedef bool                boolean;

    const int32 invalid = -1;
    const int32 success = 0;
    const int32 fail = -1;
}

#endif // __X__TYPE__HH__
