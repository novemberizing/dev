#include <stdio.h>

#include <x/std.h>

#define xobj_type_buffer        0x0000FFFFU

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
    xlogfd();
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
