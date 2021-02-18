#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xeventtarget;
struct xeventsubscription;
struct xeventprocessor;
struct xeventprocessorpool;
struct xeventengine;

typedef struct xeventtarget xeventtarget;
typedef struct xeventsubscription xeventsubscription;
typedef struct xeventprocessor xeventprocessor;
typedef struct xeventprocessorpool xeventprocessorpool;
typedef struct xeventengine xeventengine;

typedef xeventtarget * (*xeventtargetdestructor)(xeventtarget *);

#endif // __NOVEMBERIZING_X__EVENT__H__
