#include "header.h"

#include <stdio.h>

/**
 * 
 * @param   [in]    | header | const x_stun_message_header * | stun message header |
 */
int x_stun_message_header_validate(const x_stun_message_header * header) {
    if(header->signature != 0) {

    }
    return 0;
}

int main(int argc, char ** argv)
{
    printf("%ld\n", sizeof(x_stun_message_header));
    printf("%ld\n", sizeof(struct __x_stun_message_header));
    return 0;
}