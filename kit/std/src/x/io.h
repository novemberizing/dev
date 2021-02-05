#ifndef   __NOVEMBERIZING_X__IO__H__
#define   __NOVEMBERIZING_X__IO__H__

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

#endif // __NOVEMBERIZING_X__IO__H__
