#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <x/log.h>
#include <x/list.h>

#define xdefault_check_size 1024
#define xdefault_check_add  65536
#define xdefault_check_del  32768

static int check_list(int total)
{
    total = (total <= 0 ? 1 : total);

    xuint32 n;
    for(int i = 0; i < total; i++)
    {
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
            if(o->size > 0)
            {
                xval v = xlistpop(o);
            }
        }

        o = xlistrem(o, NULL);
        assertion(o != NULL, "fail to check xlistrem(...) return not null");
    }
    return total;
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
    
    total = random() % xdefault_check_size;
    fprintf(stdout, "check list(%d) => %s", total, check_list(total) ? "ok" : "fail");

    return 0;
}
