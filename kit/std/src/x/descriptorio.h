/**
 * 내부에서는 공통적으로 사용되지만 외부에서는 참조할 수 없다.
 */
#ifndef   __NOVEMBERIZING_X__DESCRIPTORIO__H__
#define   __NOVEMBERIZING_X__DESCRIPTORIO__H__

#include "io.h"

extern void xdescriptorio_queue_push(xdescriptorio * io, xdescriptor * descriptor);
extern xdescriptor * xdescriptorio_queue_del(xdescriptorio * io, xdescriptor * descriptor);

extern void xdescriptorio_children_push(xdescriptorio * io, xdescriptor * descriptor);
extern xdescriptor * xdescriptorio_children_del(xdescriptorio * io, xdescriptor * descriptor);

extern xint32 xdescriptorio_dispatch(xdescriptorio * io, xdescriptor * descriptor, xuint32 event);

extern xint32 xdescriptorio_dispatch_exception(xdescriptorio * io, xdescriptor * descriptor);
extern xint32 xdescriptorio_dispatch_in(xdescriptorio * io, xdescriptor * descriptor);
extern xint32 xdescriptorio_dispatch_out(xdescriptorio * io, xdescriptor * descriptor);
extern xint32 xdescriptorio_dispatch_open(xdescriptorio * io, xdescriptor * descriptor);
extern xint32 xdescriptorio_dispatch_close(xdescriptorio * io, xdescriptor * descriptor);
extern xint32 xdescriptorio_dispatch_shutdown_all(xdescriptorio * io, xdescriptor * descriptor);
extern xint32 xdescriptorio_dispatch_shutdown_in(xdescriptorio * io, xdescriptor * descriptor);
extern xint32 xdescriptorio_dispatch_shutdown_out(xdescriptorio * io, xdescriptor * descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTORIO__H__
