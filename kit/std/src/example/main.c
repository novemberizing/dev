#include <x/net.h>

/**
 * 사용자가 신경 쓸 이벤트는 IN/OUT/CLOSE 뿐이다.
 * 다만, 필요할 경우를 위해서 사용자가 설정할 수 있도록 하자.
 */

struct userclient
{
    xdescriptor * descriptor;
    void *        addr;
    xuint32       addrlen;
};

typedef xint32 (*xdescriptor_event_in_handler)(void *, xstream *);

int main(int argc, char ** argv)
{

    xclient * client = xclientnew(addr, addrlen);

    xint64 n = xclientsend(client, data, len);

    xint64 n = xclientrecv(client, buffer, size);

    xclientclose(client);
    xclientrem(client);

    xeventengine * engine = xeventengine_new();
    
    return 0;
}