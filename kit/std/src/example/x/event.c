#include <x/event.h>

static void example_internal_func(xeventengine * o)
{
    xeventenginecancel(o);
}

int main(int argc, char ** argv)
{
    xeventengine * engine = xeventenginenew();

    xeventengine_internal_func(engine, example_internal_func);

    return xeventenginerun(engine);
}