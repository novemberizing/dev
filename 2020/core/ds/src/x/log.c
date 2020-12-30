#include <stdbool.h>
#include <errno.h>

#include "log.h"
#include "types.h"

FILE * __stream = xnil;

void xlogfileset(FILE * f)
{
    xassertion(f == xnil, "f == xnil");
    __stream = f;
}

FILE * xlogfileget(void)
{
    return __stream ? __stream : stdout;
}

static inline int __check_x_log_sample_debug(int o, int i)
{
    xcheck(o, -1, "debug => %d", i);
    return 0;
}

int __check_x_log(int total)
{
    __stream = fopen("/dev/null", "w");

    xassertion(__stream == xnil, "fopen => %d", errno);

    for(int i = 0; i < total; i++)
    {
        xfunction("%s(%d)", __func__, total);
        xcritical("critical => %d", i);
        xerror("error => %d", i);
        xwarning("warning => %d", i);
        xcaution("caution => %d", i);
        xnotice("notice => %d", i);
        xinformation("information => %d", i);
        xdebug("debug => %d", i);
        xassertion(false, "assertion(false) => %d", i);
        // assertion(true, "assertion(true) => %d", i);
        xassertion(__check_x_log_sample_debug(true, i) == 0, "debug => %d", i);
        xassertion(__check_x_log_sample_debug(false, i) == 1, "debug => %d", i);
    }
    fclose(__stream);
    __stream = xnil;

    fprintf(stdout, "check types => ok\n");

    return true;
}
