#ifndef   __X__MATRIX__HH__
#define   __X__MATRIX__HH__

#include <x/vector.hh>

namespace x
{
    template <typename T>
    class matrix
    {
    public:     static x::matrix<T> identity(x::uint64 row, x::uint64 column)
                {
                    assertion(row != column);

                    x::matrix<T> result(row, column);
                    x::array<T> & container = result.__reference.get();
                    for(x::uint64 i = 0; i < row; i++)
                    {
                        container[i * column + i] = 1;
                    }
                    return result;
                }
    protected:  x::reference<x::array<T> > __reference;
    protected:  x::uint64 __row;
    protected:  x::uint64 __column;
    public:     inline const T * data() const
                {
                    if(__reference.exist())
                    {
                        const x::array<T> & o = __reference.get();
                        return o.data();
                    }
                    else
                    {
                        return nullptr;
                    }
                }
    public:     virtual x::matrix<T> inverse() const
                {
                    assertion(__row != __column);
                    if(__row == 1)
                    {
                        return x::matrix<T>(*this);
                    }
                    else if(__row == 2)
                    {
                        const array<T> & container = __reference.get();
                        T value = container[0] * container[3] - container[2] * container[1];
                        assertion(value == 0);
                        return x::matrix<T>({ {  container[3]/value, container[1]/value },
                                              { -container[2]/value, container[0]/value }});
                    }
                    else if(__row == 3)
                    {
                        exceptional();
                    }
                    else if(__row == 4)
                    {
                        exceptional();
                    }
                    else
                    {
                        exceptional();
                    }
                }
    public:     virtual x::int32 symmetric() const
                {
                    x::matrix<T> o = transpose();
                    return *this == o;
                }
    public:     virtual x::matrix<T> pow(const T value) const
                {
                    assertion(value <= 0 || __column != __row);

                    const x::matrix<T> & self = *this;

                    x::matrix<T> result = self;
                    for(x::uint64 i = 1; i < value; i++)
                    {
                        result = x::move(result * self);
                    }
                    return result;
                }
    public:     virtual x::matrix<T> transpose() const
                {
                    x::matrix<T> result(__column, __row);
                    const array<T> & x = __reference.get();
                    array<T> & container = result.__reference.get();
                    for(x::uint64 i = 0; i < result.__row; i++)
                    {
                        for(x::uint64 j = 0; j < result.__column; j++)
                        {
                            container[i * result.__column + j] = x[j * __column + i];
                        }
                    }
                    return result;
                }
    public:     virtual x::uint64 row() const
                {
                    return __row;
                }
    public:     virtual x::uint64 column() const
                {
                    return __column;
                }
    public:     x::vector<T> operator[](x::uint64 i) const
                {
                    assertion(__row <= i);

                    return x::vector<T>(__reference, i * __column, __column);
                }
    public:     x::matrix<T> & operator*=(const T & value)
                {
                    array<T> & container = __reference.get();
                    for(x::uint64 i = 0; i < __row; i++)
                    {
                        for(x::uint64 j = 0; j < __column; j++)
                        {
                            container[i * __column + j] *= value;
                        }
                    }
                    return *this;
                }
    public:     x::matrix<T> & operator+=(const x::matrix<T> & o)
                {
                    assertion(__row != o.__row || __column != o.__column);

                    array<T> & _x = __reference.get();
                    const array<T> & _y = o.__reference.get();
                    for(x::uint64 i = 0; i < __row; i++)
                    {
                        for(x::uint64 j = 0; j < __column; j++)
                        {
                            _x[i * __column + j] = _x[i * __column + j] + _y[i * __column + j];
                        }
                    }
                    return *this;
                }
    public:     x::matrix<T> & operator-=(const x::matrix<T> & o)
                {
                    assertion(__row != o.__row || __column != o.__column);

                    array<T> & _x = __reference.get();
                    const array<T> & _y = o.__reference.get();
                    for(x::uint64 i = 0; i < __row; i++)
                    {
                        for(x::uint64 j = 0; j < __column; j++)
                        {
                            _x[i * __column + j] = _x[i * __column + j] - _y[i * __column + j];
                        }
                    }
                    return *this;
                }
    public:     x::matrix<T> & operator=(const x::initializer<x::initializer<T> > & lists)
                {
                    __row = 0;
                    __column = 0;
                    for(typename x::initializer<x::initializer<T> >::iterator it = lists.begin(); it != lists.end(); ++it)
                    {
                        __row = __row + 1;
                        const x::initializer<T> & list = *it;
                        if(__column < list.size())
                        {
                            __column = list.size();
                        }
                    }
                    __reference = array<T>();
                    array<T> & container = __reference.get();
                    for(typename x::initializer<x::initializer<T> >::iterator it = lists.begin(); it != lists.end(); ++it)
                    {
                        const x::initializer<T> & list = *it;
                        container.push(list);
                        if(list.size() != __column)
                        {
                            container.push(T(), __column - list.size());
                        }
                    }
                    return *this;
                }
    public:     x::matrix<T> & operator=(const x::matrix<T> & o)
                {
                    if(&o != this)
                    {
                        const x::array<T> & container = o.__reference.get();;
                        __reference = container.sub(0, o.__row * o.__column);
                        __row = o.__row;
                        __column = o.__column;
                    }
                    return *this;
                }
    public:     x::matrix<T> & operator=(x::matrix<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        __reference = x::move(o.__reference);
                        __row = o.__row;
                        __column = o.__column;

                        o.__row = 0;
                        o.__column = 0;
                    }
                    return *this;
                }
    public:     matrix(x::uint64 row, x::uint64 column)
                :   __reference(array<T>(T(), row * column)),
                    __row(row),
                    __column(column)
                {
                }
    public:     matrix(const x::initializer<x::initializer<T> > & lists) :
                    __reference(array<T>()),
                    __row(lists.size()),
                    __column(0)
                {
                    for(typename x::initializer<x::initializer<T> >::iterator it = lists.begin(); it != lists.end(); ++it)
                    {
                        const x::initializer<T> & list = *it;
                        if(__column < list.size())
                        {
                            __column = list.size();
                        }
                    }
                    array<T> & container = __reference.get();
                    for(typename x::initializer<x::initializer<T> >::iterator it = lists.begin(); it != lists.end(); ++it)
                    {
                        const x::initializer<T> & list = *it;
                        container.push(list);
                        if(list.size() != __column)
                        {
                            container.push(T(), __column - list.size());
                        }
                    }
                }
    public:     matrix() :
                    __reference(array<T>()),
                    __row(0),
                    __column(0)
                {
                }
    public:     matrix(const x::matrix<T> & o) :
                    __reference(),
                    __row(o.__row),
                    __column(o.__column)
                {
                    const x::array<T> & container = o.__reference.get();
                    __reference = container.sub(0, o.__row * o.__column);
                }
    public:     matrix(x::matrix<T> && o) noexcept :
                    __reference(x::move(o.__reference)),
                    __row(o.__row),
                    __column(o.__column)
                {
                    o.__row = 0;
                    o.__column = 0;
                }
    public:     virtual ~matrix()
                {
                }
    public:     friend x::matrix<T> operator*(const x::matrix<T> & left, const T & right)
                {
                    x::matrix<T> result = left;
                    result *= right;
                    return result;
                }
    public:     friend x::matrix<T> operator*(const T & left, const x::matrix<T> & right)
                {
                    x::matrix<T> result = right;
                    result *= left;
                    return result;
                }
    public:     friend x::matrix<T> operator*(const x::matrix<T> & left, const x::matrix<T> & right)
                {
                    assertion(left.__column != right.__row || left.__row == 0 || right.__column == 0);

                    x::matrix<T> result(left.__row, right.__column);
                    x::array<T> & container = result.__reference.get();
                    const x::array<T> & x = left.__reference.get();
                    const x::array<T> & y = right.__reference.get();
                    for(x::uint64 i = 0; i < left.__row; i++)
                    {
                        for(x::uint64 j = 0; j < right.__column; j++)
                        {
                            for(x::uint64 k = 0; k < left.__column; k++)
                            {
                                container[i * result.__column + j] +=
                                    x[i * left.__column + k] *
                                    y[k * right.__column + j];
                            }
                        }
                    }
                    return result;
                }
    public:     friend x::matrix<T> operator+(const x::matrix<T> & left, const x::matrix<T> & right)
                {
                    x::matrix<T> result = left;
                    result += right;
                    return result;
                }
    public:     friend x::matrix<T> operator-(const x::matrix<T> & left, const x::matrix<T> & right)
                {
                    x::matrix<T> result = left;
                    result -= right;
                    return result;
                }
    public:     friend bool operator!=(const x::matrix<T> & left, const x::matrix<T> & right)
                {
                    if(left.__row == right.__row && left.__column && right.__column)
                    {
                        const array<T> & x = left.__reference.get();
                        const array<T> & y = right.__reference.get();
                        for(x::uint64 i = 0; i < left.__row; i++)
                        {
                            for(x::uint64 j = 0; j < left.__column; j++)
                            {
                                if(x[i * left.__column + j] != y[i * left.__column + j])
                                {
                                    return true;
                                }
                            }
                        }
                        return false;
                    }
                    return true;
                }
    public:     friend bool operator==(const x::matrix<T> & left, const x::matrix<T> & right)
                {
                    if(left.__row == right.__row && left.__column && right.__column)
                    {
                        const array<T> & x = left.__reference.get();
                        const array<T> & y = right.__reference.get();
                        for(x::uint64 i = 0; i < left.__row; i++)
                        {
                            for(x::uint64 j = 0; j < left.__column; j++)
                            {
                                if(x[i * left.__column + j] != y[i * left.__column + j])
                                {
                                    return false;
                                }
                            }
                        }
                        return true;
                    }
                    return false;
                }
    };
}

#endif // __X__MATRIX__HH__
