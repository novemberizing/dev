#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

#define xnil            ((void *) 0)

typedef __INT8_TYPE__   xint8;
typedef __INT16_TYPE__  xint16;
typedef __INT32_TYPE__  xint32;
typedef __INT64_TYPE__  xint64;
typedef __UINT8_TYPE__  xuint8;
typedef __UINT16_TYPE__ xuint16;
typedef __UINT32_TYPE__ xuint32;
typedef __UINT64_TYPE__ xuint64;




#define xdescriptor_event_type          (0x01000000U)

#define xdescriptor_event_open          (0x00000001U)
#define xdescriptor_event_in            (0x00000002U)
#define xdescriptor_event_out           (0x00000004U)
#define xdescriptor_event_exception     (0x00000008U)
#define xdescriptor_event_close         (0x00000010U)

struct xstream;

struct xeventengine;
struct xeventobject;

struct xdescriptor;

struct xconsole;

struct xclient;
struct xserver;
struct xsession;

struct xsync;

typedef struct xdescriptor xdescriptor;

typedef struct xstream xstream;

typedef struct xclient xclient;
typedef struct xserver xserver;
typedef struct xsession xsession;

typedef struct xeventengine xeventengine;
typedef struct xeventobject xeventobject;

extern xeventengine * xeventengine_new(void);
extern void *         xeventengine_rem(void * pointer);

#endif // __NOVEMBERIZING_X__STD__H__
