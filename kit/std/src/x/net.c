#include <stdlib.h>

#include "./net.h"

struct xeventiogen;
struct xdescriptor;
struct xsocket;

typedef struct xeventiogen xeventiogen;

/**
 * 디스크립터는 
 */
typedef struct xdescriptor xdescriptor;
typedef struct xsocket     xsocket;

struct xdescriptor
{
    xdescriptor * prev;
    xdescriptor * next;
    xeventiogen * generator;
};

struct xeventiogen
{
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;        // 가끔 드는 생각이지만 소켓은 4억개를 넘을 수가 없다.
    } descriptors;
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } queue;
};

struct xeventengine
{
    xeventiogen io;
};

extern xeventengine * xeventengine_new(void)
{
    xeventengine * engine = (xeventengine *) calloc(sizeof(xeventengine), 1);
    
    return (xeventengine * ) engine;
}

extern void *         xeventengine_rem(void * pointer)
{
    if(pointer)
    {
        free(pointer);
    }
    return xnil;
}