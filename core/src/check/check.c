#include <x/types.h>

#include <time.h>
#include <stdlib.h>

#include "x/_log.h"

#define xdefault_check_total    16

int main(int argc, char ** argv)
{
    srandom(time(xnil));

    check_log_all(random() % xdefault_check_total);
    return 0;
}