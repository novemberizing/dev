#ifndef   __X_GRAPHICS__MATRIX__HH__
#define   __X_GRAPHICS__MATRIX__HH__

#include <x/output/stream.hh>
#include <x/graphics/opengl.hh>
#include <x/graphics/vector.hh>
#include <x/matrix.hh>
#include <x/math/trigometric.hh>

namespace x
{
    namespace graphics
    {
        class matrix : protected x::matrix<x::float32>
        {
        public:     static x::graphics::matrix convert();
        public:     static x::graphics::matrix identity();
        public:     static x::graphics::matrix lookat(const vector & eye, const vector & center, const vector & up);
        public:     static x::graphics::matrix perspective(float32 fovy, float32 aspect, float32 near, float32 far);
        public:     static x::graphics::matrix translate(const x::graphics::matrix & m, const x::graphics::vector & v);
        public:     static x::graphics::matrix rotate(const x::graphics::matrix & m, x::float32 angle, const x::graphics::vector & v);
        public:     static x::graphics::matrix rotate(x::float32 angle, const x::graphics::vector & v);
        public:     static x::graphics::matrix scale(const x::graphics::matrix & m, const x::graphics::vector & v);
        // protected:  x::string __name;
        // protected:  x::uint32 __id;
        public:     inline const x::float32 * data() const
                    {
                        return x::matrix<x::float32>::data();
                    }
        public:     x::graphics::vector operator[](x::uint64 i) const
                    {
                        assertion(__row <= i);

                        return x::graphics::vector(__reference, i * __column, __column);
                    }
        public:     matrix & operator*=(const x::float32 & value)
                    {
                        array<x::float32> & container = __reference.get();
                        for(x::uint64 i = 0; i < __row; i++)
                        {
                            for(x::uint64 j = 0; j < __column; j++)
                            {
                                container[i * __column + j] *= value;
                            }
                        }
                        return *this;
                    }
        public:     matrix & operator+=(const matrix & o)
                    {
                        assertion(__row != o.__row || __column != o.__column);

                        array<x::float32> & _x = __reference.get();
                        const array<x::float32> & _y = o.__reference.get();
                        for(x::uint64 i = 0; i < __row; i++)
                        {
                            for(x::uint64 j = 0; j < __column; j++)
                            {
                                _x[i * __column + j] = _x[i * __column + j] + _y[i * __column + j];
                            }
                        }
                        return *this;
                    }
        public:     matrix & operator-=(const matrix & o)
                    {
                        assertion(__row != o.__row || __column != o.__column);

                        array<x::float32> & _x = __reference.get();
                        const array<x::float32> & _y = o.__reference.get();
                        for(x::uint64 i = 0; i < __row; i++)
                        {
                            for(x::uint64 j = 0; j < __column; j++)
                            {
                                _x[i * __column + j] = _x[i * __column + j] - _y[i * __column + j];
                            }
                        }
                        return *this;
                    }
        public:     matrix & operator=(const matrix & o);
        public:     matrix & operator=(matrix && o) noexcept;
        public:     matrix();
        public:     matrix(const matrix & o);
        public:     matrix(matrix && o) noexcept;
        public:     ~matrix() override;
        public:     friend matrix operator*(const matrix & x, const x::float32 & y)
                    {
                        matrix result = x;
                        result *= y;
                        return result;
                    }
        public:     friend matrix operator*(const x::float32 & x, const matrix & y)
                    {
                        matrix result = y;
                        result *= x;
                        return result;
                    }
        public:     friend matrix operator*(const matrix & x, const matrix & y)
                    {
                        assertion(x.__column != y.__row || x.__row == 0 || y.__column == 0);
                        assertion(x.__row != 4 || y.__column != 4);

                        matrix result;
                        x::array<x::float32> & container = result.__reference.get();
                        const x::array<x::float32> & _x = x.__reference.get();
                        const x::array<x::float32> & _y = y.__reference.get();
                        for(x::uint64 i = 0; i < x.__row; i++)
                        {
                            for(x::uint64 j = 0; j < y.__column; j++)
                            {
                                for(x::uint64 k = 0; k < x.__column; k++)
                                {
                                    container[i * result.__column + j] += (_x[i * x.__column + k] * _y[k * y.__column + j]);
                                }
                            }
                        }
                        return result;
                    }
        public:     friend x::graphics::vector operator*(const x::graphics::matrix & m, const x::graphics::vector & v)
                    {
                        x::graphics::vector result;
                        x::graphics::vector row = m[0];
                        result[0] = row[0] * v[0] + row[1] * v[1] + row[2] * v[2] + row[3] * v[3];
                        row = m[1];
                        result[1] = row[0] * v[0] + row[1] * v[1] + row[2] * v[2] + row[3] * v[3];
                        row = m[2];
                        result[2] = row[0] * v[0] + row[1] * v[1] + row[2] * v[2] + row[3] * v[3];
                        row = m[3];
                        result[3] = row[0] * v[0] + row[1] * v[1] + row[2] * v[2] + row[3] * v[3];
                        return result;
                    }
        public:     friend x::output::stream & operator<<(x::output::stream & os, const matrix & o)
                    {
                        if(o.__reference.exist())
                        {
                            const x::array<x::float32> & container = o.__reference.get();
                            os << "[";
                            for(x::uint64 i = 0; i < o.__row; i++)
                            {
                                os << "[";
                                for(x::uint64 j = 0; j < o.__column; j++)
                                {
                                    os << container[o.__column * i + j] << ((j + 1 == o.__column) ? "" : ",");
                                }
                                os << "]" << ((i + 1 == o.__row) ? "" : ",");
                            }
                            os << "]";
                        }
                        else
                        {
                            os << "null";
                        }
                        return os;
                    }
        };
    }
}

#endif // __X_GRAPHICS__MATRIX__HH__
