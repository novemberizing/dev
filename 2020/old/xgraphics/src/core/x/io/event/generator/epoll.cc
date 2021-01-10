#include "epoll.hh"

namespace x
{
    namespace io
    {
        namespace event
        {
            namespace generator
            {
                epoll::epoll(x::event::engine & engine)
                :   x::event::generator(x::event::type::io, engine),
                    __descriptor(x::invalid),
                    __timeout(1),
                    __objects(),
                    __newbies(),
                    __max(0),
                    __events(nullptr)
                {

                }

                epoll::~epoll()
                {
                    if(__descriptor != x::invalid)
                    {
                        ::close(__descriptor);
                        __descriptor = x::invalid;
                    }
                    __timeout = 0;
                    __objects.clear();
                    __newbies.clear();
                    __max = 0;
                    if(__events)
                    {
                        ::free(__events);
                        __events = nullptr;
                    }
                }

                void epoll::add(x::event::object * _o)
                {
                    x::descriptor * o = x::event::object::cast<x::descriptor>(_o, x::event::type::io);

                    assertion(o == nullptr);
                    assertion(__objects.exist(o));

                    if(__descriptor == x::invalid)
                    {
                        __objects.add(o);
                        __newbies.push(o);
                    }
                    else
                    {
                        __objects.add(o);

                        if(o->value() >= 0)
                        {
                            struct epoll_event event;
                            event.data.ptr = o;
                            event.events = (EPOLLRDHUP | EPOLLPRI | EPOLLHUP | EPOLLERR | EPOLLET | EPOLLONESHOT);
                            if(o->interest(x::event::io::type::read))
                            {
                                event.events |= EPOLLIN;
                            }
                            if(o->interest(x::event::io::type::write))
                            {
                                event.events |= EPOLLOUT;
                            }
                            if(epoll_ctl(__descriptor, EPOLL_CTL_ADD, o->value(), &event) == x::success)
                            {
                                o->wait(x::event::io::type::close);
                                if(event.events & EPOLLIN)
                                {
                                    o->wait(x::event::io::type::read);
                                }
                                if(event.events & EPOLLOUT)
                                {
                                    o->wait(x::event::io::type::write);
                                }
                            }
                            else
                            {
                                exceptional();
                            }
                        }
                        else
                        {
                            __newbies.push(o);
                        }
                    }
                }

                void epoll::mod(x::event::object * _o)
                {
                    x::descriptor * o = x::event::object::cast<x::descriptor>(_o, x::event::type::io);

                    assertion(o == nullptr);

                    if(__descriptor == x::invalid)
                    {
                        __newbies.push(o);
                    }
                    else
                    {
                        if(o->value() >= 0)
                        {
                            struct epoll_event event;
                            event.data.ptr = o;
                            event.events = (EPOLLRDHUP | EPOLLPRI | EPOLLHUP | EPOLLERR | EPOLLET | EPOLLONESHOT);
                            if(o->interest(x::event::io::type::read))
                            {
                                event.events |= EPOLLIN;
                            }
                            if(o->interest(x::event::io::type::write))
                            {
                                event.events |= EPOLLOUT;
                            }
                            if(epoll_ctl(__descriptor, EPOLL_CTL_MOD, o->value(), &event) == x::success)
                            {
                                o->wait(x::event::io::type::close);
                                if(event.events & EPOLLIN)
                                {
                                    o->wait(x::event::io::type::read);
                                }
                                if(event.events & EPOLLOUT)
                                {
                                    o->wait(x::event::io::type::write);
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

                void epoll::del(x::event::object * _o)
                {
                    x::descriptor * o = x::event::object::cast<x::descriptor>(_o, x::event::type::io);

                    assertion(o == nullptr);

                    if(__descriptor == x::invalid)
                    {
                        __newbies.push(o);
                    }
                    else
                    {
                        if(o->value() >= 0)
                        {
                            struct epoll_event event;
                            event.data.ptr = o;
                            event.events = (EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLPRI | EPOLLHUP | EPOLLERR | EPOLLET | EPOLLONESHOT);
                            if(epoll_ctl(__descriptor, EPOLL_CTL_DEL, o->value(), &event) == x::success)
                            {
                                o->wait(x::event::io::type::none);
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

                void epoll::initialize()
                {
                    if(__descriptor == invalid)
                    {
                        __descriptor = ::epoll_create(65536);
                    }

                    while(__newbies.size() > 0)
                    {
                        x::descriptor * o = __newbies.pop();
                        if(o->value() == x::invalid)
                        {
                            o->open(true);
                        }

                        if(o->value() >= 0)
                        {
                            struct epoll_event event;
                            event.data.ptr = o;
                            event.events = (EPOLLRDHUP | EPOLLPRI | EPOLLHUP | EPOLLERR | EPOLLET | EPOLLONESHOT);
                            if(o->interest(x::event::io::type::read))
                            {
                                event.events |= EPOLLIN;
                            }
                            if(o->interest(x::event::io::type::write))
                            {
                                event.events |= EPOLLOUT;
                            }
                            if(epoll_ctl(__descriptor, EPOLL_CTL_ADD, o->value(), &event) == x::success)
                            {
                                o->wait(x::event::io::type::close);
                                if(event.events & EPOLLIN)
                                {
                                    o->wait(x::event::io::type::read);
                                }
                                if(event.events & EPOLLOUT)
                                {
                                    o->wait(x::event::io::type::write);
                                }
                            }
                            else
                            {
                                exceptional();
                            }
                        }
                        else
                        {
                            __newbies.push(o);
                        }
                    }
                }

                void epoll::terminate()
                {
                    if(__descriptor == invalid)
                    {
                        ::close(__descriptor);
                        __descriptor = invalid;
                    }
                    // TODO: IMPLEMENT THIS
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
                            if(__events)
                            {
                                ::free(__events);
                                __events = nullptr;
                            }
                        }
                    }
                    if(__max > 0)
                    {
                        x::int32 nfds = ::epoll_wait(__descriptor, __events, __max, __timeout);
                        if(nfds >= 0)
                        {
                            for(x::int32 i = 0; i < nfds; i++)
                            {

                                x::descriptor * o = reinterpret_cast<x::descriptor *>(__events[i].data.ptr);
                                if(__events[i].events & (EPOLLRDHUP | EPOLLPRI | EPOLLERR | EPOLLHUP))
                                {
                                    __engine->add(x::event(x::event::io::type::close, o, __engine, this));
                                    continue;
                                }
                                if(__events[i].events & EPOLLOUT)
                                {
                                    __engine->add(x::event(x::event::io::type::write, o, __engine, this));
                                }
                                if(__events[i].events & EPOLLIN)
                                {
                                    __engine->add(x::event(x::event::io::type::read, o, __engine, this));
                                }
                            }
                        }
                        else
                        {
                            // TODO
                            // exceptional();
                        }
                    }
                }
            }
        }
    }
}
