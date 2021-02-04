#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

#define xnil                ((void *) 0)
#define xfail               (-1)
#define xsuccess            (0)
#define xinvalid            (-1)
#define xtrue               (1)
#define xfalse              (0)

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;
typedef void *              handle;
typedef unsigned char       xbyte;

extern int xlogfd(void);
extern unsigned long xthreadid(void);

extern void * xdup(const void * source, xuint64 len);
extern void * xfree(void * address);

#define xassertion(condition, format, ...) do {     \
    if(condition) {                                 \
        dprintf(xlogfd(), "[assertion] %s:%d "      \
                          "%s:%lu => "              \
                          format "\n",              \
                          __FILE__,                 \
                          __LINE__,                 \
                          __func__,                 \
                          xthreadid(),              \
                          ##__VA_ARGS__);           \
        exit(xfail);                                \
    }                                               \
} while(0)

#define xcheck(condition, format, ...) do {         \
    if(condition) {                                 \
        dprintf(xlogfd(), "[check] %s:%d "          \
                          "%s:%lu => "              \
                          format "\n",              \
                          __FILE__,                 \
                          __LINE__,                 \
                          __func__,                 \
                          xthreadid(),              \
                          ##__VA_ARGS__);           \
    }                                               \
} while(0)

struct xstream;

typedef struct xstream xstream;

struct xstream
{
    xstream * (*destruct)(xstream *);

    void    * (*front)(xstream *);
    void    * (*back)(xstream *);
};

extern xstream * xstream_new(xuint64 capacity);
extern xstream * xstream_rem(xstream * stream);

struct xsync;
typedef struct xsync xsync;

#endif // __NOVEMBERIZING_X__STD__H__
