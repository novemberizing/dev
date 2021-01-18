#include <stdio.h>

#include <x/std.h>

static void printval(xval v)
{
    printf("%u\n", v.u32);
}

int main(int argc, char ** argv)
{
    xrandomon();
    xlist * o = xlistnew();

    int total = xrandomgen() % 64;
    for(int i = 0; i < total; i++)
    {
        xlistpush(o, xvalgen(xrandomgen() % 128));
    }

    total = xrandomgen() % 32;
    for(int i = 0; i < total; i++)
    {
        xlistpop(o, printval);
    }
    xlistclear(o, printval);
    xlistrem(o);
    return 0;
}
