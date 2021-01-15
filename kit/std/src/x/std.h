#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

#define xsuccess        (0)
#define xfail           (-1)
#define xinvalid        (-1)
#define xtrue           (1)
#define xfalse          (0)
#define xnil            ((void *) 0)

typedef __INT8_TYPE__   xint8;
typedef __INT16_TYPE__  xint16;
typedef __INT32_TYPE__  xint32;
typedef __INT64_TYPE__  xint64;
typedef __UINT8_TYPE__  xuint8;
typedef __UINT16_TYPE__ xuint16;
typedef __UINT32_TYPE__ xuint32;
typedef __UINT64_TYPE__ xuint64;
typedef unsigned char   xbyte;

typedef void * (*destructor)(void *);

#endif // __NOVEMBERIZING_X__STD__H__
