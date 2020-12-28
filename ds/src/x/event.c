#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <x/log.h>
#include <x/type.h>
#include <x/list.h>
#include <x/engine.h>

// struct xengine
// {
//     xuint32 status;
//     xlist * generators;
// };

// typedef struct xengine xengine;

// // signal event
// // time event
// // io event

// #define xengine_status_cancelling   0x80000000U

// struct xgenerator
// {
//     xuint32 type;
//     struct xgenerator * (*rem)(struct xgenerator *);
// };

// typedef struct xgenerator xgenerator;

// #define xengine_module_generator    1
// #define xengine_module_processor    2



// extern xengine * xenginenew();
// extern xengine * xenginerem(xengine * o);
// extern int xengineon(xengine * o);
// extern xengine * xengineplug(xengine * o, xuint32 type, void * module)
// {
//     return o;
// }

// struct xevent_generator_io
// {
//     xuint32 type;
//     struct xgenerator * (*rem)(struct xgenerator *);
// };

// #define xevent_generator_type_io 1

// typedef struct xevent_generator_io xevent_generator_io;

// extern xgenerator * xevent_generator_io_rem(xgenerator * p)
// {
//     xevent_generator_io * o = (xevent_generator_io *) p;
//     if(o)
//     {
//         assertion(o->type != xevent_generator_type_io, "event generator's type is not io");

//         free(o);
//     }
//     return NULL;
// }

// /**
//  */
// extern xgenerator * xevent_generator_io_new()
// {
//     xevent_generator_io * o = (xevent_generator_io *) calloc(sizeof(xevent_generator_io), 1);

//     o->type = xevent_generator_type_io;
//     o->rem  = xevent_generator_io_rem;

//     return (xgenerator *) o;
// }

int main(int argc, char ** argv)
{
    xengine * engine = xenginenew();

    xengineplug(engine, xengine_module_type_generator, xnil);

//    xengineplug(engine, xengine_module_generator, xnil);

//    xengineon(engine);

    xenginerem(engine);
    return 0;
}

// xengine * xenginenew()
// {
//     xengine * o = (xengine *) calloc(sizeof(xengine), 1);

//     assertion(o == NULL, "o is null caused by calloc (%d)", errno);

//     o->generators = xlistnew();

//     return o;
// }

// static inline void __xengine_generator_rem(xgenerator * o)
// {
//     assertion(o == NULL, "o is null");
//     assertion(o->rem == NULL, "o->rem is null");

//     xgenerator * (*rem)(xgenerator *) = o->rem;
//     rem(o);
// }

// xengine * xenginerem(xengine * o)
// {
//     if(o)
//     {
//         // TODO: GENERATOR'S REMOVE FUNCTION IMPLMENT
//         xlistrem(o->generators, NULL);
//         free(o);
//     }
//     return NULL;
// }

// int xengineon(xengine * o)
// {
//     assertion(o == NULL, "o is null");
//     assertion(o->status != 0, "engine is already running");

//     while((o->status & xengine_status_cancelling) != xengine_status_cancelling)
//     {
//         for(xlistnode * i = o->generators->head; i != xnil; i = i->next)
//         {
//             xgenerator * generator = (xgenerator *) i->value.ptr;
//         }
//     }

//     return xsuccess;
// }
