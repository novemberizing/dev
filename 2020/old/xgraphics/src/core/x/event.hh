#ifndef   __X__EVENTH__HH__
#define   __X__EVENTH__HH__

#include <x/core.hh>
#include <x/queue.hh>
#include <x/map.hh>
#include <x/reference.hh>

namespace x
{
    class event
    {
    public:     class type
                {
                public:     static const x::uint32 none = 0;
                public:     static const x::uint32 io   = 1;
                };
    public:     class io
                {
                public:     class type
                            {
                            public:     static const x::uint32 none  = 0x00000000U << 0U;
                            public:     static const x::uint32 read  = 0x00000001U << 0U;
                            public:     static const x::uint32 write = 0x00000001U << 1U;
                            public:     static const x::uint32 close = 0x00000001U << 2U;
                            };
                };
    public:     class engine;
    public:     class generator;
    public:     class object
                {
                public:     template <typename T = x::event::object>
                            static T * cast(x::event::object * o, x::uint32 type)
                            {
                                return o ? static_cast<T *>(o->safe(type)) : nullptr;
                            }
                protected:  x::event::engine * __engine;
                public:     virtual void engine(x::event::engine * o)
                            {
                                if(__engine)
                                {
                                    assertion(o != nullptr);
                                }
                                __engine = o;
                            }
                public:     virtual x::event::object * safe(x::uint32 type)
                            {
                                return this;
                            }
                public:     virtual void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) = 0;
                public:     x::event::object & operator=(const x::event::object & o)
                            {
                                if(&o != this)
                                {
                                    __engine = o.__engine;
                                }
                                return *this;
                            }
                public:     x::event::object & operator=(x::event::object && o) noexcept
                            {
                                if(&o != this)
                                {
                                    __engine = o.__engine;

                                    o.__engine = nullptr;
                                }
                                return *this;
                            }
                public:     object()
                            :   __engine(nullptr)
                            {
                            }
                public:     object(const x::event::object & o)
                            :   __engine(o.__engine)
                            {
                            }
                public:     object(x::event::object && o) noexcept
                            :   __engine(o.__engine)
                            {
                                o.__engine = nullptr;
                            }
                public:     virtual ~object()
                            {
                                __engine = nullptr;
                            }
                };
    public:     class processor
                {
                protected:  x::queue<x::event> __queue;
                public:     virtual void cycle()
                            {
                                x::uint64 total = __queue.size();
                                for(x::uint64 i = 0; i < total && !__queue.empty(); i++)
                                {
                                    x::event event = x::move(__queue.pop());
                                    event.on();
                                }
                            }
                public:     virtual void add(const x::event & o)
                            {
                                __queue.push(o);
                            }
                public:     virtual void add(x::event && o)
                            {
                                __queue.push(x::move(o));
                            }
                public:     x::event::processor & operator=(const x::event::processor & o)
                            {
                                return *this;
                            }
                public:     x::event::processor & operator=(x::event::processor && o) noexcept
                            {
                                return *this;
                            }
                public:     processor()
                            :   __queue()
                            {
                            }
                public:     processor(const x::event::processor & o)
                            :   __queue()
                            {
                            }
                public:     processor(x::event::processor && o) noexcept
                            :   __queue()
                            {
                            }
                public:     virtual ~processor()
                            {
                            }
                };
    public:     class generator
                {
                public:     typedef x::event::generator * pointer;  // TODO REMOVE THIS
                protected:  x::uint32 __type;
                protected:  x::event::engine * __engine;
                public:     inline x::event::engine * engine()
                            {
                                return __engine;
                            }
                public:     inline x::uint32 type() const
                            {
                                return __type;
                            }
                public:     virtual void add(x::event::object * o) = 0;
                public:     virtual void mod(x::event::object * o) = 0;
                public:     virtual void del(x::event::object * o) = 0;
                public:     virtual void cycle() = 0;
                public:     virtual void initialize()
                            {
                            }
                public:     virtual void terminate()
                            {
                            }
                public:     x::event::generator & operator=(const x::event::generator & o) = delete;
                public:     x::event::generator & operator=(x::event::generator && o) noexcept = delete;
                protected:  generator(x::uint32 type, x::event::engine & engine)
                            :   __type(type),
                                __engine(&engine)
                            {
                            }
                public:     generator() = delete;
                public:     generator(const x::event::generator & o) = delete;
                public:     generator(x::event::generator && o) noexcept = delete;
                public:     virtual ~generator()
                            {
                                __type = x::event::type::none;
                            }
                };
    public:     class engine : public x::event::processor
                {
                public:     class status
                            {
                            public:     static const x::uint32 none       = 0x00000000U <<  0U;
                            public:     static const x::uint32 cancelling = 0x00000001U <<  0U;
                            public:     static const x::uint32 running    = 0x00000001U <<  1U;
                            };
                protected:  x::map<x::uint32, x::reference<x::event::generator *> > __generators;
                protected:  x::uint32 __status;
                public:     virtual void initialize()
                            {
                                if(__status == x::event::engine::status::none)
                                {
                                    __generators.each([](const x::uint32 & type, x::reference<x::event::generator *> & reference){
                                        if(reference.exist())
                                        {
                                            x::event::generator * generator = reference.get();
                                            if(generator)
                                            {
                                                generator->initialize();
                                            }
                                        }
                                    });
                                    __status = x::event::engine::status::running;
                                }
                            }
                public:     virtual void terminate()
                            {
                                if(__status == x::event::engine::status::running)
                                {
                                    __generators.each([](const x::uint32 & type, x::reference<x::event::generator *> & reference){
                                        if(reference.exist())
                                        {
                                            x::event::generator * generator = reference.get();
                                            if(generator)
                                            {
                                                generator->terminate();
                                            }
                                        }
                                    });
                                    __status = x::event::engine::status::none;
                                }
                            }
                public:     virtual void add(x::uint32 type, x::event::object & o)
                            {
                                add(type, &o);
                            }
                public:     virtual void add(x::uint32 type, x::event::object * o)
                            {
                                if(o)
                                {
                                    x::reference<x::event::generator *> reference = __generators[type];
                                    assertion(!reference.exist());

                                    x::event::generator * generator = reference.get();
                                    generator->add(o);
                                    o->engine(this);
                                }
                            }
                public:     virtual void mod(x::uint32 type, x::event::object * o)
                            {
                                if(o)
                                {
                                    x::reference<x::event::generator *> reference = __generators[type];
                                    assertion(!reference.exist());

                                    x::event::generator * generator = reference.get();
                                    generator->mod(o);
                                }
                            }
                public:     virtual void add(x::event::generator * o)
                            {
                                if(o)
                                {
                                    add(o->type(), o);
                                }
                            }
                public:     virtual void add(x::uint32 type, x::event::generator * o)
                            {
                                if(o)
                                {
                                    assertion(__generators.exist(type));

                                    __generators.put(type, x::reference(o));
                                }
                            }
                public:     void add(const x::event & o) override
                            {
                                x::event::processor::add(o);
                            }
                public:     void add(x::event && o) override
                            {
                                x::event::processor::add(x::move(o));
                            }
                public:     virtual int run()
                            {
                                if(__status == x::event::engine::status::none)
                                {
                                    initialize();
                                    while((__status & x::event::engine::status::cancelling) != x::event::engine::status::cancelling)
                                    {
                                        cycle();
                                    }
                                    terminate();
                                }
                            }
                public:     void cycle() override
                            {
                                __generators.each([](const x::uint32 & type, x::reference<x::event::generator *> & reference){
                                    if(reference.exist())
                                    {
                                        x::event::generator * generator = reference.get();
                                        if(generator)
                                        {
                                            generator->cycle();
                                        }
                                    }
                                });
                                x::event::processor::cycle();
                            }
                public:     x::event::engine & operator=(const x::event::engine & o)
                            {
                                if(&o != this)
                                {
                                    __generators.each([](const x::uint32 & type, x::reference<x::event::generator *> & reference) {
                                        reference.release([](x::event::generator::pointer & o){
                                            if(o)
                                            {
                                                delete o;
                                                o = nullptr;
                                            }
                                        });
                                    });
                                    __generators.clear();

                                    x::event::processor::operator=(o),
                                    __generators = o.__generators;
                                    __status = o.__status;

                                    __generators.each([](const x::uint32 & type, x::reference<x::event::generator *> & reference){
                                        reference.increase();
                                    });
                                }
                                return *this;
                            }
                public:     x::event::engine & operator=(x::event::engine && o) noexcept
                            {
                                if(&o != this)
                                {
                                    x::event::processor::operator=(x::move(o));
                                    __generators = x::move(o.__generators);
                                    __status = o.__status;

                                    o.__status = x::event::engine::status::none;
                                }
                                return *this;
                            }
                public:     engine()
                            :   x::event::processor(),
                                __generators(),
                                __status(x::event::engine::status::none)
                            {
                            }
                public:     engine(const x::event::engine & o)
                            :   x::event::processor(o),
                                __generators(o.__generators),
                                __status(o.__status)
                            {
                                __generators.each([](const x::uint32 & type, x::reference<x::event::generator *> & reference){
                                    reference.increase();
                                });
                            }
                public:     engine(x::event::engine && o) noexcept
                            :   x::event::processor(x::move(o)),
                                __generators(x::move(o.__generators)),
                                __status(o.__status)
                            {
                                o.__status = x::event::engine::status::none;
                            }
                public:     ~engine() override
                            {
                                __generators.each([](const x::uint32 & type, x::reference<x::event::generator *> & reference) {
                                    reference.release([](x::event::generator::pointer & o){
                                        if(o)
                                        {
                                            delete o;
                                            o = nullptr;
                                        }
                                    });
                                });
                                __generators.clear();
                            }
                };
    protected:  x::uint32 __id;
    protected:  x::event::object * __object;
    protected:  x::event::engine * __engine;
    protected:  x::event::generator * __generator;
    public:     virtual void on()
                {
                    if(__object)
                    {
                        __object->on(__id, __engine, __generator);
                    }
                }
    public:     x::event & operator=(const x::event & o)
                {
                    if(&o != this)
                    {
                        __id = o.__id;
                        __object = o.__object;
                        __engine = o.__engine;
                        __generator = o.__generator;
                    }
                    return *this;
                }
    public:     x::event & operator=(x::event && o) noexcept
                {
                    if(&o != this)
                    {
                        __id = o.__id;
                        __object = o.__object;
                        __engine = o.__engine;
                        __generator = o.__generator;

                        o.__id = x::event::type::none;
                        o.__object = nullptr;
                        o.__engine = nullptr;
                        o.__generator = nullptr;
                    }
                    return *this;
                }
    public:     event(x::uint32 id, x::event::object * o, x::event::engine * engine, x::event::generator * generator)
                :   __id(id),
                    __object(o),
                    __engine(engine),
                    __generator(generator)
                {
                }
    public:     event() = delete;
    public:     event(const x::event & o)
                :   __id(o.__id),
                    __object(o.__object),
                    __engine(o.__engine),
                    __generator(o.__generator)
                {
                }
    public:     event(x::event && o) noexcept
                :   __id(o.__id),
                    __object(o.__object),
                    __engine(o.__engine),
                    __generator(o.__generator)
                {
                    o.__id = x::event::type::none;
                    o.__object = nullptr;
                    o.__engine = nullptr;
                    o.__generator = nullptr;
                }
    public:     virtual ~event()
                {
                    __id = x::event::type::none;
                    __object = nullptr;
                    __engine = nullptr;
                    __generator = nullptr;
                }
    };
}

#endif // __X__EVENTH__HH__
