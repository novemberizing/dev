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

static void example_net_client(void)
{
    // 로컬에서 클라이언트를 생성합니다.
    xclient local = xclientinit(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
    xclientrem(&local);
    // 동적할당으로 클라이언트를 생성합니다.
    xclient * o = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
    o = xclientrem(o);

    // 클라이언트를 오픈 하고 특정 주소를 할당합니다.
    if(o == xnil)
    {
        int ret = xsuccess;
        struct sockaddr_in addr;
        addr.sin_family = PF_INET;
        addr.sin_addr.s_addr = 0;
        addr.sin_port = htons(3371);
        // 소켓을 오픈한 후에 바인드합니다.
        o = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        ret = xclientopen(o);
        xassertion(ret != xsuccess, "fail to xclientopen");
        ret = xclientbind(o, &addr, sizeof(struct sockaddr_in));
        xassertion(ret != xsuccess, "fail to xclientbind");
        o = xclientrem(o);
        // 소켓을 바인드할 때 오픈합니다.
        o = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        ret = xclientbind(o, &addr, sizeof(struct sockaddr_in));
        // 바인드 실패하면 오픈 상태입니다. 명시적으로 소켓을 닫아주어야 합니다.
        if(ret != xsuccess)
        {
            xclientclose(o);
        }
        xassertion(ret != xsuccess, "fail to xclientbind");
        o = xclientrem(o);
    }

    /**
     * simple echo server
     * ncat -l 2000 -k -c 'xargs -n1 echo'
     */
    // 클라이언트 접속
    char data[1024];
    char buffer[1024];
    for(xint32 i = 0; i < 32; i++)
    {
        int ret = xsuccess;
        struct sockaddr_in addr;
        addr.sin_family = PF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addr.sin_port = htons(2000);
        // 소켓을 오픈한 후에 바인드합니다.
        o = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        ret = xclientopen(o);
        xassertion(ret != xsuccess, "fail to xclientopen");
        ret = xclientconnect(o, &addr, sizeof(struct sockaddr_in));
        o = xclientrem(o);
        // 소켓을 바인드할 때 오픈합니다.
        o = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        ret = xclientconnect(o, &addr, sizeof(struct sockaddr_in));
        // 바인드 실패하면 오픈 상태입니다. 명시적으로 소켓을 닫아주어야 합니다.
        if(ret != xsuccess)
        {
            if(xclientalive(o))
            {
                xclientclose(o);
            }
        }
        o = xclientrem(o);

        // 접속 후에 논블록 설정을 합니다.
        o = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        ret = xclientconnect(o, &addr, sizeof(struct sockaddr_in));
        xclientnonblock_on(o);
        xint64 n = xclientread(o, buffer, 1024);
        if(n == 0)
        {
            printf("again\n");
        }
        // 바인드 실패하면 오픈 상태입니다. 명시적으로 소켓을 닫아주어야 합니다.
        if(ret != xsuccess)
        {
            if(xclientalive(o))
            {
                xclientclose(o);
            }
        }
        o = xclientrem(o);

        // 비동기 접속을 수행하는 예제입니다.
        o = xclientnew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xnil);
        xclientset_nonblock_on(o);
        ret = xclientconnect(o, &addr, sizeof(struct sockaddr_in));
        // 바인드 실패하면 오픈 상태입니다. 명시적으로 소켓을 닫아주어야 합니다.
        if(ret != xsuccess)
        {
            if(xclientalive(o))
            {
                xclientclose(o);
            }
        }
        else
        {
            if(o->descriptor.status & xclient_status_connecting)
            {
                printf("client connecting\n");
            }
            xuint32 result = xclientwait(o, xclient_event_connected, 1, 0);
            if(result & xclient_event_connected)
            {
                printf("client connected\n");
                result = xclientwait(o, xdescriptor_event_in, 1, 0);
                printf("result 0x%08x\n", result);
                if(result & xdescriptor_event_timeout)
                {
                    printf("timeout\n");
                }
                int len = snprintf(data, 1024, "helloworld%d\n", i);
                xint64 n = xclientwrite(o, data, len);
                if(n >= 0)
                {
                    printf("send => %ld\n", n);
                    result = xclientwait(o, xdescriptor_event_in, 5, 0);
                    printf("result 0x%08x\n", result);
                    if(result & xdescriptor_event_timeout)
                    {
                        printf("timeout\n");
                    }
                    n = xclientread(o, buffer, 1023);
                    if(n >= 0)
                    {
                        buffer[n] = 0;
                        printf("recv[%ld] %s", n, buffer);
                    }
                    else
                    {
                        printf("fail to socket read => close status (%d)\n", o->descriptor.handle.f);
                    }
                }
                else
                {
                    printf("fail to socket write => close status (%d)\n", o->descriptor.handle.f);
                }
            }
            else if(result & xdescriptor_event_timeout)
            {
                printf("timeout\n");
            }
            else if(result & xdescriptor_event_exception)
            {
                printf("exception\n");
                xclientclose(o);
            }
        }
        xassertion(ret != xsuccess, "fail to xclientconnect");
        o = xclientrem(o);
    }
}

int main(int argc, char ** argv)
{
    example_net_socket();
    example_net_client();
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
