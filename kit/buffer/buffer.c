#include <stdio.h>

#define xnil            (void *)(0)

#define xassertion(condition, format, ...) do {     \
    if(condition) {                                 \
        dprintf(xlogfd(), "[assertion] %s:%d "      \
                          "%s:%lu => "              \
                          format "\n",              \
                          __FILE__, __LINE__,       \
                          __func__, xthreadid(),    \
                          ##__VA_ARGS__);           \
    }                                               \
} while(0)

typedef __INT8_TYPE__   xint8;
typedef __INT16_TYPE__  xint16;
typedef __INT32_TYPE__  xint32;
typedef __INT64_TYPE__  xint64;
typedef __UINT8_TYPE__  xuint8;
typedef __UINT16_TYPE__ xuint16;
typedef __UINT32_TYPE__ xuint32;
typedef __UINT64_TYPE__ xuint64;
typedef unsigned char   xbyte;

#define xobj_mask_allocated     0x80000000U

#define xobj_type_buffer        0x00000001U

struct xbuffer;

typedef struct xbuffer xbuffer;

struct xbuffer
{
    xuint32 flags;

    xbyte * data;
    xuint64 position;
    xuint64 size;
    xuint64 capacity;
};


extern xbuffer * xbuffernew(xuint64 capacity);

int main(int argc, char ** argv)
{
    return 0;
}

xbuffer * xbuffernew(xuint64 capacity)
{
    xassertion(capacity == 0, "invalid parameter exception");

    xbuffer * o = (xbuffer *) malloc(sizeof(capacity));
    xassertion(o == xnil, "null pointer exception");

    o->flags = xobj_mask_allocated | xobj_type_buffer;
    o->capacity = capacity;

    return o;
}

void * xbufferrem(void * p)
{
    xbuffer * o = (xbuffer *) p;
    xassertion(o == xnil, "invalid parameter exception");

    if(o->data)
    {
        free(o->data);
        o->data = xnil;
    }
    o->position = 0;
    o->size = 0;
    o->capacity = 0;

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}
