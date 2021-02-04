#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

#define xnil                ((void *) 0)
#define xfail               (-1)
#define xsuccess            (0)
#define xinvalid            (-1)
#define xtrue               (1)
#define xfalse              (0)

#define xaddressof(o)       (&(o))

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

    void *    (*front)(xstream *);
    void *    (*back)(xstream *);
    xuint64   (*size)(xstream *);
    xuint64   (*remain)(xstream *);
    void      (*recapacity)(xstream *, xuint64);
    void      (*push)(xstream *, const void *, xuint64);
    xuint64   (*pop)(xstream *, void *, xuint64);
};

extern xstream * xstream_new(xuint64 capacity);
extern xstream * xstream_rem(xstream * stream);

#define xstream_front(stream)               (stream ? stream->front(stream) : 0)
#define xstream_back(stream)                (stream ? stream->back(stream) : 0)
#define xstream_size(stream)                (stream ? stream->size(stream) : 0)
#define xstream_remain(stream)              (stream ? stream->remain(stream) : 0)
#define xstream_push(stream, data, len) do {    \
    if(stream) {                                \
        stream->push(stream, data, len);        \
    }                                           \
} while(0)

#define xstream_pop(stream, buffer, size)   (stream ? stream->pop(stream, buffer, size) : 0)

#define xstream_recapacity(stream, v) do {      \
    if(stream){                                 \
        stream->recapacity(stream, v);          \
    }                                           \
} while(0)

struct xsync;
typedef struct xsync xsync;

#endif // __NOVEMBERIZING_X__STD__H__
