#ifndef   __X__IO_EVENT_GENERATOR__EPOLL__HH__
#define   __X__IO_EVENT_GENERATOR__EPOLL__HH__

#include <x/event.hh>
#include <x/descriptor.hh>

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
                protected:  x::set<x::descriptor *> __objects;
                protected:  x::queue<x::descriptor *> __newbies;
                protected:  x::int32 __max;
                protected:  struct epoll_event * __events;
                public:     void add(x::event::object * o) override;
                public:     void mod(x::event::object * o) override;
                public:     void del(x::event::object * o) override;
                public:     void cycle() override;
                public:     void initialize() override;
                public:     void terminate() override;
                public:     epoll & operator=(const epoll & o) = delete;
                public:     epoll & operator=(epoll && o) noexcept = delete;
                public:     epoll(x::event::engine & engine);
                public:     epoll() = delete;
                public:     epoll(const epoll & o) = delete;
                public:     epoll(epoll && o) noexcept = delete;
                public:     ~epoll() override;
                };
            }
        }
    }
}

#endif // __X__IO_EVENT_GENERATOR__EPOLL__HH__
