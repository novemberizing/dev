#ifndef   __X__EVENT__HH__
#define   __X__EVENT__HH__

#include <x/type.hh>
#include <x/map.hh>
#include <x/array.hh>
#include <x/list.hh>
#include <x/queue.hh>

namespace x
{
    class event
    {
    public:     class type
                {
                public:     static const x::uint32 none  = 0U;
                public:     static const x::uint32 open  = 1U;
                public:     static const x::uint32 read  = 2U;
                public:     static const x::uint32 write = 3U;
                public:     static const x::uint32 close = 4U;
                };
    public:     class object;
    public:     class engine;
    public:     class processor
                {
                protected:  x::queue<event> __events;
                public:     virtual void cycle()
                            {
                                x::uint32 total = __events.size();
                                for(x::uint32 i = 0; i < total && __events.size() > 0; i++)
                                {
                                    x::event event = x::move(__events.pop());
                                    event.on();
                                }
                            }
                public:     virtual void add(x::event && o)
                            {
                                __events.push(x::move(o));
                            }
                public:     processor & operator=(const processor & o)
                            {
                                return *this;
                            }
                public:     processor & operator=(processor && o) noexcept
                            {
                                return *this;
                            }
                public:     processor()
                            {
                            }
                public:     processor(const processor & o)
                            {
                            }
                public:     processor(processor && o) noexcept
                            {
                            }
                public:     virtual ~processor()
                            {
                            }
                };
    public:     class generator
                {
                public:     class type
                            {
                            public:     static const x::uint32 none = 0xFFFFFFFFU;
                            public:     static const x::uint32 io = 0U;
                            };
                public:     typedef generator * pointer;
                protected:  event::engine * __engine;
                protected:  x::uint32 __type;
                public:     inline x::uint32 type() const
                            {
                                return __type;
                            }
                public:     inline void engine(event::engine * o)
                            {
                                if(__engine == nullptr)
                                {
                                    __engine = o;
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                public:     virtual void init()
                            {
                            }
                public:     virtual void term()
                            {
                            }
                public:     virtual void mod(x::event::object * o) = 0;
                public:     virtual void add(x::event::object * o) = 0;
                public:     virtual void cycle() = 0;
                public:     generator & operator=(const generator & o)
                            {
                                if(&o != this)
                                {
                                    __engine = o.__engine;
                                    __type = o.__type;
                                }
                                return *this;
                            }
                public:     generator & operator=(generator && o) noexcept
                            {
                                if(&o != this)
                                {
                                    __engine = o.__engine;
                                    __type = o.__type;

                                    o.__type = generator::type::none;
                                }
                                return *this;
                            }
                protected:  generator(x::uint32 type)
                            :   __engine(nullptr),
                                __type(type)
                            {
                            }
                public:     generator()
                            :   __engine(nullptr),
                                __type(generator::type::none)
                            {
                            }
                public:     generator(const generator & o)
                            :   __engine(o.__engine),
                                __type(o.__type)
                            {
                            }
                public:     generator(generator && o) noexcept
                            :   __engine(o.__engine),
                                __type(o.__type)
                            {
                                o.__engine = nullptr;
                                o.__type = generator::type::none;
                            }
                public:     virtual ~generator()
                            {
                                __engine = nullptr;
                                __type = generator::type::none;
                            }
                };
    public:     class engine
                {
                public:     class status
                            {
                            public:     static const x::uint32 none       = 0x00000000U <<  0U;
                            public:     static const x::uint32 cancelling = 0x00000001U <<  0U;
                            public:     static const x::uint32 running    = 0x00000001U <<  1U;
                            };
                protected:  x::map<x::uint32, event::generator *> __generators;
                protected:  event::processor * __processor;
                protected:  x::uint32 __status;
                public:     inline x::boolean is(x::uint32 v)
                            {
                                return (__status & v) == v;
                            }
                public:     virtual void init()
                            {
                                if(__processor == nullptr)
                                {
                                    __processor = new event::processor();
                                }
                                __generators.each([](const x::uint32 key, generator::pointer & generator){
                                    generator->init();
                                });
                            }
                public:     virtual void term()
                            {
                                __generators.each([](const x::uint32 key, generator::pointer & generator){
                                    generator->term();
                                });
                            }
                public:     virtual void cycle()
                            {
                                __generators.each([](const x::uint32 key, generator::pointer & generator){
                                    generator->cycle();
                                });
                                if(__processor)
                                {
                                    __processor->cycle();
                                }
                            }
                public:     virtual x::int32 run()
                            {
                                init();
                                while((__status & engine::status::cancelling) != engine::status::cancelling)
                                {
                                    cycle();
                                }
                                term();
                            }
                public:     virtual void add(x::event && o)
                            {
                                if(__processor)
                                {
                                    __processor->add(x::move(o));
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                public:     virtual void add(event::generator * o)
                            {
                                if(o != nullptr)
                                {
                                    __generators.put(o->type(), o);
                                    o->engine(this);
                                }
                            }
                public:     virtual void add(x::uint32 id, x::event::object & o)
                            {
                                add(id, &o);
                            }
                public:     virtual void add(x::uint32 id, event::object * o)
                            {
                                if(o != nullptr)
                                {
                                    try
                                    {
                                        x::event::generator * generator = __generators[id];
                                        if(generator)
                                        {
                                            generator->add(o);
                                        }
                                    }
                                    catch(const x::exception & e)
                                    {

                                    }
                                }
                            }
                public:     virtual void mod(x::uint32 id, x::event::object * o)
                            {
                                if(o != nullptr)
                                {
                                    try
                                    {
                                        x::event::generator * generator = __generators[id];
                                        if(generator)
                                        {
                                            generator->mod(o);
                                        }
                                    }
                                    catch(const x::exception & e)
                                    {

                                    }
                                }
                            }
                public:     virtual void del(event::object * o)
                            {
                            }
                public:     virtual void clear()
                            {
                            }
                public:     engine & operator=(const engine & o)
                            {
                                if(&o != this)
                                {
                                    __status = o.__status;
                                    __processor = o.__processor;
                                }
                                return *this;
                            }
                public:     engine & operator=(engine && o) noexcept
                            {
                                if(&o != this)
                                {
                                    __status = o.__status;
                                    __processor = o.__processor;
                                    __generators = x::move(o.__generators);

                                    o.__status = engine::status::none;
                                    o.__processor = nullptr;
                                }
                                return *this;
                            }
                public:     engine()
                            :   __status(engine::status::none),
                                __processor(nullptr),
                                __generators()
                            {
                            }
                public:     engine(const engine & o)
                            :   __status(o.__status),
                                __processor(nullptr),
                                __generators()
                            {
                            }
                public:     engine(engine && o) noexcept
                            :   __status(o.__status),
                                __processor(o.__processor),
                                __generators(x::move(o.__generators))
                            {
                                o.__status = engine::status::none;
                                o.__processor = nullptr;
                            }
                public:     virtual ~engine()
                            {
                                clear();
                                __status = engine::status::none;
                                __generators.clear([](x::pair<x::uint32, generator::pointer> && o){
                                    if(o.second())
                                    {
                                        delete o.second();
                                        o.second(nullptr);
                                    }
                                });
                                if(__processor)
                                {
                                    delete __processor;
                                    __processor = nullptr;
                                }
                            }
                };
    public:     class object
                {
                public:     class status
                            {
                            public:     static const x::uint32             none     = 0x00000000U <<  0U;
                            public:     static const x::uint32             openable = 0x00000001U <<  0U;
                            public:     static const x::uint32             readable = 0x00000001U <<  1U;
                            public:     static const x::uint32             writable = 0x00000001U <<  2U;
                            public:     static const x::uint32             closable = 0x00000001U <<  3U;
                            public:     class wait
                                        {
                                        public:     static const x::uint32 read     = 0x00000001U <<  4U;
                                        public:     static const x::uint32 write    = 0x00000001U <<  5U;
                                        public:     static const x::uint32 close    = 0x00000001U <<  6U;
                                        };
                            public:     class on
                                        {
                                        public:     static const x::uint32 read     = 0x00000001U <<  7U;
                                        public:     static const x::uint32 write    = 0x00000001U <<  8U;
                                        };
                            };
                public:     virtual x::int32 id() const = 0;
                public:     virtual x::uint32 status() const = 0;
                public:     virtual x::event::engine * engine() const = 0;
                public:     virtual void engine(x::event::engine * o) = 0;
                public:     virtual x::boolean need(x::uint32 id)
                            {
                                return false;
                            }
                public:     virtual void off(x::uint32 id, x::event::engine * engine, x::event::generator * generator)
                            {
                            }
                public:     virtual void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator, x::event::processor * processor)
                            {
                                __console_out("base object on\n");
                            }
                public:     object & operator=(const object & o)
                            {
                                if(&o != this)
                                {
                                }
                                return *this;
                            }
                public:     object & operator=(object && o) noexcept
                            {
                                if(&o != this)
                                {
                                }
                                return *this;
                            }
                protected:  object()
                            {
                            }
                protected:  object(const object & o)
                            {
                            }
                protected:  object(object && o) noexcept
                            {
                            }
                public:     virtual ~object()
                            {
                            }
                };
    protected:  x::uint32 __id;
    protected:  x::event::object * __target;
    protected:  x::event::engine * __engine;
    protected:  x::event::generator * __generator;
    protected:  x::event::processor * __processor;
    public:     inline void on()
                {
                    __target->on(__id, __engine, __generator, __processor);
                }
    public:     event & operator=(const event & o)
                {
                    if(&o != this)
                    {
                        __id = o.__id;
                        __target = o.__target;
                        __engine = o.__engine;
                        __generator = o.__generator;
                        __processor = o.__processor;
                    }
                    return *this;
                }
    public:     event & operator=(event && o) noexcept
                {
                    if(&o != this)
                    {
                        __id = o.__id;
                        __target = o.__target;
                        __engine = o.__engine;
                        __generator = o.__generator;
                        __processor = o.__processor;

                        o.__id = event::type::none;
                        o.__target = nullptr;
                        o.__engine = nullptr;
                        o.__generator = nullptr;
                        o.__processor = nullptr;
                    }
                    return *this;
                }
    public:     event(x::uint32 id, x::event::object * target, x::event::engine * engine, x::event::generator * generator)
                :   __id(id),
                    __target(target),
                    __engine(engine),
                    __generator(generator),
                    __processor(nullptr)
                {
                }
    public:     event(x::uint32 id, x::event::object * target, x::event::engine * engine)
                :   __id(id),
                    __target(target),
                    __engine(engine),
                    __generator(nullptr),
                    __processor(nullptr)
                {
                }
    public:     event()
                :   __id(x::event::type::none),
                    __target(nullptr),
                    __engine(nullptr),
                    __generator(nullptr),
                    __processor(nullptr)
                {
                }
    public:     event(const event & o)
                :   __id(o.__id),
                    __target(o.__target),
                    __engine(o.__engine),
                    __generator(o.__generator),
                    __processor(o.__processor)
                {
                }
    public:     event(event && o) noexcept
                :   __id(o.__id),
                    __target(o.__target),
                    __engine(o.__engine),
                    __generator(o.__generator),
                    __processor(o.__processor)
                {
                    o.__id = x::event::type::none;
                    o.__target = nullptr;
                    o.__engine = nullptr;
                    o.__generator = nullptr;
                    o.__processor = nullptr;
                }
    public:     virtual ~event()
                {
                    __id = x::event::type::none;
                    __target = nullptr;
                    __engine = nullptr;
                    __generator = nullptr;
                    __processor = nullptr;
                }
    };
}

#endif // __X__EVENT__HH__
