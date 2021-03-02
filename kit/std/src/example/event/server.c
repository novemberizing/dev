#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <x/server.h>
#include <x/event/engine.h>

static xint64 xsessionsubscriber_echo(xsession * session, xuint64 event, void * data, xint64 result);

int main(int argc, char ** argv)
{
    xeventengine * engine = xeventengine_new();

    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(3371);

    xserver * server = xservernew(AF_INET, SOCK_STREAM, IPPROTO_TCP, xaddressof(addr), sizeof(struct sockaddr_in), xsessionsubscriber_echo, sizeof(xserver));

    xeventengine_server_register(engine, server);
    
    return xeventengine_run(engine);


    return 0;
}

static xint64 xsessionsubscriber_echo(xsession * session, xuint64 event, void * data, xint64 result)
{
    // ECHO SERVER 의 스트리밍은 데이터 카피가 일어나지 않도록 하나의 INPUT & OUTPUT STREAM 을 합칠 수 있다.
    if(event == xsessioneventtype_in)
    {
    }
    else if(event == xsessioneventtype_out)
    {

    }
}