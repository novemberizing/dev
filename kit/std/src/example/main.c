/**
 * ncat -l 2000 -k -c 'xargs -n1 echo'
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <signal.h>

#include <x/std.h>
#include <x/io.h>
#include <x/client.h>
#include <x/server.h>

static xdescriptorio * __global_io = xnil;

static void terminate_descriptor_io(int number)
{
    if(__global_io)
    {
        printf("terminate descriptorio\n");
        __global_io->status |= xdescriptorio_status_cancel;
    }
}

static xint32 xexample_simple_client(void);
static xint32 xexample_simple_client_with_ncat(void);
static xint32 xexample_simple_client_with_ncat_nonblock(void);
static xint32 xexample_simple_client_with_ncat_nonblock_wait(void);
static xint32 xexample_simple_nonblock_connect(void);
static xint32 xexample_simple_server(void);
static xint32 xexample_simple_server_open(void);

static xint32 xexample_simple_server_with_descriptorio(void);

int main(int argc, char ** argv)
{
    xexample_simple_client();
    xexample_simple_client_with_ncat();
    xexample_simple_client_with_ncat_nonblock();
    xexample_simple_nonblock_connect();
    xexample_simple_server();
    xexample_simple_server_open();
    xexample_simple_server_with_descriptorio();

    return 0;
}

/**
 */

static xint32 xexample_simple_server_with_descriptorio(void)
{
    signal(SIGINT, terminate_descriptor_io);
    // signal(SIGINT)
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = 0;
    addrin.sin_port = htons(3371);

    xserver * server = xserver_new(PF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xserver));

    xdescriptorio * io = xdescriptorio_new();
    __global_io = io;

    xdescriptorio_reg(io, (xdescriptor *) server->descriptor);

    while((xdescriptorio_status(io) & xdescriptorio_status_cancel) == xdescriptorio_status_void)
    {
        xdescriptorio_call(io);
    }
    xdescriptorio_clear(io);

    xdescriptorio_rem(io);

    server = xserver_rem(server);

    return 0;
}

static xint32 xexample_simple_server_open(void)
{
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = 0;
    addrin.sin_port = htons(3371);

    xserver * server = xserver_new(PF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xserver));
    printf("server is created => %p\n", server);

    xint32 ret = xserver_listen(server);
    if(ret == xsuccess)
    {
        printf("server is listen\n");
    }
    else
    {
        printf("server is not listen\n");
    }

    server = xserver_rem(server);

    return 0;
}

static xint32 xexample_simple_server(void)
{
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = 0;
    addrin.sin_port = htons(3371);

    xserver * server = xserver_new(PF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xserver));
    printf("server is created => %p\n", server);
    server = xserver_rem(server);

    return 0;
}

static xint32 xexample_simple_nonblock_connect(void)
{
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrin.sin_port = htons(2000);
    char data[1024];
    char buffer[1024];

    xclient * client = xclient_new(AF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xclient));
    xclient_mask_add(client, xdescriptor_mask_nonblock);

    xint32 ret = xclient_connect(client);
    if(ret == xsuccess)
    {
        if(xclient_status(client) & xdescriptor_status_connect)
        {
            printf("succeed to xclient connect\n");
        }
        else if(xclient_status(client) & xdescriptor_status_connecting)
        {
            printf("succeed to xclient connect (connecting)\n");
        }
        xuint32 events = xclient_wait(client, xdescriptor_event_connect, 1, 0);
        if((events & xdescriptor_event_exception) == xdescriptor_event_void)
        {
            if(events & xdescriptor_event_connect)
            {
                printf("succeed to xclient connect (wait)\n");
            }
            else
            {
                if(events & xdescriptor_event_timeout)
                {
                    printf("fail to xclient wait connect (timeout)\n");
                }
            }
        }
        else
        {
            printf("client wait exception\n");
        }

        xint32 len = snprintf(data, 1024, "helloworld\n");
        xint64 n = xclient_write(client, data, len);
        if(n > 0)
        {
            printf("succeed to xclient write => %ld\n", n);
        }
        else if(n == 0)
        {
            printf("fail to xclient write (nonblock)\n");
        }
        else
        {
            printf("fail to xclient write (exception)\n");
        }
        xclient_nonblock_off(client);
        n = xclient_read(client, buffer, n);
        if(n > 0)
        {
            buffer[n] = 0;
            printf("succeed to xclient read => %lu => %s", n, buffer);
        }
        else if(n == 0)
        {
            printf("fail to xclient read (nonblock)\n");
        }
        else
        {
            printf("fail to xclient read (exception)\n");
        }
        ret = xclient_close(client);
        if(ret == xsuccess)
        {
            printf("succeed to xclient close\n");
        }
        else
        {
            printf("fail to xclient close\n");
        }
    }
    else
    {
        printf("fail to xclient connect\n");
    }

    xclient_rem(client);
    return 0;
}

static xint32 xexample_simple_client_with_ncat_nonblock_wait(void)
{
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrin.sin_port = htons(2000);
    char data[1024];
    char buffer[1024];

    xclient * client = xclient_new(AF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xclient));

    xint32 ret = xclient_connect(client);
    if(ret == xsuccess)
    {
        xclient_nonblock_on(client);
        printf("succeed to xclient connect\n");
        xint32 len = snprintf(data, 1024, "helloworld\n");
        xint64 n = xclient_write(client, data, len);
        if(n > 0)
        {
            printf("succeed to xclient write => %ld\n", n);
        }
        else if(n == 0)
        {
            printf("fail to xclient write (nonblock)\n");
        }
        else
        {
            printf("fail to xclient write (exception)\n");
        }
        xuint32 events = xclient_wait(client, xdescriptor_event_in, 1, 0);
        if((events & xdescriptor_event_exception) == xdescriptor_event_void)
        {
            if(events & xdescriptor_event_in)
            {
                n = xclient_read(client, buffer, n);
                if(n > 0)
                {
                    buffer[n] = 0;
                    printf("succeed to xclient read => %lu => %s", n, buffer);
                }
                else if(n == 0)
                {
                    printf("fail to xclient read (nonblock)\n");
                }
                else
                {
                    printf("fail to xclient read (exception)\n");
                }
            }
            else
            {
                if(events & xdescriptor_event_timeout)
                {
                    printf("fail to event wait\n");
                }
            }
        }
        else
        {
            printf("event wait exception\n");
        }

        ret = xclient_close(client);
        if(ret == xsuccess)
        {
            printf("succeed to xclient close\n");
        }
        else
        {
            printf("fail to xclient close\n");
        }
    }
    else
    {
        printf("fail to xclient connect\n");
    }

    xclient_rem(client);
    return 0;
}

static xint32 xexample_simple_client(void)
{
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrin.sin_port = htons(3306);

    xclient * client = xclient_new(AF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xclient));

    xint32 ret = xclient_connect(client);
    if(ret == xsuccess)
    {
        printf("succeed to xclient connect\n");
        ret = xclient_close(client);
        if(ret == xsuccess)
        {
            printf("succeed to xclient close\n");
        }
        else
        {
            printf("fail to xclient close\n");
        }
    }
    else
    {
        printf("fail to xclient connect\n");
    }

    xclient_rem(client);
    return 0;
}

static xint32 xexample_simple_client_with_ncat(void)
{
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrin.sin_port = htons(2000);
    char data[1024];
    char buffer[1024];

    xclient * client = xclient_new(AF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xclient));

    xint32 ret = xclient_connect(client);
    if(ret == xsuccess)
    {
        printf("succeed to xclient connect\n");
        xint32 len = snprintf(data, 1024, "helloworld\n");
        xint64 n = xclient_write(client, data, len);
        if(n > 0)
        {
            printf("succeed to xclient write => %ld\n", n);
        }
        else if(n == 0)
        {
            printf("fail to xclient write (nonblock)\n");
        }
        else
        {
            printf("fail to xclient write (exception)\n");
        }
        n = xclient_read(client, buffer, n);
        if(n > 0)
        {
            buffer[n] = 0;
            printf("succeed to xclient read => %lu => %s", n, buffer);
        }
        else if(n == 0)
        {
            printf("fail to xclient read (nonblock)\n");
        }
        else
        {
            printf("fail to xclient read (exception)\n");
        }
        ret = xclient_close(client);
        if(ret == xsuccess)
        {
            printf("succeed to xclient close\n");
        }
        else
        {
            printf("fail to xclient close\n");
        }
    }
    else
    {
        printf("fail to xclient connect\n");
    }

    xclient_rem(client);
    return 0;
}

static xint32 xexample_simple_client_with_ncat_nonblock(void)
{
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrin.sin_port = htons(2000);
    char data[1024];
    char buffer[1024];

    xclient * client = xclient_new(AF_INET, SOCK_STREAM, IPPROTO_TCP, &addrin, sizeof(struct sockaddr_in), sizeof(xclient));

    xint32 ret = xclient_connect(client);
    if(ret == xsuccess)
    {
        xclient_nonblock_on(client);
        printf("succeed to xclient connect\n");
        xint32 len = snprintf(data, 1024, "helloworld\n");
        xint64 n = xclient_write(client, data, len);
        if(n > 0)
        {
            printf("succeed to xclient write => %ld\n", n);
        }
        else if(n == 0)
        {
            printf("fail to xclient write (nonblock)\n");
        }
        else
        {
            printf("fail to xclient write (exception)\n");
        }
        xclient_nonblock_off(client);
        n = xclient_read(client, buffer, n);
        if(n > 0)
        {
            buffer[n] = 0;
            printf("succeed to xclient read => %lu => %s", n, buffer);
        }
        else if(n == 0)
        {
            printf("fail to xclient read (nonblock)\n");
        }
        else
        {
            printf("fail to xclient read (exception)\n");
        }
        ret = xclient_close(client);
        if(ret == xsuccess)
        {
            printf("succeed to xclient close\n");
        }
        else
        {
            printf("fail to xclient close\n");
        }
    }
    else
    {
        printf("fail to xclient connect\n");
    }

    xclient_rem(client);
    return 0;
}
