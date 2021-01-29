#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <x/net.h>

static void example_net_socket(void)
{
    // 로컬에 소켓을 생성합니다.
    xsocket local = xsocketinit(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
    xsocketrem(xaddressof(local));
    // 동적할당으로 소켓을 생성합니다.
    xsocket * o = xsocketnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
    o = xsocketrem(o);
    // 소켓을 오픈합니다.
    o = xsocketnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
    int ret = xsocketopen(o);
    xassertion(ret != xsuccess, "fail to xsocketopen");
    o = xsocketrem(o);
    // 소켓을 오픈 하고 특정 주소를 할당합니다.
    if(o == xnil)
    {
        int ret = xsuccess;
        struct sockaddr_in addr;
        addr.sin_family = PF_INET;
        addr.sin_addr.s_addr = 0;
        addr.sin_port = htons(3371);
        // 소켓을 오픈한 후에 바인드합니다.
        o = xsocketnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        ret = xsocketopen(o);
        xassertion(ret != xsuccess, "fail to xsocketopen");
        ret = xsocketbind(o, &addr, sizeof(struct sockaddr_in));
        xassertion(ret != xsuccess, "fail to xsocketbind");
        o = xsocketrem(o);
        // 소켓을 바인드할 때 오픈합니다.
        o = xsocketnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        ret = xsocketbind(o, &addr, sizeof(struct sockaddr_in));
        // 바인드 실패하면 오픈 상태입니다. 명시적으로 소켓을 닫아주어야 합니다.
        if(ret != xsuccess)
        {
            xsocketclose(o);
        }
        xassertion(ret != xsuccess, "fail to xsocketbind");
        o = xsocketrem(o);
    }
}

int main(int argc, char ** argv)
{
    example_net_socket();
    return 0;
    // printf("net\n");
    // xdescriptor descriptor = xdescriptorinit();

    // printf("%d\n", descriptor.value.f);
    // printf("%d\n", xdescriptoralive(xaddressof(descriptor)));

    // xsocket socket = xsocketinit(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // xsocketopen(xaddressof(socket));

    // printf("%s\n", xsocketalive(xaddressof(socket)) ? "true" : "false");

    // // simple server ... 

    // xsocketclose(xaddressof(socket));

    // /**
    //  * simple echo server
    //  * ncat -l 2000 -k -c 'xargs -n1 echo'
    //  */
    // xclient * client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // struct sockaddr_in addr;
    // addr.sin_family = PF_INET;
    // addr.sin_port = htons(2000);
    // addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // socklen_t addrlen = sizeof(struct sockaddr_in);
    // xclientconnect(client, xaddressof(addr), addrlen);
    // xclientsend(client, "hello\n", 6);
    // char buffer[8];
    // int ret = xclientrecv(client, buffer, 5);
    // buffer[5] = 0;
    // printf("[recv:%d] %s\n", ret, buffer);
    // xclientrem(client);

    // // SET NONBLOCKING
    // buffer[0] = 0;
    // client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // addr.sin_family = PF_INET;
    // addr.sin_port = htons(2000);
    // addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // addrlen = sizeof(struct sockaddr_in);
    // xclientconnect(client, xaddressof(addr), addrlen);
    // xclient_nonblock_on(client);
    // xclientsend(client, "hello\n", 6);
    // ret = xclientrecv(client, buffer, 5);
    // buffer[5] = 0;
    // printf("[recv:%d] %s\n", ret, buffer);
    // xclientrem(client);

    // // SET NONBLOCKING & OFF
    // buffer[0] = 0;
    // client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // addr.sin_family = PF_INET;
    // addr.sin_port = htons(2000);
    // addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // addrlen = sizeof(struct sockaddr_in);
    // xclientconnect(client, xaddressof(addr), addrlen);
    // xclient_nonblock_on(client);
    // xclient_nonblock_off(client);
    // xclientsend(client, "hello\n", 6);
    // ret = xclientrecv(client, buffer, 5);
    // buffer[5] = 0;
    // printf("[recv:%d] %s\n", ret, buffer);
    // xclientrem(client);

    // // SET NONBLOCKING CONNECT
    // for(int i = 0; i < xrandomgen() % 2048; i++)
    // {
    //     printf("nonblock connect\n");
    //     buffer[0] = 0;
    //     client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //     xclientmaskadd(client, xsocket_mask_nonblock);
    //     addr.sin_family = PF_INET;
    //     addr.sin_port = htons(2000);
    //     addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //     addrlen = sizeof(struct sockaddr_in);
    //     ret = xclientconnect(client, xaddressof(addr), addrlen);
    //     xcheck(ret != xsuccess, "working nonblock connect");
    //     printf("connect => %d\n", ret);
    //     xclient_nonblock_on(client);
    //     // NONBLOCLING CONNECT 상태에서 WRITE 가 가능하다.
    //     ret = xclientsend(client, "hello\n", 6);
    //     xclient_nonblock_off(client);
    //     printf("send => %d\n", ret);
    //     ret = xclientrecv(client, buffer, 5);
    //     buffer[5] = 0;
    //     printf("[recv:%d] %s\n", ret, buffer);
    //     xclientrem(client);
    // }

    // // SET NONBLOCKING CONNECT
    // for(int i = 0; i < xrandomgen() % 64; i++)
    // {
    //     printf("nonblock connect %d\n", i);
    //     buffer[0] = 0;
    //     client = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //     xclientmaskadd(client, xsocket_mask_nonblock);
    //     addr.sin_family = PF_INET;
    //     addr.sin_port = htons(2000);
    //     addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //     addrlen = sizeof(struct sockaddr_in);
    //     ret = xclientconnect(client, xaddressof(addr), addrlen);
    //     xcheck(ret != xsuccess, "working nonblock connect");
    //     printf("connect => %d\n", ret);

    //     if(client->status & xclient_status_connecting)
    //     {
    //         xuint32 status = xclientwait(client, xclient_event_connect, 1000000000);
    //         xcheck((status & xclient_event_connect) != xclient_event_connect, "not connect (%08x)", status);
    //         if((status & xclient_event_connect) != xclient_event_connect)
    //         {
    //             xclientclose(client);
    //         }
    //     }

    //     // xclient_nonblock_on(client);
    //     // NONBLOCLING CONNECT 상태에서 WRITE 가 가능하다.
    //     ret = xclientsend(client, "hello\n", 6);
    //     // xclient_nonblock_off(client);
    //     printf("send => %d\n", ret);
    //     xuint32 status = xclientwait(client, xclient_event_read, 1000000000);
    //     printf("status (0x%08x)\n", status);
    //     ret = xclientrecv(client, buffer, 5);
    //     if(ret > 0)
    //     {
    //         buffer[5] = 0;
    //         printf("[recv:%d] %s\n", ret, buffer);
    //     }
    //     xclientrem(client);
    // }

    // // SERVER
    // {
    //     xserver * server = xservernew(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //     struct sockaddr_in addr;
    //     addr.sin_family = PF_INET;
    //     addr.sin_addr.s_addr = 0;
    //     addr.sin_port = htons(3371);
    //     socklen_t addrlen = sizeof(struct sockaddr_in);

    //     int ret = xserverlisten(server, &addr, addrlen);
    //     xassertion(ret != xsuccess, "fail to server listen");
    //     xcheck(xtrue, "server listen");

    //     xserverrem(server);
    // }


    // return 0;
}
