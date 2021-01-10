#ifndef   __X_REALITY__MATRIX__HH__
#define   __X_REALITY__MATRIX__HH__

#include <x/matrix.hh>
#include <x/reality/vector.hh>

namespace x
{
    namespace reality
    {
        class matrix : protected x::matrix<x::real>
        {
        public:     static const x::reality::matrix identity;
        public:     static x::reality::matrix lookat(const x::reality::vector & eye, const x::reality::vector & center, const x::reality::vector & up);
        public:     static x::reality::matrix perspective(x::real fovy, x::real aspect, x::real near, x::real far);
        public:     static x::reality::matrix orthogonal(x::real left, x::real right, x::real bottom, x::real far);
        public:     static x::reality::matrix translate(const x::reality::matrix & m, const x::reality::vector & v);
        public:     static x::reality::matrix rotate(const x::reality::matrix & m, x::real angle, const x::reality::vector & v);
        public:     static x::reality::matrix rotate(const x::reality::matrix & m, const x::reality::vector & v);
        public:     static x::reality::matrix rotate(const x::reality::matrix & m, const x::reality::vector & angle, const x::reality::vector & axis);
        public:     static x::reality::matrix rotate(x::real angle, const x::reality::vector & v);
        public:     static x::reality::matrix scale(const x::reality::matrix & m, const x::reality::vector & v);
        public:     inline const x::real * data() const
                    {
                        return x::matrix<x::real>::data();
                    }
        public:     inline x::reality::vector operator[](x::uint64 i) const
                    {
                        assertion(__row <= i);

                        return x::reality::vector(__reference, i * __column, __column);
                    }
        public:     x::reality::matrix & operator*=(const x::real & value);
        public:     x::reality::matrix & operator+=(const x::reality::matrix & o);
        public:     x::reality::matrix & operator-=(const x::reality::matrix & o);
        public:     x::reality::matrix & operator=(const x::reality::matrix & o);
        public:     x::reality::matrix & operator=(x::reality::matrix && o) noexcept;
        public:     matrix(const x::reality::vector & first, const x::reality::vector & second, const x::reality::vector & third, const x::reality::vector & fourth);
        public:     matrix();
        public:     matrix(const x::reality::matrix & o);
        public:     matrix(x::reality::matrix && o) noexcept;
        public:     ~matrix() override;
        public:     friend x::reality::matrix operator*(const x::reality::matrix & x, const x::real & y)
                    {
                        x::reality::matrix result = x;
                        result *= y;
                        return result;
                    }
        public:     friend x::reality::matrix operator*(const x::real & x, const x::reality::matrix & y)
                    {
                        x::reality::matrix result = y;
                        result *= x;
                        return result;
                    }
        public:     friend x::reality::matrix operator*(const x::reality::matrix & x, const x::reality::matrix & y)
                    {
                        assertion(x.__column != y.__row || x.__row == 0 || y.__column == 0);
                        assertion(x.__row != 4 || y.__column != 4);

                        x::reality::matrix result;
                        x::array<x::real> & container = result.__reference.get();
                        const x::array<x::real> & _x = x.__reference.get();
                        const x::array<x::real> & _y = y.__reference.get();
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
        public:     friend x::reality::vector operator*(const x::reality::matrix & m, const x::reality::vector & v)
                    {
                        x::reality::vector result;
                        result[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3];
                        result[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3];
                        result[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3];
                        result[3] = m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3];
                        return result;
                    }
        };
    }
}

#endif // __X_REALITY__MATRIX__HH__
