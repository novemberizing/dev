#include "epoll.hh"

namespace x
{
    namespace io
    {
        namespace event
        {
            namespace generator
            {

                epoll::epoll()
                :   x::event::generator(x::event::generator::type::io),
                    __descriptor(invalid),
                    __timeout(1),
                    __objects(),
                    __max(0),
                    __events(nullptr)
                {
                }

                epoll::epoll(const epoll & o)
                :   x::event::generator(o),
                    __descriptor(o.__descriptor),
                    __timeout(o.__timeout),
                    __objects(o.__objects),
                    __max(0),
                    __events(nullptr)
                {
                }

                epoll::epoll(epoll && o)
                :   x::event::generator(x::move(o)),
                    __descriptor(o.__descriptor),
                    __timeout(o.__timeout),
                    __objects(x::move(o.__objects)),
                    __max(o.__max),
                    __events(o.__events)
                {
                    o.__descriptor = invalid;
                    o.__timeout = 1;
                    o.__max = 0;
                    o.__events = nullptr;
                }

                epoll::~epoll()
                {
                }

                epoll & epoll::operator=(epoll && o) noexcept
                {
                    if(&o != this)
                    {
                        if(__events)
                        {
                            ::free(__events);
                        }
                        x::event::generator::operator=(x::move(o));
                        __descriptor = o.__descriptor;
                        __timeout = o.__timeout;
                        __objects = x::move(o.__objects);
                        __max = o.__max;
                        __events = o.__events;

                         o.__descriptor = invalid;
                         o.__timeout = 0;
                         o.__max = 0;
                         o.__events = nullptr;

                    }
                    return *this;
                }

                epoll & epoll::operator=(const epoll & o)
                {
                    if(&o != this)
                    {
                        x::event::generator::operator=(o);
                        __descriptor = o.__descriptor;
                        __timeout = o.__timeout;
                        __objects = o.__objects;
                    }
                    return *this;
                }

                void epoll::cycle()
                {
                    if(__max != __objects.size())
                    {
                        __max = __objects.size();
                        if(__max > 0)
                        {
                            if(__events)
                            {
                                __events = reinterpret_cast<struct epoll_event *>(::realloc(__events, __max * sizeof(struct epoll_event)));
                            }
                            else
                            {
                                __events = reinterpret_cast<struct epoll_event *>(::malloc(__max * sizeof(struct epoll_event)));
                            }
                        }
                        else
                        {
                            ::free(__events);
                            __events = nullptr;
                        }
                    }
                    if(__max > 0)
                    {
                        x::int32 nfds = ::epoll_wait(__descriptor, __events, __max, __timeout);
                        if(nfds >= 0)
                        {
                            for(x::int32 i = 0; i < nfds; i++)
                            {
                                x::event::object * o = reinterpret_cast<x::event::object *>(__events[i].data.ptr);
                                if(__events[i].events & (EPOLLRDHUP | EPOLLPRI | EPOLLERR | EPOLLHUP))
                                {
                                    __engine->add(x::event(x::event::type::close, o, __engine));
                                    continue;
                                }
                                if(__events[i].events & EPOLLOUT)
                                {
                                    __engine->add(x::event(x::event::type::write, o, __engine));
                                }
                                if(__events[i].events & EPOLLIN)
                                {
                                    __engine->add(x::event(x::event::type::read, o, __engine));
                                }
                            }
                        }
                        else
                        {
                            // TODO: ERROR HANDLING
                        }
                    }
                }

                void epoll::init()
                {
                    if(__descriptor == invalid)
                    {
                        __descriptor = ::epoll_create(65536);
                    }
                    while(__newbies.size() > 0)
                    {
                        x::event::object * o = __newbies.pop();
                        struct epoll_event event;
                        event.data.ptr = o;
                        event.events = (EPOLLRDHUP | EPOLLPRI | EPOLLHUP | EPOLLERR | EPOLLET | EPOLLONESHOT);
                        if(o->need(x::event::type::read))
                        {
                            event.events |= EPOLLIN;
                        }
                        if(o->need(x::event::type::write))
                        {
                            event.events |= EPOLLOUT;
                        }
                        if(epoll_ctl(__descriptor, EPOLL_CTL_ADD, o->id(), &event) == success)
                        {
                            if(event.events & EPOLLIN)
                            {
                                o->off(x::event::type::read, __engine, this);
                            }
                            if(event.events & EPOLLOUT)
                            {
                                o->off(x::event::type::write, __engine, this);
                            }
                        }
                        else
                        {
                            // TODO: CASE BY CASE FOR ERROR
                            exceptional();
                        }
                    }
                }

                void epoll::term()
                {
                    if(__descriptor == invalid)
                    {
                        ::close(__descriptor);
                        __descriptor = invalid;
                    }
                }

                void epoll::mod(x::event::object * o)
                {
                    if(o != nullptr)
                    {
                        if(__engine != nullptr)
                        {
                            if(o->id() >= 0)
                            {
                                struct epoll_event event;
                                event.data.ptr = o;
                                event.events = (EPOLLRDHUP | EPOLLPRI | EPOLLHUP | EPOLLERR | EPOLLET | EPOLLONESHOT);
                                if(o->need(x::event::type::read))
                                {
                                    event.events |= EPOLLIN;
                                }
                                if(o->need(x::event::type::write))
                                {
                                    event.events |= EPOLLOUT;
                                }
                                if(epoll_ctl(__descriptor, EPOLL_CTL_MOD, o->id(), &event) == success)
                                {
                                    if(event.events & EPOLLIN)
                                    {
                                        o->off(x::event::type::read, __engine, this);
                                    }
                                    if(event.events & EPOLLOUT)
                                    {
                                        o->off(x::event::type::write, __engine, this);
                                    }
                                }
                                else
                                {
                                    // TODO: CASE BY CASE FOR ERROR
                                    exceptional();
                                }
                            }
                        }
                    }
                }

                void epoll::add(x::event::object * o)
                {
                    if(o != nullptr)
                    {
                        if(__engine != nullptr)
                        {
                            if(o->engine() == nullptr)
                            {
                                if(!__objects.exist(o))
                                {
                                    __objects.add(o);
                                    o->engine(__engine);
                                    if(o->id() >= 0)
                                    {
                                        __nonblock(o->id());
                                        o->off(x::event::type::read, __engine, this);
                                        o->off(x::event::type::write, __engine, this);
                                        if(__engine->is(x::event::engine::status::running))
                                        {
                                            struct epoll_event event;
                                            event.data.ptr = o;
                                            event.events = (EPOLLRDHUP | EPOLLPRI | EPOLLHUP | EPOLLERR | EPOLLET | EPOLLONESHOT);
                                            if(o->need(x::event::type::read))
                                            {
                                                event.events |= EPOLLIN;
                                            }
                                            if(o->need(x::event::type::write))
                                            {
                                                event.events |= EPOLLOUT;
                                            }
                                            if(epoll_ctl(__descriptor, EPOLL_CTL_ADD, o->id(), &event) == success)
                                            {
                                                if(event.events & EPOLLIN)
                                                {
                                                    o->off(x::event::type::read, __engine, this);
                                                }
                                                if(event.events & EPOLLOUT)
                                                {
                                                    o->off(x::event::type::write, __engine, this);
                                                }
                                            }
                                            else
                                            {
                                                // TODO: CASE BY CASE FOR ERROR
                                                exceptional();
                                            }
                                        }
                                        else
                                        {
                                            __newbies.push(o);
                                        }
                                    }
                                    else
                                    {
                                        exceptional();
                                    }
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                            else
                            {
                                exceptional();
                            }
                        }
                        else
                        {
                            exceptional();
                        }
                    }
                    else
                    {
                        exceptional();
                    }
                }
            }
        }
    }
}
