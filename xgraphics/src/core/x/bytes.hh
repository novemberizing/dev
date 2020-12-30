#ifndef   __X__BYTES__HH__
#define   __X__BYTES__HH__

#include <x/array.hh>

namespace x
{
    class bytes : protected x::array<x::byte>
    {
    public:     inline x::bytes sub(x::uint64 offset, x::uint64 length) const
                {
                    assertion(__size < offset + length);
                    return x::bytes(&__container[offset], length);
                }
    public:     virtual void erase(x::uint64 offset, x::uint64 length)
                {
                    assertion(__size < offset + length);

                    if(offset + length == __size)
                    {
                        __size = offset;
                    }
                    else
                    {
                        x::memory::move<x::byte>(&__container[offset], &__container[offset + length], __size - (offset + length));
                        __size = __size - length;
                    }
                }
    public:     const x::byte * data() const override
                {
                    return x::array<x::byte>::data();
                }
    public:     void resize(x::uint64 n, const x::byte & item) override
                {
                    x::array<x::byte>::resize(n, item);
                }
    public:     void resize(x::uint64 n) override
                {
                    x::array<x::byte>::resize(n);
                }
    public:     void append(const x::byte * source, x::uint64 n) override
                {
                    x::array<x::byte>::append(source, n);
                }
    public:     void append(const x::byte & item, x::uint64 n) override
                {
                    x::array<x::byte>::append(item, n);
                }
    public:     void append(const x::byte & item) override
                {
                    x::array<x::byte>::append(item);
                }
    public:     void append(x::byte && item) override
                {
                    x::array<x::byte>::append(x::move(item));
                }
    public:     void append(const x::array<x::byte> & o) override
                {
                    x::array<x::byte>::append(o);
                }
    public:     void append(const x::initializer<x::byte> & list) override
                {
                    x::array<x::byte>::append(list);
                }
    public:     virtual void append(const x::bytes & o)
                {
                    x::array<x::byte>::append(o);
                }
    public:     void assign(const x::byte * source, x::uint64 n) override
                {
                    x::array<x::byte>::assign(source, n);
                }
    public:     void assign(const x::byte & item, x::uint64 n) override
                {
                    x::array<x::byte>::assign(item, n);
                }
    public:     void assign(const x::byte & item) override
                {
                    x::array<x::byte>::assign(item);
                }
    public:     void assign(x::byte && item) override
                {
                    x::array<x::byte>::assign(x::move(item));
                }
    public:     void assign(const x::array<x::byte> & o) override
                {
                    x::array<x::byte>::assign(o);
                }
    public:     void assign(x::array<x::byte> && o) noexcept override
                {
                    x::array<x::byte>::assign(x::move(o));
                }
    public:     void assign(const x::initializer<x::byte> & list) override
                {
                    x::array<x::byte>::assign(list);
                }
    public:     virtual void assign(const x::bytes & o)
                {
                    x::array<x::byte>::assign(o);
                }
    public:     virtual void assign(x::bytes && o) noexcept
                {
                    x::array<x::byte>::assign(x::move(o));
                }
    public:     x::uint64 size() const override
                {
                    return x::array<x::byte>::size();
                }
    public:     x::boolean empty() const override
                {
                    return x::array<x::byte>::empty();
                }
    public:     void clear() override
                {
                    x::array<x::byte>::clear();
                }
    public:     void clear(x::function<void (x::byte&&)> f) override
                {
                    x::array<x::byte>::clear(f);
                }
    public:     x::byte & operator[](x::uint64 i)
                {
                    return x::array<x::byte>::operator[](i);
                }
    public:     const x::byte & operator[](x::uint64 i) const
                {
                    return x::array<x::byte>::operator[](i);
                }
    public:     x::bytes & operator+=(x::byte c)
                {
                    append(c);
                    return *this;
                }
    public:     x::bytes & operator+=(const x::array<x::byte> & o)
                {
                    append(o);
                    return *this;
                }
    public:     x::bytes & operator+=(const x::initializer<x::byte> & o)
                {
                    append(o);
                    return *this;
                }
    public:     x::bytes & operator+=(const x::bytes & o)
                {
                    append(o);
                    return *this;
                }
    public:     x::bytes & operator=(x::byte c)
                {
                    assign(c);
                    return *this;
                }
    public:     x::bytes & operator=(const x::array<x::byte> & o)
                {
                    assign(o);
                    return *this;
                }
    public:     x::bytes & operator=(const x::initializer<x::byte> & o)
                {
                    assign(o);
                    return *this;
                }
    public:     x::bytes & operator=(const x::bytes & o)
                {
                    assign(o);
                    return *this;
                }
    public:     x::bytes & operator=(x::bytes && o) noexcept
                {
                    assign(x::move(o));
                    return *this;
                }
    protected:  bytes(x::uint64 page)
                :   x::array<x::byte>(page)
                {
                }
    protected:  bytes(x::byte * container, x::uint64 n, x::uint64 capacity, x::uint64 page)
                :   x::array<x::byte>(container, n, capacity, page)
                {
                }
    protected:  bytes(x::byte * container, x::uint64 n, x::uint64 capacity)
                :   x::array<x::byte>(container, n, capacity)
                {
                }
    public:     bytes(const x::byte * source, x::uint64 n)
                :   x::array<x::byte>(source, n)
                {
                }
    public:     bytes(const x::byte & item, x::uint64 n)
                :   x::array<x::byte>(item, n)
                {
                }
    public:     bytes(const x::initializer<x::byte> & list)
                :   x::array<x::byte>(list)
                {
                }
    public:     bytes(const x::array<x::byte> & o)
                :   x::array<x::byte>(o)
                {
                }
    public:     bytes(x::array<x::byte> && o) noexcept
                :   x::array<x::byte>(x::move(o))
                {
                }
    public:     bytes()
                :   x::array<x::byte>()
                {
                }
    public:     bytes(const x::bytes & o)
                :   x::array<x::byte>(o)
                {
                }
    public:     bytes(x::bytes && o) noexcept
                :   x::array<x::byte>(x::move(o))
                {
                }
    public:     ~bytes() override
                {
                }
    public:     friend x::bytes operator+(const x::bytes & left, const x::bytes & right)
                {
                    x::bytes out = left;
                    out += right;
                    return out;
                }
    public:     friend x::bytes operator+(const x::bytes & left, x::byte          right)
                {
                    x::bytes out = left;
                    out += right;
                    return out;
                }
    public:     friend x::bytes operator+(x::byte          left, const x::bytes & right)
                {
                    x::bytes out = left;
                    out += right;
                    return out;
                }
    };
}

#endif // __X__BYTES__HH__
