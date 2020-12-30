#ifndef   __NOVEMBERIZING_DS_XTYPE__H__
#define   __NOVEMBERIZING_DS_XTYPE__H__

#if defined __GNUC__ && !defined __GNUC_STDC_INLINE__ && !defined __GNUC_GNU_INLINE__
# define __GNUC_GNU_INLINE__ 1
#endif

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;

typedef char                xchar;
typedef unsigned char       xbyte;

union variant
{
    xuint64 u64;
    xuint32 u32;
    void *  ptr;
};

typedef union variant       variant;

extern variant vargen(xuint64 v);
extern int varcmp(variant x, variant y);

#define fail        -1
#define ok          0

#endif // __NOVEMBERIZING_DS_XTYPE__H__
