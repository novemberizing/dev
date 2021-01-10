#include <stdio.h>

struct xeventengine;

struct xeventengine
{

};

extern xeventengine * xevent_engine_new();

int main(int argc, char ** argv)
{
    xeventengine * engine = xevent_engine_new();

    xevent_engine_run(engine);
    return 0;
}

xeventengine * xevent_engine_new()
{
    return 0;
}