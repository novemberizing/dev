/**
 * ncat -l 2000 -k -c 'xargs -n1 echo'
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include <x/std.h>
#include <x/client.h>

static xint32 xexample_simple_client(void);
static xint32 xexample_simple_client_with_ncat(void);
static xint32 xexample_simple_client_with_ncat_nonblock(void);
static xint32 xexample_simple_client_with_ncat_nonblock_wait(void);

int main(int argc, char ** argv)
{
    xexample_simple_client();
    xexample_simple_client_with_ncat();
    xexample_simple_client_with_ncat_nonblock();

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
