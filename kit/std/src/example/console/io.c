#include <x/console.h>

int main(int argc, char ** argv)
{
    char s[1024];
    s[0] = 0;

    xconsoleout_string("hello world\n");
    xconsolein_string(s, 1024);
    return 0;
}
