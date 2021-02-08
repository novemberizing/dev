#ifndef   __NOVEMBERIZING_X__IO__H__
#define   __NOVEMBERIZING_X__IO__H__

#include <x/std.h>

#define xdescriptor_mask_nonblock           (0x00000001u)

#define xdescriptor_event_void              (0x00000000u)
#define xdescriptor_event_open              (0x00000001u)
#define xdescriptor_event_in                (0x00000002u)
#define xdescriptor_event_out               (0x00000004u)
#define xdescriptor_event_close             (0x00000008u)
#define xdescriptor_event_exception         (0x00000010u)
#define xdescriptor_event_create            (0x00000020u)
#define xdescriptor_event_bind              (0x00000040u)
#define xdescriptor_event_connect           (0x00000080u)
#define xdescriptor_event_listen            (0x00000100u)
#define xdescriptor_event_shutdown_in       (0x00000200u)
#define xdescriptor_event_shutdown_out      (0x00000400u)
#define xdescriptor_event_shutdown_all      (xdescriptor_event_shutdown_in | xdescriptor_event_shutdown_out)
#define xdescriptor_event_timeout           (0x00000800u)
#define xdescriptor_event_connecting        (0x00001000u)

#define xdescriptor_status_void             xdescriptor_event_void
#define xdescriptor_status_open             xdescriptor_event_open
#define xdescriptor_status_in               xdescriptor_event_in
#define xdescriptor_status_out              xdescriptor_event_out
#define xdescriptor_status_close            xdescriptor_event_close
#define xdescriptor_status_exception        xdescriptor_event_exception
#define xdescriptor_status_create           xdescriptor_event_create
#define xdescriptor_status_bind             xdescriptor_event_bind
#define xdescriptor_status_connect          xdescriptor_event_connect
#define xdescriptor_status_listen           xdescriptor_event_listen
#define xdescriptor_status_shutdown_in      xdescriptor_event_shutdown_in
#define xdescriptor_status_shutdown_out     xdescriptor_event_shutdown_out
#define xdescriptor_status_shutdown_all     xdescriptor_event_shutdown_all
#define xdescriptor_status_timeout          xdescriptor_event_timeout
#define xdescriptor_status_connecting       xdescriptor_event_connecting

#define xdescriptorio_status_void           (0x00000000u)
#define xdescriptorio_status_cancel         (0x80000000u)

struct xdescriptor;
struct xdescriptorio;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorio xdescriptorio;

struct xdescriptorio
{
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } children;
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } queue;
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } exceptions;
    xuint32 status;
};

extern void xdescriptor_debug_print_event(xuint32 event);

extern xdescriptorio * xdescriptorio_new(void);
extern xdescriptorio * xdescriptorio_rem(xdescriptorio * o);

extern xint32 xdescriptorio_reg(xdescriptorio * o, xdescriptor * descriptor);
extern xint32 xdescriptorio_unreg(xdescriptorio * o, xdescriptor * descriptor);

extern void xdescriptorio_call(xdescriptorio * o);
extern void xdescriptorio_clear(xdescriptorio * o);
extern void xdescriptorio_term(xdescriptorio * o);
extern xuint32 xdescriptorio_status(xdescriptorio * o);

#endif // __NOVEMBERIZING_X__IO__H__
