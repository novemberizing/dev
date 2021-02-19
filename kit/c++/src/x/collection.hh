#ifndef   __NOVEMBERIZING_X__COLLECTION__HH__
#define   __NOVEMBERIZING_X__COLLECTION__HH__

namespace x
{
    template <typename T>
    class collection : public container
    {
    public:     x::collection<T> & operator=(const x::collection<T> & o) = delete;
    public:     x::collection<T> & operator=(x::collection<T> && o) noexcept = delete;
    public:     collection(void) : x::container()
                {
                }
    public:     collection(const x::collection<T> & o) : x::container(o)
                {
                }
    public:     collection(x::collection<T> && o) noexcept : x::container(x::move(o))
                {
                }
    public:     virtual ~collection(void)
                {
                }
    };
}

#endif // __NOVEMBERIZING_X__COLLECTION__HH__
