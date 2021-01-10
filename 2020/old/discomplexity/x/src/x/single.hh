#ifndef   __X__SINGLE__HH__
#define   __X__SINGLE__HH__

namespace x
{
    template <typename A>
    class single
    {
    protected:  A __first;
    public:     const A & first() const
                {
                    return this->__first;
                }
    public:     void first(const A & v)
                {
                    this->__first = v;
                }
    public:     void first(A && v)
                {
                    this->__first = x::move(v);
                }
    public:     single<A> & operator=(const A & v)
                {
                    this->__first = v;
                    return *this;
                }
    public:     single<A> & operator=(A && v)
                {
                    this->__first = x::move(v);
                    return *this;
                }
    public:     single<A> & operator=(const single<A> & o)
                {
                    if(&o != this)
                    {
                        this->__first = o.__first;
                    }
                    return *this;
                }
    public:     single<A> & operator=(single<A> && o) noexcept
                {
                    if(&o != this)
                    {
                        this->__first = x::move(o.__first);
                    }
                    return *this;
                }
    public:     single(const A & v) :
                    __first(v)
                {
                }
    public:     single(A && v) :
                    __first(x::move(v))
                {
                }
    public:     single() :
                    __first()
                {
                }
    public:     single(const single<A> & o) :
                    __first(o.__first)
                {
                }
    public:     single(single<A> && o) noexcept :
                    __first(x::move(o.__first))
                {

                }
    public:     virtual ~single()
                {
                }
    };
}

#endif // __X__SINGLE__HH__
