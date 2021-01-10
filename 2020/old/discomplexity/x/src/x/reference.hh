#ifndef   __X__REFERENCE__HH__
#define   __X__REFERENCE__HH__

#include <x/space.hh>
#include <x/function.hh>

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
    public:     inline void set(const T & value)
                {
                    if(__space == nullptr)
                    {
                        __space = new space<T>(value);
                        __space->increase();
                    }
                    else
                    {
                        __space->set(value);
                    }
                }
    public:     inline void set(T && value)
                {
                    if(__space == nullptr)
                    {
                        __space = new space<T>(x::move(value));
                        __space->increase();
                    }
                    else
                    {
                        __space->set(x::move(value));
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
    public:     reference<T> & operator=(const T & value)
                {
                    set(value);
                    return *this;
                }
    public:     reference<T> & operator=(T && value)
                {
                    set(x::move(value));
                    return *this;
                }
    public:     reference<T> & operator=(const reference<T> & o)
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
                :   __space(new space<T>(value))
                {
                    __space->increase();
                }
    public:     reference(T && value)
                :   __space(new space<T>(x::move(value)))
                {
                    __space->increase();
                }
    public:     reference()
                :   __space(nullptr)
                {
                }
    public:     reference(const reference<T> & o)
                :   __space(o.__space)
                {
                    if(__space != nullptr)
                    {
                        __space->increase();
                    }
                }
    public:     reference(reference<T> && o) noexcept
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
