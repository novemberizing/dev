/**
 * @file    x/descriptor.h
 * @brief   [internal] 내부적으로 사용하는 디스크립터 로직
 * 
 *              외부에서는 이 파일의 구조를 보지 못한다.
 */
#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include "std.h"

#define xdescriptor_event_void          (0x00000000U)
#define xdescriptor_event_open          (0x00000001U)
#define xdescriptor_event_in            (0x00000002U)
#define xdescriptor_event_out           (0x00000004U)
#define xdescriptor_event_close         (0x00000008U)
#define xdescriptor_event_exception     (0x00000010U)

#define xdescriptor_status_void         xdescriptor_event_void
#define xdescriptor_status_open         xdescriptor_event_open
#define xdescriptor_status_in           xdescriptor_event_in
#define xdescriptor_status_out          xdescriptor_event_out
#define xdescriptor_status_close        xdescriptor_event_close
#define xdescriptor_status_exception    xdescriptor_event_exception

struct xdescriptor;
struct xdescriptorio;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorio xdescriptorio;

typedef xint32 (*xdescriptor_opener)(xdescriptor *);
typedef xint64 (*xdescriptor_event_handler)(xdescriptor *, xuint32, const void *, xint64);

struct xdescriptor
{
    union
    {
        int    f;
        void * v;
    } handle;

    xuint32            status;

    xdescriptor *      prev;
    xdescriptor *      next;
    xdescriptorio *    io;

    xdescriptor_opener open;            // 디스크립터의 오픈 함수가 존재하면 디스크립터 IO 에서 다시 오픈하는 디스크립터가 된다.

    xdescriptor_event_handler on;
};

extern xdescriptor * xdescriptor_new(xint32 f, xdescriptor_opener opener);
extern xdescriptor * xdescriptor_rem(xdescriptor * descriptor);

#define xdescriptor_open(descriptor)    ((descriptor && descriptor->open) ? descriptor->open(descriptor) : xsuccess)

extern xint64 xdescriptor_read(xdescriptor * descriptor, void * buffer, xuint64 size);
extern xint64 xdescriptor_write(xdescriptor * descriptor, const void * data, xuint64 len);
extern xint32 xdescriptor_close(xdescriptor * descriptor);

#define xdescriptoreventpub(descriptor, event, data, val)           \
    (descriptor->on ? descriptor->on(descriptor, event, data, val)  \
                    : xsuccess)

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
