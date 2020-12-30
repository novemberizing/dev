#ifndef   __X__VECTOR__HH__
#define   __X__VECTOR__HH__

#include <x/array.hh>
#include <x/reference.hh>
#include <x/math.hh>

namespace x
{
    template <typename T>
    class vector
    {
    public:     static x::vector<T> normalize(const x::vector<T> & o)
                {
                    T dot = x::sqrt<T>(x::vector<T>::dot(o, o));
                    const array<T> & container = o.__reference.get();
                    array<T> result;
                    for(x::uint64 i = 0; i < o.__length; i++)
                    {
                        result.push(container[o.__offset + i] / dot);
                    }
                    return x::vector<T>(x::move(result));
                }
    public:     static x::vector<T> cross(const x::vector<T> & x, const x::vector<T> & y)
                {
                    assertion(x.__length != y.__length || x.__length != 3);
                    x::vector<T> result = x::vector<T>(3);
                    result[0] = (x[1] * y[2] - x[2] * y[1]);
                    result[1] = (x[2] * y[0] - x[0] * y[2]);
                    result[2] = (x[0] * y[1] - x[1] * y[0]);
                    return result;
                }
    public:     static T length(const x::vector<T> & o)
                {
                    assertion(o.__length == 0);

                    const x::array<T> & container = o.__reference.get();
                    T result = container[o.__offset] * container[o.__offset];
                    for(x::uint64 i = 1; i < o.__length; i++)
                    {
                        result = result + container[o.__offset + i] * container[o.__offset + i];
                    }
                    return x::sqrt<T>(result);
                }
    public:     static T dot(const x::vector<T> & x, const x::vector<T> & y)
                {
                    assertion(x.__length != y.__length || x.__length == 0);
                    T result = x[0] * y[0];
                    for(x::uint64 i = 1; i < x.__length; i++)
                    {
                        result += (x[i] * y[i]);
                    }
                    return result;
                }
    public:     static T angle(const x::vector<T> & x, const x::vector<T> & y)
                {
                    assertion(x.__length != y.__length || x.__length == 0);

                    return x::acos<T>(x::vector<T>::dot(x, y) / (x::vector<T>::length(x) * x::vector<T>::length(y)));
                }
    public:     static T distance(const x::vector<T> & x, const vector<T> & y)
                {
                    assertion(x.__length != y.__length || x.__length == 0);

                    x::vector<T> v = x - y;
                    return x::vector<T>::length(v);
                }
    public:     static x::vector<T> projection(const x::vector<T> & x, const x::vector<T> & y)
                {
                    exceptional();
                }
    public:     static x::boolean orthogonal(const x::vector<T> & x, const x::vector<T> & y)
                {
                    return x::vector<T>::dot(x, y) == 0;
                }
    protected:  x::reference<x::array<T> > __reference;
    protected:  x::uint64 __offset;
    protected:  x::uint64 __length;
    public:     inline const T * data() const
                {
                    const x::array<T> & o = __reference.get();
                    return &o.data()[__offset];
                }
    public:     inline x::uint64 size() const
                {
                    return __length;
                }
    public:     x::vector<T> & operator-=(const x::vector<T> & o)
                {
                    if(&o != this)
                    {
                        assertion(__length != o.__length);
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] -= o[i];
                        }
                    }
                    else
                    {
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] = T();
                        }
                    }
                    return *this;
                }
    public:     x::vector<T> & operator+=(const x::vector<T> & o)
                {
                    if(&o != this)
                    {
                        assertion(__length != o.__length);
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] += o[i];
                        }
                    }
                    else
                    {
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] = 2 * container[__offset + i];
                        }
                    }
                    return *this;
                }
    public:     x::vector<T> & operator*=(const T & v)
                {
                    array<T> & container = __reference.get();
                    for(x::uint64 i = 0; i < __length; i++)
                    {
                        container[__offset + i] *= v;
                    }
                    return *this;
                }
    public:     const T & operator[](x::uint64 i) const
                {
                    assertion(__length <= i);
                    const array<T> & container = __reference.get();
                    return container[__offset + i];
                }
    public:     T & operator[](x::uint64 i)
                {
                    assertion(__length <= i);
                    array<T> & container = __reference.get();
                    return container[__offset + i];
                }
    public:     x::vector<T> & operator=(const x::initializer<T> & list)
                {
                    if(list.size() != __length)
                    {
                        __reference = x::array<T>(list);
                        __offset = 0;
                        __length = list.size();
                    }
                    else
                    {
                        array<T> & container = __reference.get();
                        x::uint64 i = 0;
                        for(typename x::initializer<T>::iterator it = list.begin(); it != list.end(); ++it, ++i)
                        {
                            container[__offset + i] = *it;
                        }
                    }
                    return *this;
                }
    public:     x::vector<T> & operator=(const x::array<T> & o)
                {
                    if(o.size() != __length)
                    {
                        __reference = o;
                        __offset = 0;
                        __length = o.size();
                    }
                    else
                    {
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] = o[i];
                        }
                    }
                    return *this;
                }
    public:     x::vector<T> & operator=(x::array<T> && o)
                {
                    if(o.size() != __length)
                    {
                        __length = o.size();
                        __reference = x::move(o);
                        __offset = 0;
                    }
                    else
                    {
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] = o[i];
                        }
                    }
                    return *this;
                }
    public:     x::vector<T> & operator=(const x::vector<T> & o)
                {
                    if(o.size() != __length)
                    {
                        __length = o.__length;
                        __reference = o.__reference;
                        __offset = o.__offset;
                    }
                    else
                    {
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] = o[i];
                        }
                    }
                    return *this;
                }
    public:     x::vector<T> & operator=(x::vector<T> && o) noexcept
                {
                    if(o.size() != __length)
                    {
                        __length = o.__length;
                        __reference = x::move(o.__reference);
                        __offset = o.__offset;

                        o.__length = 0;
                        o.__offset = 0;
                    }
                    else
                    {
                        array<T> & container = __reference.get();
                        for(x::uint64 i = 0; i < __length; i++)
                        {
                            container[__offset + i] = o[i];
                        }
                    }
                    return *this;
                }
    public:     vector(x::uint64 length)
                :   __reference(x::array<T>(T(), length)),
                    __offset(0),
                    __length(length)
                {
                }
    public:     vector(x::array<T> && container, x::uint64 offset, x::uint64 length) :
                    __reference(x::move(container)),
                    __offset(offset),
                    __length(length)
                {

                }
    public:     vector(const x::array<T> & container, x::uint64 offset, x::uint64 length) :
                    __reference(container),
                    __offset(offset),
                    __length(length)
                {

                }
    public:     vector(const x::initializer<T> & list, x::uint64 offset, x::uint64 length) :
                    __reference(x::array<T>(list)),
                    __offset(offset),
                    __length(length)
                {

                }
    public:     vector(x::reference<array<T> > && reference) :
                    __reference(x::move(reference)),
                    __offset(0),
                    __length(0)
                {
                    const x::array<T> & o = __reference.get();
                    __length = o.size();
                }
    public:     vector(x::reference<array<T> > && reference, x::uint64 offset, x::uint64 length) :
                    __reference(x::move(reference)),
                    __offset(offset),
                    __length(length)
                {
                }
    public:     vector(const x::reference<array<T> > & reference) :
                    __reference(reference),
                    __offset(0),
                    __length(0)
                {
                    const x::array<T> & o = __reference.get();
                    __length = o.size();
                }
    public:     vector(const x::reference<array<T> > & reference, x::uint64 offset, x::uint64 length) :
                    __reference(reference),
                    __offset(offset),
                    __length(length)
                {
                }
    public:     vector(const x::initializer<T> & list) :
                    __reference(array<T>(list)),
                    __offset(0),
                    __length(list.size())
                {
                }
    public:     vector(x::array<T> && container) :
                    __reference(x::move(container)),
                    __offset(0),
                    __length(0)
                {
                    const x::array<T> & o = __reference.get();
                    __length = o.size();
                }
    public:     vector(const x::array<T> & container) :
                    __reference(container),
                    __offset(0),
                    __length(container.size())
                {
                }
    public:     vector() :
                    __reference(x::array<T>()),
                    __offset(0),
                    __length(0)
                {
                }
    public:     vector(const x::vector<T> & o) :
                    __reference(),
                    __offset(0),
                    __length(o.__length)
                {
                    const x::array<T> & container = o.__reference.get();
                    __reference = container.sub(o.__offset, o.__length);
                }
    public:     vector(x::vector<T> && o) noexcept :
                    __reference(x::move(o.__reference)),
                    __offset(o.__offset),
                    __length(o.__length)
                {
                    o.__offset = 0;
                    o.__length = 0;
                }
    public:     virtual ~vector()
                {
                }
    public:     friend x::vector<T> operator*(const x::vector<T> & left, const T & right)
                {
                    x::vector<T> result = left;
                    result *= right;
                    return result;
                }
    public:     friend x::vector<T> operator*(const T & left, const x::vector<T> & right)
                {
                    x::vector<T> result = right;
                    result *= left;
                    return result;
                }
    public:     friend x::vector<T> operator+(const x::vector<T> & left, const x::vector<T> & right)
                {
                    if(left.__length != right.__length)
                    {
                        exceptional();
                    }

                    x::vector<T> result = left;
                    result += right;
                    return result;
                }
    public:     friend x::vector<T> operator-(const x::vector<T> & left, const x::vector<T> & right)
                {
                    if(left.__length != right.__length)
                    {
                        exceptional();
                    }

                    x::vector<T> result = left;
                    result -= right;
                    return result;
                }
    public:     friend bool operator!=(const x::vector<T> & left, const x::vector<T> & right)
                {
                    if(left.__length == right.__length)
                    {
                        for(x::uint64 i = 0; i < left.__length; i++)
                        {
                            if(left[i] != right[i])
                            {
                                return true;
                            }
                        }
                        return false;
                    }
                    return true;
                }
    public:     friend bool operator==(const x::vector<T> & left, const x::vector<T> & right)
                {
                    if(left.__length == right.__length)
                    {
                        for(x::uint64 i = 0; i < left.__length; i++)
                        {
                            if(left[i] != right[i])
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    return false;
                }
    };
}

#endif // __X__VECTOR__HH__
