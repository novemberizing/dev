#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/net.h>

int main(int argc, char ** argv)
{
    printf("net\n");
    xdescriptor descriptor = xdescriptorinit();

    printf("%d\n", descriptor.f);
    printf("%d\n", xdescriptoralive(xaddressof(descriptor)));

    xsocket socket = xsocketinit(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    xsocketopen(xaddressof(socket));

    printf("%s\n", xsocketalive(xaddressof(socket)) ? "true" : "false");

    // simple server ... 

    xsocketclose(xaddressof(socket));

    /**
     * simple echo server
     * ncat -l 2000 -k -c 'xargs -n1 echo'
     */
    xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t addrlen = sizeof(struct sockaddr_in);
    xclientconnect(client, xaddressof(addr), addrlen);
    xclientsend(client, "hello\n", 6);
    char buffer[8];
    int ret = xclientrecv(client, buffer, 5);
    buffer[5] = 0;
    printf("[recv:%d] %s\n", ret, buffer);
    xclientrem(client);

    return 0;
}
