#include "matrix.hh"

namespace x
{
    namespace reality
    {
        const x::reality::matrix x::reality::matrix::identity(x::reality::vector({1.0f, 0.0f, 0.0f, 0.0f}), x::reality::vector(0.0f, 1.0f, 0.0f, 0.0f), x::reality::vector(0.0f, 0.0f, 1.0f, 0.0f), x::reality::vector(0.0f, 0.0f, 0.0f, 1.0f));

        x::reality::matrix matrix::orthogonal(x::real left, x::real right, x::real bottom, x::real top)
        {
            x::reality::matrix result;

            result[0][0] = 2.0f / (right - left);
            result[1][1] = 2.0f / (top - bottom);
            result[2][2] = -1.0f;
            result[3][0] = - (right + left) / (right - left);
            result[3][1] = - (top + bottom) / (top - bottom);
            result[3][3] = 1.0f;

            return result;
        }

        x::reality::matrix matrix::rotate(x::real angle, const x::reality::vector & v)
        {
            return matrix::rotate(matrix::identity, angle, v);
        }

        x::reality::matrix matrix::rotate(const x::reality::matrix & m, const x::reality::vector & angle, const x::reality::vector & axis)
        {
            x::reality::matrix result = m;
            if(angle.x() != 0)
            {
                result = matrix::rotate(result, angle.x(), axis);
            }
            if(angle.y() != 0)
            {
                result = matrix::rotate(result, angle.y(), axis);
            }
            if(angle.z() != 0)
            {
                result = matrix::rotate(result, angle.z(), axis);
            }
            return result;
        }

        x::reality::matrix matrix::rotate(const x::reality::matrix & m, const x::reality::vector & v)
        {
            x::reality::matrix result = m;

            result = matrix::rotate(result, v.x(), {1.0f, 0.0f, 0.0f});
            result = matrix::rotate(result, v.y(), {0.0f, 1.0f, 0.0f});
            result = matrix::rotate(result, v.z(), {0.0f, 0.0f, 1.0f});

            return result;
        }

        x::reality::matrix matrix::rotate(const x::reality::matrix & m, x::real angle, const x::reality::vector & v)
        {
            x::real c = x::cos(angle);
            x::real s = x::sin(angle);
            x::reality::vector axis = x::reality::vector::normalize(v);
            x::reality::vector temp = axis * (1.0f - c);

            x::reality::matrix rotation;

            rotation[0][0] = c + temp[0] * axis[0];
    		rotation[0][1] = temp[0] * axis[1] + s * axis[2];
    		rotation[0][2] = temp[0] * axis[2] - s * axis[1];

    		rotation[1][0] = temp[1] * axis[0] - s * axis[2];
    		rotation[1][1] = c + temp[1] * axis[1];
    		rotation[1][2] = temp[1] * axis[2] + s * axis[0];

    		rotation[2][0] = temp[2] * axis[0] + s * axis[1];
    		rotation[2][1] = temp[2] * axis[1] - s * axis[0];
    		rotation[2][2] = c + temp[2] * axis[2];

            x::reality::matrix result;

            result[0] = m[0] * rotation[0][0] + m[1] * rotation[0][1] + m[2] * rotation[0][2];
    		result[1] = m[0] * rotation[1][0] + m[1] * rotation[1][1] + m[2] * rotation[1][2];
    		result[2] = m[0] * rotation[2][0] + m[1] * rotation[2][1] + m[2] * rotation[2][2];
    		result[3] = m[3];

            return result;
        }

        x::reality::matrix matrix::scale(const x::reality::matrix & m, const x::reality::vector & v)
        {
            x::reality::matrix result;
            result[0] = m[0] * v[0];
            result[1] = m[1] * v[1];
            result[2] = m[2] * v[2];
            result[3] = m[3];
            return result;
        }

        x::reality::matrix matrix::translate(const x::reality::matrix & m, const x::reality::vector & v)
        {
            x::reality::matrix result = m;
            result[3] = (m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3]);
            return result;
        }

        x::reality::matrix matrix::perspective(x::real fovy, x::real aspect, x::real near, x::real far)
        {

            x::real half = x::tan(fovy / 2.0f);
            x::reality::matrix result;
            result[0][0] = 1.0f / (aspect * half);
            result[1][1] = 1.0f / half;
            result[2][2] = (far + near) / (near - far);
            result[2][3] = -1.0f;
            result[3][2] = -(2.0f * far * near) / (far - near);
            return result;
        }

        x::reality::matrix matrix::lookat(const x::reality::vector & eye, const x::reality::vector & center, const x::reality::vector & up)
        {
            x::reality::vector f = vector::normalize(center - eye);
            x::reality::vector s = vector::normalize(vector::cross(f, up));
            x::reality::vector u = vector::cross(s, f);
            x::reality::matrix result = matrix::identity;

            result[0][0] =  s[0];
            result[1][0] =  s[1];
            result[2][0] =  s[2];
            result[0][1] =  u[0];
            result[1][1] =  u[1];
            result[2][1] =  u[2];
            result[0][2] = -f[0];
            result[1][2] = -f[1];
            result[2][2] = -f[2];
            result[3][0] = -vector::dot(s, eye);
            result[3][1] = -vector::dot(u, eye);
            result[3][2] =  vector::dot(f, eye);

            return result;
        }

        x::reality::matrix & matrix::operator*=(const x::real & value)
        {
            x::array<x::real> & container = __reference.get();
            for(x::uint64 i = 0; i < __row; i++)
            {
                for(x::uint64 j = 0; j < __column; j++)
                {
                    container[i * __column + j] *= value;
                }
            }
            return *this;
        }

        x::reality::matrix & matrix::operator+=(const x::reality::matrix & o)
        {
            assertion(__row != o.__row || __column != o.__column);

            x::array<x::real> & _x = __reference.get();
            const x::array<x::real> & _y = o.__reference.get();
            for(x::uint64 i = 0; i < __row; i++)
            {
                for(x::uint64 j = 0; j < __column; j++)
                {
                    _x[i * __column + j] = _x[i * __column + j] + _y[i * __column + j];
                }
            }
            return *this;
        }

        x::reality::matrix & matrix::operator-=(const x::reality::matrix & o)
        {
            assertion(__row != o.__row || __column != o.__column);

            x::array<x::real> & _x = __reference.get();
            const x::array<x::real> & _y = o.__reference.get();
            for(x::uint64 i = 0; i < __row; i++)
            {
                for(x::uint64 j = 0; j < __column; j++)
                {
                    _x[i * __column + j] = _x[i * __column + j] - _y[i * __column + j];
                }
            }
            return *this;
        }

        x::reality::matrix & matrix::operator=(const x::reality::matrix & o)
        {
            if(&o != this)
            {
                x::matrix<x::real>::operator=(o);
            }
            return *this;
        }

        x::reality::matrix & matrix::operator=(x::reality::matrix && o) noexcept
        {
            if(&o != this)
            {
                x::matrix<x::real>::operator=(x::move(o));
            }
            return *this;
        }

        matrix::matrix(const x::reality::vector & first, const x::reality::vector & second, const x::reality::vector & third, const x::reality::vector & fourth)
        :   x::matrix<x::real>(4, 4)
        {
            x::array<x::real> & container = __reference.get();

            container[__column * 0 + 0] = first[0];
            container[__column * 0 + 1] = first[1];
            container[__column * 0 + 2] = first[2];
            container[__column * 0 + 3] = first[3];

            container[__column * 1 + 0] = second[0];
            container[__column * 1 + 1] = second[1];
            container[__column * 1 + 2] = second[2];
            container[__column * 1 + 3] = second[3];

            container[__column * 2 + 0] = third[0];
            container[__column * 2 + 1] = third[1];
            container[__column * 2 + 2] = third[2];
            container[__column * 2 + 3] = third[3];

            container[__column * 3 + 0] = fourth[0];
            container[__column * 3 + 1] = fourth[1];
            container[__column * 3 + 2] = fourth[2];
            container[__column * 3 + 3] = fourth[3];
        }

        matrix::matrix()
        :   x::matrix<x::real>(4, 4)
        {
        }

        matrix::matrix(const x::reality::matrix & o)
        :   x::matrix<x::real>(o)
        {
        }

        matrix::matrix(x::reality::matrix && o) noexcept
        :   x::matrix<x::real>(x::move(o))
        {
        }

        matrix::~matrix()
        {
        }
    }
}
