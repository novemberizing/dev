#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "std.h"

struct xsimplestream
{
    xstream * (*destruct)(xstream *);

    void *    (*front)(xstream *);
    void *    (*back)(xstream *);
    xuint64   (*size)(xstream *);
    xuint64   (*remain)(xstream *);
    void      (*recapacity)(xstream *);
    void      (*push)(xstream *, const void *, xuint64);
    xuint64   (*pop)(xstream *, void *, xuint64);

    xbyte *   buffer;
    xuint64   pos;
    xuint64   last;
    xuint64   capacity;
};

static xstream * xsimplestream_destructor(xstream * stream);
static void *    xsimplestream_front(xstream * stream);
static void *    xsimplestream_back(xstream * stream);
static xuint64   xsimplestream_size(xstream * stream);
static xuint64   xsimplestream_remain(xstream * stream);
static void      xsimplestream_recapacity(xstream * stream, xuint64 capacity);
static void      xsimplestream_push(xstream * stream, const void * data, xuint64 len);
static xuint64   xsimplestream_pop(xstream * stream, void * buffer, xuint64 size);

typedef struct xsimplestream xsimplestream;

static const xuint64 xsimplestream_page = 64;

extern xstream * xstream_new(xuint64 capacity)
{
    xsimplestream * stream = (xsimplestream *) calloc(sizeof(xsimplestream), 1);

    xassertion(stream == xnil, "fail to calloc (%d)", errno);

    stream->capacity = (capacity/xsimplestream_page + 1) * xsimplestream_page;
    stream->buffer   = malloc(stream->capacity);

    xassertion(stream->buffer == xnil, "fail to malloc (%d)", errno);

    stream->destruct   = xsimplestream_destructor;

    stream->front      = xsimplestream_front;
    stream->back       = xsimplestream_back;
    stream->size       = xsimplestream_size;
    stream->remain     = xsimplestream_remain;
    stream->recapacity = xsimplestream_recapacity;
    stream->push       = xsimplestream_push;
    stream->pop        = xsimplestream_pop;

    return stream;
}

extern xstream * xstream_rem(xstream * stream)
{
    if(stream)
    {
        stream = stream->destruct(stream);
    }
    return stream;
}

static xstream * xsimplestream_destructor(xstream * o)
{
    xsimplestream * stream = (xsimplestream *) o;
    if(stream)
    {
        if(stream->buffer)
        {
            free(stream->buffer);
        }
        free(stream);
        stream = xnil;
    }
    return stream;
}

static void *    xsimplestream_front(xstream * o)
{
    xsimplestream * stream = (xsimplestream *) o;

    return (stream && stream->buffer) ? xaddressof(stream->buffer[stream->pos]) : xnil;
}

static void *    xsimplestream_back(xstream * o)
{
    xsimplestream * stream = (xsimplestream *) o;

    return (stream && stream->buffer) ? xaddressof(stream->buffer[stream->last]) : xnil;
}

static xuint64   xsimplestream_size(xstream * o)
{
    xsimplestream * stream = (xsimplestream *) o;

    return (stream && stream->buffer) ? stream->last - stream->pos : 0;
}

static xuint64   xsimplestream_remain(xstream * o)
{
    xsimplestream * stream = (xsimplestream *) o;

    return (stream && stream->buffer) ? stream->capacity - stream->last : 0;
}

static void      xsimplestream_recapacity(xstream * o, xuint64 capacity)
{
    xsimplestream * stream = (xsimplestream *) o;

    xassertion(stream == xnil, "stream is null");

    capacity = ((stream->last + capacity) / xsimplestream_page + 1) * xsimplestream_page;

    xassertion(capacity < stream->last, "capacity is small");

    stream->capacity = capacity;

    if(stream->buffer)
    {
        stream->buffer = realloc(stream->buffer, capacity);
    }
    else
    {
        stream->buffer = malloc(capacity);
    }
}

static void      xsimepestream_push(xstream * o, const void * data, xuint64 len)
{
    xsimplestream * stream = (xsimplestream *) o;

    xassertion(stream == xnil, "stream is null");

    if(len)
    {
        if(data)
        {
            if((stream->capacity - stream->last) < len)
            {
                stream->capacity = ((stream->last + len) / xsimplestream_page + 1) * xsimplestream_page;
                if(stream->buffer)
                {
                    stream->buffer = realloc(stream->buffer, stream->capacity);
                }
                else
                {
                    stream->buffer = malloc(stream->capacity);
                }
            }
            memcpy(xaddressof(stream->buffer[stream->last]), data, len);
            stream->last = stream->last + len;
        }
        else
        {
            xassertion((stream->capacity - stream->last) < len, "critical");
            stream->last = stream->last + len;
        }
    }
}

static xuint64 xsimplestream_pop(xstream * o, void * buffer, xuint64 size)
{
    xsimplestream * stream = (xsimplestream *) o;

    xassertion(stream == xnil, "stream is null");

    if(size)
    {
        if((stream->last - stream->pos) < size)
        {
            size = (stream->last - stream->pos);
        }

        if(buffer)
        {
            memcpy(buffer, xaddressof(stream->buffer[stream->pos]), size);
        }

        if(stream->last - stream->pos - size > 0)
        {
            memmove(xaddressof(stream->buffer[stream->pos]),
                    xaddressof(stream->buffer[stream->pos + size]),
                    stream->last - stream->pos - size);
        }
        stream->last = stream->last - size;
        if(stream->last == 0)
        {
            stream->capacity = xsimplestream_page;
            if(stream->buffer)
            {
                stream->buffer = realloc(stream->buffer, stream->capacity);
            }
            else
            {
                stream->buffer = malloc(stream->capacity);
            }
        }
    }

    return size;
}
