#include "pool.h"

#include "../processor.h"

extern void xeventprocessorpoll_add(xeventprocessorpool * pool, xuint64 n)
{
    for(xuint64 i = 0; i < n; i++)
    {
        xeventprocessor * processor = xeventprocessor_new(pool);

        processor->prev = pool->tail;
        if(processor->prev)
        {
            processor->prev->next = processor;
        }
        else
        {
            pool->head = processor;
        }
        pool->tail = processor;
        pool->size = pool->size + 1;
    }
}