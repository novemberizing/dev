#ifndef   __NOVEMBERIZING_X__NET__H__
#define   __NOVEMBERIZING_X__NET__H__

#include <x/std.h>

struct xeventengine;

struct xclient;
struct xsession;
struct xserver;

typedef struct xeventengine xeventengine;

extern xeventengine * xeventengine_new(void);
extern void *         xeventengine_rem(void * pointer);

/**
 * xclient_new()
 * xclient_rem(...)
 */

// #define xevent_descriptor_type      (0x01000000U)

// struct xeventgenerator;

// typedef struct xeventgenerator xeventgenerator;

// extern xeventgenerator * xeventgenerator_io_new(void);
// extern void * xeventgenerator_io_rem(void * pointer);

#endif // __NOVEMBERIZING_X__NET__H__
