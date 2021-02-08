#include <stdio.h>

#include "io.h"

extern void xdescriptor_debug_print_event(xuint32 event)
{
    if(event == xdescriptor_event_void)
    {
        printf("xdescriptor event void\n");
    }
    else
    {
        if((event & xdescriptor_event_open) == xdescriptor_event_open)
        {
            printf("xdescriptor event open\n");
        }
        if((event & xdescriptor_event_in) == xdescriptor_event_in)
        {
            printf("xdescriptor event in\n");
        }
        if((event & xdescriptor_event_out) == xdescriptor_event_out)
        {
            printf("xdescriptor event out\n");
        }
        if((event & xdescriptor_event_close) == xdescriptor_event_close)
        {
            printf("xdescriptor event close\n");
        }
        if((event & xdescriptor_event_exception) == xdescriptor_event_exception)
        {
            printf("xdescriptor event exception\n");
        }
        if((event & xdescriptor_event_create) == xdescriptor_event_create)
        {
            printf("xdescriptor event create\n");
        }
        if((event & xdescriptor_event_bind) == xdescriptor_event_bind)
        {
            printf("xdescriptor event bind\n");
        }
        if((event & xdescriptor_event_connect) == xdescriptor_event_connect)
        {
            printf("xdescriptor event connect\n");
        }
        if((event & xdescriptor_event_listen) == xdescriptor_event_listen)
        {
            printf("xdescriptor event listen\n");
        }
        if((event & xdescriptor_event_shutdown_in) == xdescriptor_event_shutdown_in)
        {
            printf("xdescriptor event shutdown in\n");
        }
        if((event & xdescriptor_event_shutdown_out) == xdescriptor_event_shutdown_out)
        {
            printf("xdescriptor event shutdown out\n");
        }
        if((event & xdescriptor_event_shutdown_all) == xdescriptor_event_shutdown_all)
        {
            printf("xdescriptor event shutdown all\n");
        }
        if((event & xdescriptor_event_timeout) == xdescriptor_event_timeout)
        {
            printf("xdescriptor event timeout\n");
        }
        if((event & xdescriptor_event_connecting) == xdescriptor_event_connecting)
        {
            printf("xdescriptor event connecting\n");
        }
    }
}