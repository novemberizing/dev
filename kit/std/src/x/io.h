#ifndef   __NOVEMBERIZING_X__IO__H__
#define   __NOVEMBERIZING_X__IO__H__

#include <x/std.h>

struct xclient;
struct xserver;
struct xsession;
struct xsocket;
struct xdescriptor;
struct xdescriptorexception;
struct xdescriptoreventgenerator;
struct xdescriptoreventgeneratorsubscriptions;
struct xdescriptoreventsubscription;


typedef struct xdescriptorexception xdescriptorexception;
typedef struct xdescriptoreventgenerator xdescriptoreventgenerator;
typedef struct xdescriptoreventsubscription xdescriptoreventsubscription;
typedef struct xdescriptoreventgeneratorsubscriptions xdescriptoreventgeneratorsubscriptions;
typedef struct xclient xclient;
typedef struct xserver xserver;
typedef struct xsession xsession;
typedef struct xsocket xsocket;
typedef struct xdescriptor xdescriptor;

typedef xsocket * (*xsocketdestructor)(xsocket *);
typedef xdescriptor * (*xdescriptordestructor)(xdescriptor *);

#define xdescriptormask_void            (0x00000000u)
#define xdescriptormask_nonblock        (0x00000001u)

#define xdescriptoreventmask_void       (0x00000000u)
#define xdescriptoreventmask_open       (0x00000001u)
#define xdescriptoreventmask_in         (0x00000002u)
#define xdescriptoreventmask_out        (0x00000004u)
#define xdescriptoreventmask_close      (0x00000008u)
#define xdescriptoreventmask_exception  (0x00000010u)
#define xdescriptoreventmask_rem        (0x00000020u)
#define xdescriptoreventmask_register   (0x00000040u)

#define xdescriptorstatus_void          xdescriptoreventmask_void
#define xdescriptorstatus_open          xdescriptoreventmask_open
#define xdescriptorstatus_in            xdescriptoreventmask_in
#define xdescriptorstatus_out           xdescriptoreventmask_out
#define xdescriptorstatus_close         xdescriptoreventmask_close
#define xdescriptorstatus_exception     xdescriptoreventmask_exception
#define xdescriptorstatus_rem           xdescriptoreventmask_rem
#define xdescriptorstatus_register      xdescriptoreventmask_register

#include <x/descriptor/exception.h>



// #define xdescriptormask_nonblock    (0x00000001u)

// #define xdescriptorevent_void       (0x00000000u)
// #define xdescriptorevent_open       (0x00000001u)
// #define xdescriptorevent_in         (0x00000002u)
// #define xdescriptorevent_out        (0x00000004u)
// #define xdescriptorevent_close      (0x00000008u)
// #define xdescriptorevent_exception  (0x00000010u)



// #define xdescriptorstatus_void      xdescriptorevent_void
// #define xdescriptorstatus_open      xdescriptorevent_open
// #define xdescriptorstatus_in        xdescriptorevent_in
// #define xdescriptorstatus_out       xdescriptorevent_out
// #define xdescriptorstatus_close     xdescriptorevent_close
// #define xdescriptorstatus_exception xdescriptorevent_exception


// /** 어느 정도 정리되면 SOCKT 으로 옮길 것 */

// #define xsocketmask_nonblock        xdescriptormask_nonblock

// #define xsocketevent_void           xdescriptorevent_void
// #define xsocketevent_open           xdescriptorevent_open
// #define xsocketevent_in             xdescriptorevent_in
// #define xsocketevent_out            xdescriptorevent_out
// #define xsocketevent_close          xdescriptorevent_close
// #define xsocketevent_exception      xdescriptorevent_exception

// #define xsocketevent_create         (0x00010000u)
// #define xsocketevent_bind           (0x00020000u)
// #define xsocketevent_connect        (0x00040000u)
// #define xsocketevent_connecting     (0x00080000u)

// #define xsocketstatus_void          xdescriptorstatus_void
// #define xsocketstatus_open          xdescriptorstatus_open
// #define xsocketstatus_in            xdescriptorstatus_in
// #define xsocketstatus_out           xdescriptorstatus_out
// #define xsocketstatus_close         xdescriptorstatus_close
// #define xsocketstatus_exception     xdescriptorstatus_exception

// #define xsocketstatus_create        xsocketevent_create
// #define xsocketstatus_bind          xsocketevent_bind
// #define xsocketstatus_connect       xsocketevent_connect
// #define xsocketstatus_connecting    xsocketevent_connecting

#endif // __NOVEMBERIZING_X__IO__H__
