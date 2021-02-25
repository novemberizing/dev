#include <x/event/engine.h>
#include <x/console.h>

int main(int argc, char ** argv)
{
    xeventengine * engine = xeventengine_new();

    xeventengine_console_descriptor_register(engine, xconsoledescriptorout_get());
    
    return xeventengine_run(engine);
}
