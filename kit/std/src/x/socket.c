#include "socket.h"

extern xsocket * xsocketnew(xuint64 size)
{
    xassertion(size < sizeof(xsocket), "");

    xsocket * o = xdescriptornew(size);

    return o;
}