#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <x/net.h>

int main(int argc, char ** argv)
{
    printf("net\n");
    xdescriptor descriptor = xdescriptorinit();

    printf("%d\n", descriptor.f);
    printf("%d\n", xdescriptoralive(xaddressof(descriptor)));

    xsocket socket = xsocketinit(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    xsocketopen(xaddressof(socket));

    printf("%d\n", xsocketalive(xaddressof(socket)));

    // simple server ... 

    xsocketclose(xaddressof(socket));

    return 0;
}
