#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <novemberizing/ds/xlist.h>
#include <novemberizing/ds/xmap.h>

static void print(variant v)
{
    // fprintf(stdout, "%lu ", v.u64);
}

int check_xlistnew()
{
    int result = false;
    xlist * o = xlistnew();
    if(o)
    {
        o = xlistrem(o, NULL);
        if(o == NULL)
        {
            result = true;
        }
    }
    return result;
}

int check_xlistclr()
{
    int result = false;
    xlist * o = xlistnew();
    if(o)
    {
        long int n = (random() % 64);
        for(int i = 0; i < n; i++)
        {
            xlistpush(o, vargen(random() % 64));
        }
        n = (random() % 64);
        for(int i = 0; i < n; i++)
        {
            xlistpop(o, print);
        }
        xlistclr(o, print);
        o = xlistrem(o, NULL);
        if(o == NULL)
        {
            result = true;
        }
    }
    return result;
}

int check_xmapnew()
{
    int result = false;
    xmap * o = xmapnew();

    if(o)
    {
        xmapadd(o, vargen(30), NULL);
        xmapadd(o, vargen(33), NULL);
        xmapadd(o, vargen(13), NULL);
        xmapadd(o, vargen(57), NULL);
        xmapadd(o, vargen(57), NULL);
        xmapadd(o, vargen(18), NULL);
        xmapadd(o, vargen(12), NULL);
        xmapadd(o, vargen(33), NULL);
        xmapadd(o, vargen(2), NULL);
        xmapadd(o, vargen(14), NULL);
        xmapadd(o, vargen(35), NULL);
        xmapadd(o, vargen(21), NULL);
        xmapadd(o, vargen(3), NULL);
        xmapadd(o, vargen(26), NULL);
        xmapadd(o, vargen(9), NULL);
        xmapadd(o, vargen(53), NULL);
        xmapadd(o, vargen(48), NULL);
        xmapadd(o, vargen(61), NULL);
        xmapadd(o, vargen(50), NULL);
        xmapadd(o, vargen(24), NULL);
        xmapadd(o, vargen(20), NULL);
        xmapadd(o, vargen(53), NULL);

        xmapdel(o, vargen(12), NULL);
        xmapdel(o, vargen(13), NULL);
        xmapdel(o, vargen(9), NULL);
        xmapdel(o, vargen(3), NULL);

        fprintf(stdout, "hello world\n");
// 13 : 15

        xmapadd(o, vargen(30), NULL);
        xmapadd(o, vargen(33), NULL);
        xmapadd(o, vargen(13), NULL);
        xmapadd(o, vargen(57), NULL);
        xuint64 n = random() % 65536;
        for(xint32 i = 0; i < n; i++)
        {
            xmapadd(o, vargen(random() % (65536/2)), NULL);
        }
        xmapfor(o, print);
        n = random() % 65536;
        for(xint64 i = 0; i < n; i++)
        {
            variant v = vargen(random() % (65536/2));
            xmapnode * node = xmapget(o, v);
            if(node)
            {
                if(node->value.u64 != v.u64)
                {
                    fprintf(stdout, "found value is not same\n");
                    abort();
                }
                // fprintf(stdout, "found ==========================>\n");
            }
        }
        printf("\n");
        int total = o->size;
        int count = 0;
        n = random() % 65536;
        for(xint64 i = 0; i < n; i++)
        {
            variant v = vargen(random() % (65536/2));
            xmapnode * found = xmapget(o, v);
            if(found)
            {
                xmapdel(o, v, print);
                count = count + 1;
            }
        }
        if(total - count != o->size)
        {
            fprintf(stdout, "fail to xmapdel()\n");
            abort();
        }
        o = xmaprem(o, print);
        printf("\n");
        if(o == NULL)
        {
            result = true;
        }
    }

    return result;
}

int main(int argc, char ** argv)
{
    srandom(time(NULL));
    printf("check xlistnew() => %s\n", check_xlistnew() ? "ok" : "fail");
    printf("check xlistclr() => %s\n", check_xlistclr() ? "ok" : "fail");
    for(int i = 0; i < 256; i++)
    {
        printf("check xmapnew() => %s\n", check_xmapnew() ? "ok" : "fail");
    }
    
    
    return 0;
}