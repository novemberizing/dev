#include "event.h"


int main(int argc, char ** argv)
{
    xeventengine engine = xeventengine_init();

    // xeventengine_plug_generator(xeventgenerator_io_new());
    // xeventengine_plug_generator(xeventgenerator_signal_new());
    // xeventengine_plug_generator(xeventgenerator_time_new());

    return xeventengine_run(&engine);
}