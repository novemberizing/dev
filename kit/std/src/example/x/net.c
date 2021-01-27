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

    printf("%d\n", descriptor.value.f);
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

    // SET NONBLOCKING
    buffer[0] = 0;
    client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrlen = sizeof(struct sockaddr_in);
    xclientconnect(client, xaddressof(addr), addrlen);
    xclient_nonblock_on(client);
    xclientsend(client, "hello\n", 6);
    ret = xclientrecv(client, buffer, 5);
    buffer[5] = 0;
    printf("[recv:%d] %s\n", ret, buffer);
    xclientrem(client);

    // SET NONBLOCKING & OFF
    buffer[0] = 0;
    client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    addr.sin_family = PF_INET;
    addr.sin_port = htons(2000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrlen = sizeof(struct sockaddr_in);
    xclientconnect(client, xaddressof(addr), addrlen);
    xclient_nonblock_on(client);
    xclient_nonblock_off(client);
    xclientsend(client, "hello\n", 6);
    ret = xclientrecv(client, buffer, 5);
    buffer[5] = 0;
    printf("[recv:%d] %s\n", ret, buffer);
    xclientrem(client);

    // SET NONBLOCKING CONNECT
    for(int i = 0; i < xrandomgen() % 2048; i++)
    {
        printf("nonblock connect\n");
        buffer[0] = 0;
        client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        xclientmaskadd(client, xsocket_mask_nonblock);
        addr.sin_family = PF_INET;
        addr.sin_port = htons(2000);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addrlen = sizeof(struct sockaddr_in);
        ret = xclientconnect(client, xaddressof(addr), addrlen);
        xcheck(ret != xsuccess, "working nonblock connect");
        printf("connect => %d\n", ret);
        xclient_nonblock_on(client);
        // NONBLOCLING CONNECT 상태에서 WRITE 가 가능하다.
        ret = xclientsend(client, "hello\n", 6);
        xclient_nonblock_off(client);
        printf("send => %d\n", ret);
        ret = xclientrecv(client, buffer, 5);
        buffer[5] = 0;
        printf("[recv:%d] %s\n", ret, buffer);
        xclientrem(client);
    }

    // SET NONBLOCKING CONNECT
    for(int i = 0; i < xrandomgen() % 64; i++)
    {
        printf("nonblock connect %d\n", i);
        buffer[0] = 0;
        client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        xclientmaskadd(client, xsocket_mask_nonblock);
        addr.sin_family = PF_INET;
        addr.sin_port = htons(2000);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addrlen = sizeof(struct sockaddr_in);
        ret = xclientconnect(client, xaddressof(addr), addrlen);
        xcheck(ret != xsuccess, "working nonblock connect");
        printf("connect => %d\n", ret);

        if(client->status & xclient_status_connecting)
        {
            xuint32 status = xclientwait(client, xclient_event_connect, 1000000000);
            xcheck((status & xclient_event_connect) != xclient_event_connect, "not connect (%08x)", status);
            if((status & xclient_event_connect) != xclient_event_connect)
            {
                xclientclose(client);
            }
        }

        // xclient_nonblock_on(client);
        // NONBLOCLING CONNECT 상태에서 WRITE 가 가능하다.
        ret = xclientsend(client, "hello\n", 6);
        // xclient_nonblock_off(client);
        printf("send => %d\n", ret);
        xuint32 status = xclientwait(client, xclient_event_read, 1000000000);
        printf("status (0x%08x)\n", status);
        ret = xclientrecv(client, buffer, 5);
        if(ret > 0)
        {
            buffer[5] = 0;
            printf("[recv:%d] %s\n", ret, buffer);
        }
        xclientrem(client);
    }

    // SERVER
    {
        xserver * server = xservernew(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        struct sockaddr_in addr;
        addr.sin_family = PF_INET;
        addr.sin_addr.s_addr = 0;
        addr.sin_port = htons(3371);
        socklen_t addrlen = sizeof(struct sockaddr_in);

        int ret = xserverlisten(server, &addr, addrlen);
        xassertion(ret != xsuccess, "fail to server listen");
        xcheck(xtrue, "server listen");

        xserverrem(server);
    }


    return 0;
}
