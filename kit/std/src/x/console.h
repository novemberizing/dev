#ifndef   __NOVEMBERIZING_X__CONSOLE__H__
#define   __NOVEMBERIZING_X__CONSOLE__H__

#include <x/std.h>
#include <x/descriptor.h>

struct xconsole;
struct xconsoledescriptor;
struct xconsoledescriptorevent;

typedef struct xconsole xconsole;
typedef struct xconsoledescriptor xconsoledescriptor;
typedef struct xconsoledescriptorevent xconsoledescriptorevent;

typedef xint64 (*xconsolesubscriber)(xconsole *, xuint64, void *, xint64);

struct xconsole
{
    xconsoledescriptor * in;
    xconsoledescriptor * out;
    xconsolesubscriber   on;
    
};

extern xdescriptor * xconsoledescriptorin_get(void);
extern xdescriptor * xconsoledescriptorout_get(void);

#endif // __NOVEMBERIZING_X__CONSOLE__H__
