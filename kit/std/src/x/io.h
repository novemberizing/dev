#ifndef   __NOVEMBERIZING_X__IO__H__
#define   __NOVEMBERIZING_X__IO__H__

#include <x/std.h>
#include <x/sync.h>

struct xdescriptor;

typedef struct xdescriptor xdescriptor;

struct xclient;
struct xserver;
struct xsession;
struct xsocket;

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
#define xdescriptoreventmask_link       (0x00000080u)

#define xdescriptoreventmask_create     (0x00000100u)   // socket
#define xdescriptoreventmask_bind       (0x00000200u)   // socket
#define xdescriptoreventmask_connect    (0x00000400u)   // socket
#define xdescriptoreventmask_connecting (0x00000800u)   // socket

#define xdescriptorstatus_void          xdescriptoreventmask_void
#define xdescriptorstatus_open          xdescriptoreventmask_open
#define xdescriptorstatus_in            xdescriptoreventmask_in
#define xdescriptorstatus_out           xdescriptoreventmask_out
#define xdescriptorstatus_close         xdescriptoreventmask_close
#define xdescriptorstatus_exception     xdescriptoreventmask_exception
#define xdescriptorstatus_rem           xdescriptoreventmask_rem
#define xdescriptorstatus_register      xdescriptoreventmask_register
#define xdescriptorstatus_link          xdescriptoreventmask_link

#define xdescriptorstatus_create        xdescriptoreventmask_create
#define xdescriptorstatus_bind          xdescriptoreventmask_bind
#define xdescriptorstatus_connect       xdescriptoreventmask_connect
#define xdescriptorstatus_connecting    xdescriptoreventmask_connecting

#endif // __NOVEMBERIZING_X__IO__H__
