// #include <x/types.h>

// #include <time.h>
// #include <stdlib.h>

// #include "x/_log.h"
// #include "x/_types.h"

// #define xdefault_check_total    16

// int main(int argc, char ** argv)
// {
//     srandom(time(xnil));

//     check_log_all(random() % xdefault_check_total);
//     check_types_all(random() % xdefault_check_total);

//     return 0;
// }

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <x/std.h>

#include "x/_std.h"

int main(int argc, char ** argv)
{
    srandom(time(xnil));

    // fprintf(stdout, "check xobjval => %s\n", check_xobjval(random() % 16) ? "ok" : "fail");
    // fprintf(stdout, "check xfun => %s\n", check_xfun(random() % 16) ? "ok" : "fail");
    
    return 0;
}
