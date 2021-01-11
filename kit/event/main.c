#include <stdio.h>

#define xinvalid    -1
#define xsuccess    0
#define xfail       -1
#define xtrue       1
#define xfalse      0
#define xnil        (void *)(0)

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;

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

struct xsocket;

typedef struct xsocket xsocket;

struct xsocket
{
    int fd;
};

struct xevent;

typedef struct xevent xevent;

struct xevent
{

};

struct xgenerator;

typedef struct xgenerator xgenerator;

struct xgenerator
{
    xgenerator * next;
};

struct xprocessor;

typedef struct xprocessor xprocessor;

struct xprocessor
{

};

struct xengine;

typedef struct xengine xengine;

#define xengine_status_void         0x00000000U
#define xengine_status_cancel       0x80000000U

extern void xgeneratorrun(xgenerator * o, xengine * engine);
extern xevent * xgeneratoremit(xgenerator * o, xengine * engine);

struct xengine
{
    xuint32 status;
    xgenerator * generators;
};

#define xengineinit()   (xengine) { xengine_status_void }

extern int xenginerun(xengine * o);
extern void xenginedispatch(xengine * o, xevent * event);

int main(int argc, char ** argv)
{
    xengine engine = xengineinit();

    return xenginerun(&engine);
}

int xenginerun(xengine * o)
{
    xassertion(o == xnil, "invalid parameter");
    while((o->status & xengine_status_cancel) == xfalse)
    {
        for(xgenerator * generator = o->generators; generator != xnil; generator = generator->next)
        {
            xgeneratorrun(generator, o);
        }
    }
    return xsuccess;
}

void xgeneratorrun(xgenerator * o, xengine * engine)
{
    xassertion(o == xnil || engine == xnil, "invalid paramter");
    xevent * event = xnil;
    
    while((event = xgeneratoremit(o, engine)) != xnil)
    {
        xenginedispatch(engine, event);
    }
}