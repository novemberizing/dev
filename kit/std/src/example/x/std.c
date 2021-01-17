#include <stdio.h>

#include <x/std.h>

static void check_primitive_impl(xint64 total)
{
    for(xint64 i = 0; i < total; i++)
    {
        xprimitive local = xprimitiveinit(xvalgen(xrandomgen()));
        xprimitiverem(&local);
        xprimitive * o = xprimitivenew(xvalgen(xrandomgen()));
        xprimitiverem(o);
    }
}

int main(int argc, char ** argv)
{
    xrandomon();

    check_primitive_impl(xrandomgen() % 64);

    return 0;
}
