#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <x/log.h>
#include <x/list.h>
#include <x/map.h>

#include <x/thread.h>
#include <x/sync.h>

// #define xdefault_check_size 1024
#define xdefault_check_size     32
#define xdefault_check_add      65536
#define xdefault_check_del      32768
#define xdefault_check_until    65536

static int __count = 0;
static xsync * sync = xnil;

static int __condition_thread_func(struct xthread * o)
{
    struct timespec timespec;
    for(xuint64 i = 0; i < o->parameter.u64; i++)
    {
        xsynclock(sync);
        if(random() % 2)
        {
            timespec = (struct timespec) { 0, random() % 1000000000 };
            xsyncwait(sync, &timespec);
        }
        else
        {
            xsyncwait(sync, xnil);
        }
        xsyncunlock(sync);
    }
    xsynclock(sync);
    __count = __count + 1;
    xsyncunlock(sync);
    return xsuccess;
}

static int check_condition(int total)
{
    sync = xsyncnew(xsync_type_mutex);
    xsyncon(sync, true);
    xlist * threads = xlistnew();
    struct timespec timespec;
    for(int i = 0; i < total; i++)
    {
        xthread * thread = xthreadnew(__condition_thread_func);
        xlistpush(threads, xvalgenptr(thread));
        xthreadon(thread, xvalgen(random() % xdefault_check_until));
    }
    while(__count < total)
    {
        timespec = (struct timespec) { 0, random() % 1000000000 };

        xsynclock(sync);
        xsyncwait(sync, &timespec);
        xsyncwakeup(sync, (random() % 2));
        xsyncunlock(sync);
    }
    for(xlistnode * node = threads->head; node != xnil; node = node->next)
    {
        xthreadrem((xthread *) node->value.ptr, xnil);
    }
    sync = xsyncrem(sync);
    xlistrem(threads, xnil);
    return true;
}

static int __mutex_thread_func(struct xthread * o)
{
    for(xuint64 i = 0; i < o->parameter.u64; i++)
    {
        xsynclock(sync);
        __count = __count + 1;
        xsyncunlock(sync);
    }
    return xsuccess;
}

static int check_mutex(int total)
{
    xuint64 expected = 0;
    sync = xsyncnew(xsync_type_mutex);
    xsyncon(sync, false);
    xlist * threads = xlistnew();
    for(int i = 0; i < total; i++)
    {
        xthread * thread = xthreadnew(__mutex_thread_func);
        xlistpush(threads, xvalgenptr(thread));
        xuint64 n = random() % xdefault_check_until;
        expected += n;
        xthreadon(thread, xvalgen(n));
    }
    for(xlistnode * node = threads->head; node != xnil; node = node->next)
    {
        xthreadrem((xthread *) (node->value.ptr), xnil);
    }
    assertion(__count != expected, "mutex is not working");
    __count = 0;
    xlistrem(threads, xnil);
    xsyncoff(sync);
    sync = xsyncrem(sync);
    return true;
}

static int __simple_thread_func(struct xthread * o)
{
    for(xuint64 i = 0; i < o->parameter.u64; i++)
    {
        fprintf(stdout, "thread %lu\n", i);
    }
    return xsuccess;
}

static int check_thread(int total)
{
    xlist * threads = xlistnew();

    for(int i = 0; i < total; i++)
    {
        xthread * thread = xthreadnew(__simple_thread_func);
        xlistpush(threads, xvalgenptr(thread));
        xthreadon(thread, xvalgen(random() % xdefault_check_until));
    }
    for(xlistnode * node = threads->head; node != xnil; node = node->next)
    {
        xthreadrem(node->value.ptr, xnil);
    }
    xlistrem(threads, xnil);
    return true;
}

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
    fprintf(stdout, "check map(%d) => %s\n", total, check_map(total) ? "ok" : "fail");
    total = random() % xdefault_check_size;
    fprintf(stdout, "check thread(%d) => %s\n", total, check_thread(total) ? "ok" : "fail");
    total = random() % xdefault_check_size;
    fprintf(stdout, "check mutex(%d) => %s\n", total, check_mutex(total) ? "ok" : "fail");
    total = random() % xdefault_check_size;
    fprintf(stdout, "check condition(%d) => %s\n", total, check_condition(total) ? "ok" : "fail");

    return 0;
}
