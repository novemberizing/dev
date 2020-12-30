#include "x/_log.h"

#define xdefault_check_total    16

int main(int argc, char ** argv)
{
    check_log_all(random() % xdefault_check_total);
    return 0;
}