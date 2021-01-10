#ifndef   __X__REFERENCE__HH__
#define   __X__REFERENCE__HH__

#include <x/space.hh>

namespace x
{
    template <typename T>
    class reference
    {
    protected:  x::space<T> * __space;
    public:     inline const T & get() const
                {
                    assertion(__space == nullptr);

                    return __space->get();
                }
    public:     inline T & get()
                {
                    assertion(__space == nullptr);

                    return __space->get();
                }
    public:     inline void set(const T & v)
                {
                    if(__space == nullptr)
                    {
                        __space = new x::space<T>(v);
                        __space->increase();
                    }
                    else
                    {
                        __space->set(v);
                    }
                }
    public:     inline void set(T && v)
                {
                    if(__space == nullptr)
                    {
                        __space = new x::space<T>(x::move(v));
                        __space->increase();
                    }
                    else
                    {
                        __space->set(v);
                    }
                }
    public:     inline x::boolean exist() const
                {
                    return __space != nullptr;
                }
    public:     inline x::boolean empty() const
                {
                    return __space == nullptr;
                }
    public:     virtual x::int64 increase()
                {
                    if(__space)
                    {
                        __space->increase();
                    }
                    return 0;
                }
    public:     virtual void release(x::function<void (T&)> f)
                {
                    if(__space)
                    {
                        if(__space->decrease() <= 0)
                        {
                            if(f)
                            {
                                f(__space->get());
                            }
                            delete __space;
                        }
                        __space = nullptr;
                    }
                }
    public:     x::reference<T> & operator=(const T & v)
                {
                    set(v);
                    return *this;
                }
    public:     x::reference<T> & operator=(T && v)
                {
                    set(x::move(v));
                    return *this;
                }
    public:     x::reference<T> & operator=(const x::reference<T> & o)
                {
                    if(&o != this)
                    {
                        if(__space)
                        {
                            if(__space->decrease() <= 0)
                            {
                                delete __space;
                            }
                        }
                        __space = o.__space;

                        __space->increase();
                    }
                    return *this;
                }
    public:     reference<T> & operator=(reference<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        if(__space)
                        {
                            if(__space->decrease() <= 0)
                            {
                                delete __space;
                            }
                        }

                        __space = o.__space;

                        o.__space = nullptr;
                    }
                    return *this;
                }
    public:     reference(const T & value)
                :   __space(new x::space<T>(value))
                {
                    __space->increase();
                }
    public:     reference(T && value)
                :   __space(new x::space<T>(x::move(value)))
                {
                    __space->increase();
                }
    public:     reference()
                :   __space(nullptr)
                {
                }
    public:     reference(const x::reference<T> & o)
                :   __space(o.__space)
                {
                    if(__space != nullptr)
                    {
                        __space->increase();
                    }
                }
    public:     reference(x::reference<T> && o) noexcept
                :   __space(o.__space)
                {
                    o.__space = nullptr;
                }
    public:     virtual ~reference()
                {
                    if(__space)
                    {
                        if(__space->decrease() <= 0)
                        {
                            delete __space;
                        }
                        __space = nullptr;
                    }
                }
    };
}

#endif // __X__REFERENCE__HH__
