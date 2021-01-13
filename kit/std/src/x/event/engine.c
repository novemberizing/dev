#include "../event.h"

// int xeventengine_run(xeventengine * engine)
// {
//     xassertion(engine == xnil, "null pointer exception");
//     xassertion(engine->status != xeventengine_status_void, "already running exception");
//     engine->status = xeventengine_status_on;
//     // TODO: IMPLEMENT INITIALIZE
//     while((engine->status & xeventengine_status_cancel) == xfalse)
//     {
//     }
//     // TODO: IMPLEMENT DESTROY
//     engine->status &= (~xeventengine_status_on);
//     return xsuccess;
// }