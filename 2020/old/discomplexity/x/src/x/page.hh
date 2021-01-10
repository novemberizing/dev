#ifndef   __X__PAGE__HH__
#define   __X__PAGE__HH__

namespace x
{
    class page
    {
    public:     static x::uint64 size()
                {
                    return 64L;
                }
    public:     static x::uint64 calculate(x::uint64 n)
                {
                    return (n / size() + 1) * size();
                }
    public:     static x::uint64 calculate(x::uint64 n, x::uint64 page)
                {
                    page = (page == 0 ? 1 : page);
                    return (n / page + 1) * page;
                }
    public:     x::page & operator=(const x::page & o) = delete;
    public:     x::page & operator=(x::page && o) = delete;
    public:     page() = delete;
    public:     page(const x::page & o) = delete;
    public:     page(x::page && o) noexcept = delete;
    public:     virtual ~page() =  delete;
    };
}

#endif // __X__PAGE__HH__
