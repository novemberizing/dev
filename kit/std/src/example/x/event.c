#include <signal.h>

#include <x/event.h>

static void example_internal_func(xeventengine * o)
{
    xeventenginecancel(o);
}

static void example_signal_handler(void)
{
    // xeventenginecancel(o);
}

int main(int argc, char ** argv)
{
    xeventengine * engine = xeventenginenew();

    xeventengine_internal_func(engine, example_internal_func);

    int ret = xeventenginerun(engine);

    engine = xeventenginenew();

    xeventengine_signal_handler_set(engine, SIGINT, example_signal_handler);

    xeventengine_signal_handler_set(engine, SIGINT, xnil);

    xeventengine_signal_handler_set(engine, SIGINT, example_signal_handler);

    xeventengine_signal_handler_del(engine, SIGINT);

    xeventengine_signal_handler_set(engine, SIGINT, example_signal_handler);

    // xeventengine_internal_func(engine, example_internal_func);

    // signal event handling

    return xeventenginerun(engine);
}