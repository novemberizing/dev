#ifndef   __X__BYTES__HH__
#define   __X__BYTES__HH__

#include <x/output/stream.hh>
#include <x/array.hh>

namespace x
{
    class bytes : protected array<byte>
    {
    public:     virtual void erase(uint64 offset, uint64 n)
                {
                    if(n > 0)
                    {
                        if(offset < __size)
                        {
                            if(offset + n < __size)
                            {
                                __memmove(&__container[offset], &__container[offset + n], __size - (offset + n));
                                __size = __size - n;
                            }
                            else
                            {
                                __size = offset;
                            }
                        }
                    }
                }
    public:     virtual void assign(const byte * source, x::uint64 n)
                {
                    array<byte>::clear();
                    push(source, n);
                }
    public:     void push(const byte & item) override
                {
                    array<byte>::push(item);
                }
    public:     void push(byte && item) override
                {
                    array<byte>::push(x::move(item));
                }
    public:     void push(const byte & item, uint64 n) override
                {
                    array<byte>::push(item, n);
                }
    public:     void push(const byte * source, x::uint64 n) override
                {
                    array<byte>::push(source, n);
                }
    public:     void clear() override
                {
                    array<byte>::clear();
                }
    public:     void clear(std::function<void (byte &&)> f) override
                {
                    array<byte>::clear(f);
                }
    public:     uint64 size() const override
                {
                    return array<byte>::size();
                }
    public:     const byte * data() const override
                {
                    return array<byte>::data();
                }
    public:     x::byte & operator[](x::uint64 i)
                {
                    return x::array<byte>::operator[](i);
                }
    public:     const x::byte & operator[](x::uint64 i) const
                {
                    return x::array<byte>::operator[](i);
                }
    public:     bytes & operator+=(byte c)
                {
                    array<byte>::push(c);
                    return *this;
                }
    public:     bytes & operator+=(const bytes & o)
                {
                    if(&o != this)
                    {
                        array<byte>::push(o.__container, o.__size);
                    }
                    else
                    {
                        bytes s = o;
                        array<byte>::push(s.__container, s.__size);
                    }
                    return *this;
                }
    public:     bytes & operator+=(bytes && o)
                {
                    if(&o != this)
                    {
                        array<byte>::push(o.__container, o.__size);
                    }
                    else
                    {
                        bytes s = o;
                        array<byte>::push(s.__container, s.__size);
                    }
                    return *this;
                }
    public:     bytes & operator=(byte c)
                {
                    array<byte>::clear();
                    array<byte>::push(c);
                    return *this;
                }
    public:     bytes & operator=(const bytes & o)
                {
                    array<byte>::operator=(o);
                    return *this;
                }
    public:     bytes & operator=(bytes && o) noexcept
                {
                    array<byte>::operator=(x::move(o));
                    return *this;
                }
    protected:  bytes(x::uint64 page)
                :   array<byte>(page)
                {
                }
    /**
     * TODO: CHECK THIS CONVENTION
     */
    public:     bytes(byte *&& data, uint64 n)
                :   array<byte>(x::move(data), n)
                {
                }
    public:     bytes(byte c)
                : array<byte>()
                {
                    array<byte>::push(c);
                }
    public:     bytes(byte c, uint64 n)
                :   array<byte>()
                {
                    array<byte>::push(c, n);
                }
    public:     bytes(const byte * data, uint64 len)
                :   array<byte>()
                {
                    array<byte>::push(data, len);
                }
    public:     bytes() : array<byte>()
                {
                }
    public:     bytes(const bytes & o) : array<byte>(o)
                {
                }
    public:     bytes(bytes && o) noexcept : array<byte>(x::move(o))
                {
                }
    public:     ~bytes() override
                {
                }
    public:     friend bytes operator+(const bytes & left, const bytes & right)
                {
                    bytes out = left;
                    out += right;
                    return out;
                }
    public:     friend bytes operator+(const bytes & left, byte          right)
                {
                    bytes out = left;
                    out += right;
                    return out;
                }
    public:     friend bytes operator+(byte          left, const bytes & right)
                {
                    bytes out = left;
                    out += right;
                    return out;
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const bytes & o)
                {
                    os << "{";
                    os << "\"capacity\": " << o.__capacity << ",";
                    os << "\"size\": " << o.__size << ",";
                    os << "\"page\": " << o.__page << ",";
                    os << "\"data: \"";
                    if(o.__container == nullptr)
                    {
                        os << "null";
                    }
                    else
                    {
                        os << "[";
                        for(uint64 i = 0; i < o.__size; i++)
                        {
                            os << o.__container[i];
                            if(i + 1 != o.__size)
                            {
                                os << ",";
                            }
                        }
                        os << "]";
                    }
                    os << "}";
                    return os;
                }
    };
}

#endif // __X__BYTES__HH__
