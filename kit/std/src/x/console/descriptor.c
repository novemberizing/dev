#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../thread.h"
#include "descriptor.h"

static inline xint64 xconsoledescriptorprocessor_console_input_open(xconsoledescriptor * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        if((o->status & xdescriptorstatus_open) == xdescriptorstatus_void)
        {
            o->handle.f = STDOUT_FILENO;
            o->on(o, xdescriptoreventtype_open, xnil, 0);

            return xsuccess;
        }
    }
    return xsuccess;
}

static inline xint64 xconsoledescriptorprocessor_console_input_in(xconsoledescriptor * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        // TODO: 적절한 TCP 버그 크기를 구한다.
        xstreamadjust(o->stream, xfalse);
        xstreamcapacity_set(o->stream, xstreamcapacity_get(o->stream) + 8192);
        xint64 n = xdescriptorread((xdescriptor *) o, xstreamback(o->stream), xstreamremain(o->stream));
        if(n > 0)
        {
            xstreamsize_set(o->stream, xstreamsize_get(o->stream) + n);
        }
        return n;
    }
    return xfail;
}

static xint64 xconsoledescriptorprocessor_console_input_out(xconsoledescriptor * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        // TODO: 적절한 TCP 버그 크기를 구한다.
        xstreamcapacity(o->stream, 8192);
        xint64 n = xdescriptorwrite((xdescriptor *) o, xstreamfront(o->stream), xstreamlen(o->stream));
        if(n > 0)
        {
            xstreampos_set(o->stream, xstreampos_get(o->stream) + n);
            xstreamadjust(o->stream, xfalse);
        }
        return n;
    }
    return xfail;
}

static xint64 xconsoledescriptorprocessor_console_input_close(xconsoledescriptor * o)
{
    xassertion(o->event.queue, "");

    if((o->status & xdescriptorstatus_close) == xdescriptorstatus_void)
    {
        o->status |= xdescriptorstatus_close;
    }
    
    return xsuccess;
}

static xint64 xconsoledescriptorprocessor_console_input_exception(xconsoledescriptor * o)
{
    return xconsoledescriptorprocessor_console_input_close(o);
}

static xint64 xconsoledescriptorprocessor_console_input_rem(xconsoledescriptor * o)
{
    return xconsoledescriptorprocessor_console_input_close(o);
}

static xint64 xconsoledescriptorprocessor_input(xconsoledescriptor * descriptor, xuint32 event, void * data)
{
    xassertion(descriptor == xnil, "");
    switch(event)
    {
        case xdescriptoreventtype_open:         return xconsoledescriptorprocessor_console_input_open(descriptor);
        case xdescriptoreventtype_in:           return xconsoledescriptorprocessor_console_input_in(descriptor);
        case xdescriptoreventtype_out:          return xconsoledescriptorprocessor_console_input_out(descriptor);
        case xdescriptoreventtype_close:        return xconsoledescriptorprocessor_console_input_close(descriptor);
        case xdescriptoreventtype_exception:    return xconsoledescriptorprocessor_console_input_exception(descriptor);
        case xdescriptoreventtype_rem:          return xconsoledescriptorprocessor_console_input_rem(descriptor);
    }
    xassertion(xtrue, "");
}
static xint32 xconsoledescriptorcheck_input(xconsoledescriptor * o, xuint32 event)
{
    if(event == xdescriptoreventtype_out)
    {
        // INPUT STREAM 에는 WRITE 할 것이 존재하지 않는다.
        return xfalse;
    }

    xassertion(event != xdescriptoreventtype_out, "");
}

static xint64 xconsoledescriptorsubscriber_input(xconsoledescriptor * o, xuint32 event, void * data, xint64 val)
{
    switch(event)
    {
        case xdescriptoreventtype_in:           return o->console->on(o->console, event, o->stream, val);
        case xdescriptoreventtype_out:          return o->console->on(o->console, event, xnil, 0);
        case xdescriptoreventtype_exception:    return o->console->on(o->console, event, xaddressof(o->exception), 0);
        case xdescriptoreventtype_close:        return o->console->on(o->console, event, xnil, 0);
        case xdescriptoreventtype_rem:          return o->console->on(o->console, event, xnil, 0);
        case xdescriptoreventtype_register:     return o->console->on(o->console, event, xnil, val);
    }

    return o->console->on(o->console, event, data, val);
}

static void xconsoledescriptoreventhandler_input(xconsoledescriptorevent * event)
{
    // xdescriptorevent_process_on
}

static xconsoledescriptor * xconsoledescriptor_output_rem(xconsoledescriptor * descriptor);
static xint64 xconsoledescriptorprocessor_output(xconsoledescriptor * descriptor, xuint32 event, void * data);
static xint32 xconsoledescriptorcheck_output(xconsoledescriptor * descriptor, xuint32 event);
static xint64 xconsoledescriptorsubscriber_output(xconsoledescriptor * descriptor, xuint32 event, void * data, xint64 val);
static void xconsoledescriptoreventhandler_output(xconsoledescriptorevent * event);


static xconsoledescriptor * xconsoledescriptor_input_rem(xconsoledescriptor * descriptor)
{
    xassertion(descriptor->subscription, "");
    xassertion(descriptor->event.queue, "");
    xassertion(xstreamlen(descriptor->stream) > 0, "");

    descriptor->stream = xstreamrem(descriptor->stream);
    descriptor->sync = xsyncrem(descriptor->sync);

    return descriptor;
}

static xconsoledescriptor consoledescriptor_in = {
    /** INHERITED EVENT TARGET */
    xconsoledescriptor_input_rem,
    xnil,
    xnil,
    xdescriptormask_void,
    xdescriptorstatus_void,
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle_invalid,
    xconsoledescriptorprocessor_input,
    xconsoledescriptorcheck_input,
    xconsoledescriptorsubscriber_input,
    xconsoledescriptorevent_init(xconsoledescriptoreventhandler_input, xnil),
    xexception_void,
    /** CONSOLE DESCRIPTOR MEMBER */
    xnil,
    xnil
};

static xconsoledescriptor consoledescriptor_out = {
    /** INHERITED EVENT TARGET */
    xconsoledescriptor_output_rem,
    xnil,
    xnil,
    xdescriptormask_void,
    xdescriptorstatus_void,
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle_invalid,
    xconsoledescriptorprocessor_output,
    xconsoledescriptorcheck_output,
    xconsoledescriptorsubscriber_output,
    xconsoledescriptorevent_init(xconsoledescriptoreventhandler_output, xnil),
    xexception_void,
    /** CONSOLE DESCRIPTOR MEMBER */
    xnil,
    xnil
};

static xconsoledescriptor * consoledescriptorsingleton_in = xnil;
static xconsoledescriptor * consoledescriptorsingleton_out = xnil;

extern xconsoledescriptor * xconsoledescriptorin_get(void)
{
    if(consoledescriptorsingleton_in == xnil)
    {
        consoledescriptorsingleton_in = xaddressof(consoledescriptor_in);
        consoledescriptorsingleton_in->handle.f = STDIN_FILENO;
        consoledescriptorsingleton_in->event.descriptor = xaddressof(consoledescriptor_in);
    }

    return consoledescriptorsingleton_in;
}

extern xconsoledescriptor * consoledescriptorout_get(void)
{
    if(consoledescriptorsingleton_out == xnil)
    {
        consoledescriptorsingleton_out = xaddressof(consoledescriptor_out);
        consoledescriptorsingleton_out->handle.f = STDIN_FILENO;
        consoledescriptorsingleton_out->event.descriptor = xaddressof(consoledescriptor_out);
    }

    return consoledescriptorsingleton_out;
}
