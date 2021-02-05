/**
 * @file    x/descriptor.h
 * @brief   [internal] 내부적으로 사용하는 디스크립터 로직
 * 
 *              외부에서는 이 파일의 구조를 보지 못한다.
 */
#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include "std.h"
#include "io.h"

struct xdescriptor;
struct xdescriptorio;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorio xdescriptorio;

typedef xint64 (*xdescriptor_event_handler)(xdescriptor *, xuint32, const void *, xint64);
typedef xint64 (*xdescriptor_process_func)(xdescriptor *, xuint32);

struct xdescriptor
{
    union
    {
        xint32 f;
        handle v;
    } handle;
    xuint32                   mask;
    xuint32                   status;
    xdescriptor *             prev;
    xdescriptor *             next;
    xdescriptorio *           io;
    xsync *                   sync;
    xdescriptor_process_func  process;
    xdescriptor_event_handler on;
};

#define xdescriptor_do(descriptor, event)   (descriptor                 \
    ? ((xdescriptor *) descriptor)->process((xdescriptor *) descriptor, \
                                            event)                      \
    : xfail)

#define xdescriptor_event_on(descriptor, event, data, val) (descriptor  \
    ? ((xdescriptor *) descriptor)->on((xdescriptor *) descriptor,      \
                                       event,                           \
                                       data,                            \
                                       val)                             \
    : xfail)

#define xdescriptor_open(descriptor)    xdescriptor_do(descriptor, xdescriptor_event_open)

extern xint64  xdescriptor_read(xdescriptor * descriptor, void * buffer, xuint64 size);
extern xint64  xdescriptor_write(xdescriptor * descriptor, const void * data, xuint64 len);
extern xint64  xdescriptor_close(xdescriptor * descriptor);
extern xint32  xdescriptor_nonblock_on(xdescriptor * descriptor);
extern xint32  xdescriptor_nonblock_off(xdescriptor * descriptor);
extern xuint32 xdescriptor_wait(xdescriptor * descriptor, xuint32 event, xint64 second, xint64 nanosecond);
extern void    xdescriptor_mask_add(xdescriptor * descriptor, xuint32 mask);
extern void    xdescriptor_mask_del(xdescriptor * descriptor, xuint32 mask);
extern xint32  xdescriptor_is_normal(xdescriptor * descriptor);
extern xint32  xdescriptor_is_unnormal(xdescriptor * descriptor);

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
};

extern xdescriptorio * xdescriptorio_new(void);
extern xdescriptorio * xdescriptorio_rem(xdescriptorio * o);

extern xint32 xdescriptorio_reg(xdescriptorio * o, xdescriptor * descriptor);
extern xint32 xdescriptorio_unreg(xdescriptorio * o, xdescriptor * descriptor);

extern void xdescriptorio_call(xdescriptorio * o);

// #define xdescrpitor_close(descriptor)   xdescriptor_do(descriptor, xdescriptor_event_close)

// #define xdescriptor_event_void          (0x00000000U)
// #define xdescriptor_event_open          (0x00000001U)
// #define xdescriptor_event_in            (0x00000002U)
// #define xdescriptor_event_out           (0x00000004U)
// #define xdescriptor_event_close         (0x00000008U)
// #define xdescriptor_event_exception     (0x00000010U)
// #define xdescriptor_event_create        (0x00000020U)
// #define xdescriptor_event_bind          (0x00000040U)
// #define xdescriptor_event_connect       (0x00000080U)

// #define xsocket_event_void              xdescriptor_event_void
// #define xsocket_event_open              xdescriptor_event_open
// #define xsocket_event_in                xdescriptor_event_in
// #define xsocket_event_out               xdescriptor_event_out
// #define xsocket_event_close             xdescriptor_event_close
// #define xsocket_event_exception         xdescriptor_event_exception
// #define xsocket_event_create            xdescriptor_event_create
// #define xsocket_event_bind              xdescriptor_event_bind
// #define xsocket_event_connect           xdescriptor_event_connect

// #define xdescriptor_status_void         xdescriptor_event_void
// #define xdescriptor_status_open         xdescriptor_event_open
// #define xdescriptor_status_in           xdescriptor_event_in
// #define xdescriptor_status_out          xdescriptor_event_out
// #define xdescriptor_status_close        xdescriptor_event_close
// #define xdescriptor_status_exception    xdescriptor_event_exception
// #define xdescriptor_status_create       xdescriptor_event_create
// #define xdescriptor_status_bind         xdescriptor_event_bind
// #define xdescriptor_status_connect      xdescriptor_event_connect

// #define xsocket_status_void             xdescriptor_event_void
// #define xsocket_status_open             xdescriptor_event_open
// #define xsocket_status_in               xdescriptor_event_in
// #define xsocket_status_out              xdescriptor_event_out
// #define xsocket_status_close            xdescriptor_event_close
// #define xsocket_status_exception        xdescriptor_event_exception
// #define xsocket_status_create           xdescriptor_event_create
// #define xsocket_status_bind             xdescriptor_event_bind
// #define xsocket_status_connect          xdescriptor_event_connect

// struct xdescriptor;

// struct xdescriptorio;

// typedef struct xdescriptor xdescriptor;
// typedef struct xdescriptorio xdescriptorio;

// typedef xint32 (*xdescriptor_opener)(xdescriptor *);
// typedef xint64 (*xdescriptor_event_processor)(xdescriptor *, xuint32);
// typedef xint64 (*xdescriptor_event_handler)(xdescriptor *, xuint32, const void *, xint64);

// struct xdescriptor
// {
//     union
//     {
//         int    f;
//         void * v;
//     } handle;

//     xuint32            status;

//     xdescriptor *      prev;
//     xdescriptor *      next;
//     xdescriptorio *    io;

//     xsync * sync;

//     xdescriptor_opener          open;
//     xdescriptor_event_processor process;
//     xdescriptor_event_handler   on;
// };

// extern xdescriptor * xdescriptor_new(xint32 f, xdescriptor_event_handler handler, xdescriptor_event_processor processor, xdescriptor_opener opener);
// extern xdescriptor * xdescriptor_rem(xdescriptor * descriptor);

// #define xdescriptor_open(descriptor)    ((descriptor && descriptor->open) ? descriptor->open(descriptor) : xsuccess)

// extern xint64 xdescriptor_read(xdescriptor * descriptor, void * buffer, xuint64 size);
// extern xint64 xdescriptor_write(xdescriptor * descriptor, const void * data, xuint64 len);
// extern xint32 xdescriptor_close(xdescriptor * descriptor);

// #define xdescriptoreventpub(descriptor, event, data, val)               \
//     (((xdescriptor *)descriptor)->on                                    \
//         ? ((xdescriptor *)descriptor)->on(descriptor, event, data, val) \
//         : xsuccess)

// #define xdescriptor_alive(descriptor)           (descriptor && (((xdescriptor *) descriptor)->handle.f >= 0))
// #define xdescriptor_handle_value(descriptor)    (descriptor ? ((xdescriptor *) descriptor)->handle.f : xinvalid)
// #define xdescriptorstatus_add(descriptor, mask) (((xdescriptor *) descriptor)->status |= mask)
// #define xdescriptorstatus_rem(descriptor, mask) (((xdescriptor *) descriptor)->status &= (~mask))

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
