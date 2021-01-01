#include "log.h"
#include "types.h"

static FILE * __stream = xnil;
static int __debug = xtrue;

FILE * xlogfobj(void)
{
    return __stream ? __stream : stdout;
}

void xlogfobjset(FILE * fp)
{
    __stream = fp;
}

void xabort(void)
{
    if(__debug) {
        abort();
    }
}

void xabortset(int status)
{
    __debug = status;
}
