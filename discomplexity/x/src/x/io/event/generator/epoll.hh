#ifndef   __X_IO_EVENT_GENERATOR__EPOLL__HH__
#define   __X_IO_EVENT_GENERATOR__EPOLL__HH__

#include <x/event.hh>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <stdlib.h>

namespace x
{
    namespace io
    {
        namespace event
        {
            namespace generator
            {
                class epoll : public x::event::generator
                {
                protected:  x::int32 __descriptor;
                protected:  x::int32 __timeout;
                protected:  x::set<x::event::object *> __objects;
                protected:  x::queue<x::event::object *> __newbies;
                // attach descriptor object ...
                protected:  x::int32 __max;
                protected:  struct epoll_event * __events;
                public:     void add(x::event::object * o) override;
                public:     void mod(x::event::object * o) override;
                public:     void init() override;
                public:     void term() override;
                public:     void cycle() override;
                public:     epoll & operator=(const epoll & o);
                public:     epoll & operator=(epoll && o) noexcept;
                public:     epoll();
                public:     epoll(const epoll & o);
                public:     epoll(epoll && o);
                public:     ~epoll() override;
                };
            }
        }
    }
}

#endif // __X_IO_EVENT_GENERATOR__EPOLL__HH__
