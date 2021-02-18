#include "processor.h"

extern xeventprocessor * xeventprocessor_new(xeventprocessorpool * pool)
{
    xassertion(pool == xnil, "");

    xeventprocessor * processor = (xeventprocessor *) calloc(sizeof(xeventprocessor), 1);

    processor->pool = pool;

    return processor;
}