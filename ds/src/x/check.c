#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <x/log.h>
#include <x/list.h>
#include <x/map.h>

#define xdefault_check_size 1024
#define xdefault_check_add  65536
#define xdefault_check_del  32768

static int check_map(int total)
{
    total = (total <= 0 ? 1 : total);

    xuint32 n;
    for(int i = 0; i < total; i++)
    {
        printf("%d/%d\n", i + 1, total);
        xmap * o = xmapnew(NULL);
        assertion(o == NULL, "fail to check xmapnew() return null");
        
        n = random() % xdefault_check_add;
        for(xuint32 i = 0; i < n; i++)
        {
            xmapadd(o, xvalgen(random()), NULL);
        }

        n = random() % xdefault_check_del;
        for(xuint32 i = 0; i < n; i++)
        {
            xmapdel(o, xvalgen(random()), NULL);
        }

        o = xmaprem(o, NULL);
        assertion(o != NULL, "fail to check xmaprem(...) return not null");
    }
    return total;
}

static int check_list(int total)
{
    total = (total <= 0 ? 1 : total);

    xuint32 n;
    for(int i = 0; i < total; i++)
    {
        printf("%d/%d\n", i + 1, total);
        xlist * o = xlistnew();
        assertion(o == NULL, "fail to check xlistnew() return null");
        
        n = random() % xdefault_check_add;
        for(xuint32 i = 0; i < n; i++)
        {
            xlistpush(o, xvalgen(random()));
        }

        n = random() % xdefault_check_del;
        for(xuint32 i = 0; i < n; i++)
        {
            if(!xlistpop(o, NULL))
            {
                break;
            }
        }

        o = xlistrem(o, NULL);
        assertion(o != NULL, "fail to check xlistrem(...) return not null");
    }
    return total;
}

void check_invalid_map_case()
{
    xmap * o = xmapnew(NULL);
    xmapadd(o, xvalgen(5), NULL);
    xmapadd(o, xvalgen(19), NULL);
    xmapadd(o, xvalgen(15), NULL);
    xmaprem(o, NULL);

    o = xmapnew(NULL);
    xmapadd(o, xvalgen(41), NULL);
    xmapadd(o, xvalgen(17), NULL);
    xmapadd(o, xvalgen(21), NULL);
    xmapadd(o, xvalgen(93), NULL);
    xmaprem(o, NULL);
}

int main(int argc, char ** argv)
{
    int total;

    srandom(time(NULL));

    functionLog("%s %s", "hello", "world");
    criticalLog("%s %s", "hello", "world");
    errorLog("%s %s", "hello", "world");
    warningLog("%s %s", "hello", "world");
    cautionLog("%s %s", "hello", "world");
    noticeLog("%s %s", "hello", "world");
    informationLog("%s %s", "hello", "world");
    debugLog("%s %s", "hello", "world");
    assertion(false, "hello world");

    check_invalid_map_case();
    
    total = random() % xdefault_check_size;
    fprintf(stdout, "check list(%d) => %s\n", total, check_list(total) ? "ok" : "fail");
    total = random() % xdefault_check_size;
    total = 16;
    fprintf(stdout, "check map(%d) => %s\n", total, check_map(total) ? "ok" : "fail");

    return 0;
}
