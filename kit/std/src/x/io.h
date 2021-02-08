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
#define xdescriptor_event_register          (0x00002000u)
#define xdescriptor_event_rem               (0x00004000u)

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
#define xdescriptor_status_register         xdescriptor_event_register
#define xdescriptor_status_rem              xdescriptor_event_rem

struct xdescriptor;
typedef struct xdescriptor xdescriptor;

extern void xdescriptor_debug_print_event(xuint32 event);

struct xdescriptorio;

typedef struct xdescriptorio xdescriptorio;

#define xdescriptorio_status_void           (0x00000000u)
#define xdescriptorio_status_cancel         (0x80000000u)

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
    xuint32 status;
};

extern xdescriptorio * xdescriptorio_new(void);
extern xdescriptorio * xdescriptorio_rem(xdescriptorio * o);

extern xint32 xdescriptorio_reg(xdescriptorio * o, xdescriptor * descriptor);
extern xint32 xdescriptorio_unreg(xdescriptorio * o, xdescriptor * descriptor);

extern void xdescriptorio_call(xdescriptorio * o);

#endif // __NOVEMBERIZING_X__IO__H__
