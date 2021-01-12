#include <stdio.h>
#include <stdlib.h>

#include <x/std.h>

struct qitem
{
    struct qitem * next;
    struct qitem * prev;
    int value;
};

extern struct qitem * qitemnew(int value)
{
    struct qitem * o = calloc(sizeof(struct qitem), 1);
    o->value = value;
    return o;
}

struct q
{
    struct qitem * head;
    struct qitem * tail;
    xuint64 size;
};

#ifdef xqueuepop
#undef xqueuepop
#endif 

#define xqueuepop(queue)    queue->head, queue->head
    

int main(int argc, char ** argv)
{
    struct q queue = { 0, };

    struct q * p = &queue;

    struct qitem * item = qitemnew(1);

    xqueuepush(p, item);
    // struct qitem * item = (p->head), (p->head);

    item = xqueuepop(p);
    printf("%lx\n", item);
    free(item);
    // printf("%lx\n", item);

    return 0;
}