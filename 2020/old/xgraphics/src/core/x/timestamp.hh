#ifndef   __X__TIMESTAMP__HH__
#define   __X__TIMESTAMP__HH__

namespace x
{
    class timestamp
    {
    public:     static x::timestamp current()
                {
                    x::int64 second = 0;
                    x::int64 micro = 0;
                    __core_gettimeofday(second, micro);
                    return x::timestamp(second, micro);
                }
    protected:  x::int64 __second;
    protected:  x::int64 __micro;
    public:     inline x::int64 millisecond() const { return __second * 1000 + __micro/1000; }
    public:     inline x::int64 second() const { return __second; }
    public:     inline x::int64 micro() const { return __micro; }
    public:     inline void second(x::int64 v){ __second = v; }
    public:     inline void micro(x::int64 v){ __micro = v; }
    public:     x::timestamp & operator=(const x::timestamp & o)
                {
                    if(&o != this)
                    {
                        __second = o.__second;
                        __micro = o.__micro;
                    }
                    return *this;
                }
    public:     x::timestamp & operator=(x::timestamp && o) noexcept
                {
                    if(&o != this)
                    {
                        __second = o.__second;
                        __micro = o.__micro;

                        o.__second = 0;
                        o.__micro = 0;
                    }
                    return *this;
                }
    protected:  timestamp(x::int64 second, x::int64 micro)
                :   __second(second),
                    __micro(micro)
                {
                }
    public:     timestamp()
                :   __second(0),
                    __micro(0)
                {
                }
    public:     timestamp(const x::timestamp & o)
                :   __second(o.__second),
                    __micro(o.__micro)
                {
                }
    public:     timestamp(x::timestamp && o) noexcept
                :   __second(o.__second),
                    __micro(o.__micro)
                {
                    o.__second = 0;
                    o.__micro = 0;
                }
    public:     virtual ~timestamp()
                {
                    __second = 0;
                    __micro = 0;
                }
    };
}

#endif // __X__TIMESTAMP__HH__
