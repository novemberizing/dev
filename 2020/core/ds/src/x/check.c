#include <stdio.h>

#include <x/types.h>
#include <x/log.h>

#define xdefault_check_total    16

int main(int argc, char ** argv)
{
    srandom(time(xnil));

    __check_x_log(random() % xdefault_check_total);

    return 0;
}
