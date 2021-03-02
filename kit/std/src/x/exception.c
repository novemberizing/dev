#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

#include "exception.h"

extern const char * xexceptionmessage_get(void * func, xuint32 type, xint32 number)
{
    return "";
}

extern void xexceptionset(xexception * exception, void * func, xint32 number, xuint32 type, const char * message)
{
    xassertion(exception == xnil, "");

    if(exception->type == xexceptiontype_void)
    {
        exception->func = func;
        exception->number = number;
        exception->type = type;
        exception->message = message;
    }
}
