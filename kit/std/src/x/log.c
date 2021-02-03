#include <unistd.h>

#include "std.h"

extern int xlogfd(void)
{
    return STDOUT_FILENO;
}