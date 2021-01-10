/**
 * @file    x/std.h
 * @brief   standard library include file.
 * @details - log
 *          - data structure
 *          - thread & synchronization
 * 
 */
#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

typedef __INT8_TYPE__   xint8;
typedef __INT16_TYPE__  xint16;
typedef __INT32_TYPE__  xint32;
typedef __INT64_TYPE__  xint64;
typedef __UINT8_TYPE__  xuint8;
typedef __UINT16_TYPE__ xuint16;
typedef __UINT32_TYPE__ xuint32;
typedef __UINT64_TYPE__ xuint64;

#define xassertion(condition, format, ...)  do {    \
    if(condition) {                                 \
                                                    \
    }                                               \
} while(0)


#endif // __NOVEMBERIZING_X__STD__H__
