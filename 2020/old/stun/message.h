#ifndef   __NOVEMBERIZING_STUN_MESSAGE__H__
#define   __NOVEMBERIZING_STUN_MESSAGE__H__

#include <stdint.h>

#ifdef    _WIN32
#define   messagepack  
#else
#define   messagepack __attribute__((packed))
#endif // WIN32

typedef struct __header {
    uint8_t signature: 2;
    uint16_t type: 14;
    uint16_t length;
    uint32_t magic;
    uint32_t transaction[3];
} messagepack header;

#endif // __NOVEMBERIZING_STUN_MESSAGE__H__
