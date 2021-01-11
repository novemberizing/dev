/**
 * @file    x/std.h
 * @brief   표준 라이브러리의 헤더파일입니다.
 * @details
 * 
 * @version 0.0.1
 * @date    2021. 01. 11.
 */
#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

/** COMMON *****************************************/

#define xsuccess            0
#define xfail               -1
#define xtrue               1
#define xfalse              0
#define xinvalid            -1
#define xnil                (void *)(0)

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;


/** LOG ********************************************/

#define xassertion(condition, format, ...) do {     \
    if(condition) {                                 \
        dprintf(xlogfd(), "[assertion] "            \
        "%s:%d "                                    \
        "%s:%lu => "                                \
        format "\n",                                \
        __FILE__, __LINE__,                         \
        __func__, xthreadid(),                      \
        ##__VA_ARGS__);                             \
    }                                               \
} while(0)

/** DATA STRUCTUE **********************************/

struct xlist
{
};

#endif // __NOVEMBERIZING_X__STD__H__
