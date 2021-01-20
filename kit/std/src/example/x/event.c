#include <signal.h>
#include <stdio.h>

#include <x/event.h>

static void example_internal_func(xeventengine * o)
{
    xeventenginecancel(o);
}

static void example_signal_interrupt_handler(xint32 category, xint32 no, xeventobj * target, void * parameter, xeventgenerator * generator, xeventengine * engine)
{
    printf("example => %d\n", category);
    printf("example => %d\n", no);
    printf("example => %p\n", engine);
    xeventenginecancel(engine);
}

int main(int argc, char ** argv)
{
    xeventengineon();
    
    xeventengine * engine = xeventenginenew();

    xeventengine_internal_func(engine, example_internal_func);

    int ret = xeventenginerun(engine);

    engine = xeventenginenew();

    xeventengine_signal_handler_set(engine, SIGINT, example_signal_interrupt_handler);

    xeventengine_signal_handler_set(engine, SIGINT, xnil);

    xeventengine_signal_handler_set(engine, SIGINT, example_signal_interrupt_handler);

    xeventengine_signal_handler_del(engine, SIGINT);

    xeventengine_signal_handler_set(engine, SIGINT, example_signal_interrupt_handler);

    // xeventengine_internal_func(engine, example_internal_func);

    // signal event handling

    return xeventenginerun(engine);
}