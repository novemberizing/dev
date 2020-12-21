#ifndef   __NOVEMBERIZING__STUN_MESSAGE_HEADER__H__
#define   __NOVEMBERIZING__STUN_MESSAGE_HEADER__H__

#include <stdint.h>

#ifdef    _WIN32
#define   messagepack  
#else
#define   messagepack __attribute__((packed))
#endif // WIN32

struct __x_stun_message_header {
    uint8_t  signature: 2;
    uint16_t type: 14;
    uint16_t length;
    uint32_t magic;
    uint32_t transaction[3];
} messagepack;

enum __x_stun_message_class {
    x_stun_message_class_request    = 0x0000,
    x_stun_message_class_indication = 0x0010,
    x_stun_message_class_success    = 0x0100,
    x_stun_message_class_error      = 0x0110,
    x_stun_message_class_flags      = 0x0110,
};

#define X_STUN_MESSAGE_HEADER_MAGIC_COOKIE        0x2112A442

typedef struct __x_stun_message_header x_stun_message_header;

extern int x_stun_message_header_validate(const x_stun_message_header * header);

#endif // __NOVEMBERIZING__STUN_MESSAGE_HEADER__H__