#ifndef   __X__RANDOM__HH__
#define   __X__RANDOM__HH__

#include <x/core.hh>

namespace x
{
    class random
    {
    protected:  static inline x::random * __singleton = nullptr;
    public:     static random & get()
                {
                    if(x::random::__singleton == nullptr)
                    {
                        static x::random o;
                        x::random::__singleton = &o;
                    }
                    return *x::random::__singleton;
                }
    protected:  x::uint32 __seed;
    public:     inline x::int32 integer32()
                {
                    return __core_random();
                }
    public:     inline x::int32 integer32(x::uint32 max)
                {
                    return __core_random() % max;
                }
    public:     random & operator=(const random & o) = delete;
    public:     random & operator=(random && o) noexcept = delete;
    protected:  random()
                :   __seed(__core_time(nullptr))
                {
                    __core_srandom(__seed);
                }
    public:     random(const random & o) = delete;
    public:     random(random && o) noexcept = delete;
    public:     virtual ~random()
                {
                }
    };
}

#endif // __X__RANDOM__HH__
