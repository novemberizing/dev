#include "matrix.hh"

namespace x
{
    namespace graphics
    {
        x::graphics::matrix matrix::identity()
        {
            x::graphics::matrix result;
            result[0][0] = 1;
            result[1][1] = 1;
            result[2][2] = 1;
            result[3][3] = 1;
            return result;
        }
        // TODO : RENAME
        x::graphics::matrix matrix::convert()
        {
            x::graphics::matrix result;
            result[0][0] = 1;
            result[1][2] = 1;
            result[2][1] = 1;
            result[3][3] = 1;

            return result;
        }

        x::graphics::matrix matrix::rotate(x::float32 angle, const x::graphics::vector & v)
        {
            return matrix::rotate(matrix::identity(), angle, v);
        }

        x::graphics::matrix matrix::rotate(const x::graphics::matrix & m, x::float32 angle, const x::graphics::vector & v)
        {
            x::float32 c = x::math::cos(angle);
            x::float32 s = x::math::sin(angle);
            x::graphics::vector axis = x::graphics::vector::normalize(v);
            x::graphics::vector temp = axis * (1.0f - c);

            x::graphics::matrix rotation;

            rotation[0][0] = c + temp[0] * axis[0];
    		rotation[0][1] = temp[0] * axis[1] + s * axis[2];
    		rotation[0][2] = temp[0] * axis[2] - s * axis[1];

    		rotation[1][0] = temp[1] * axis[0] - s * axis[2];
    		rotation[1][1] = c + temp[1] * axis[1];
    		rotation[1][2] = temp[1] * axis[2] + s * axis[0];

    		rotation[2][0] = temp[2] * axis[0] + s * axis[1];
    		rotation[2][1] = temp[2] * axis[1] - s * axis[0];
    		rotation[2][2] = c + temp[2] * axis[2];

            x::graphics::matrix result;

            result[0] << m[0] * rotation[0][0] + m[1] * rotation[0][1] + m[2] * rotation[0][2];
    		result[1] << m[0] * rotation[1][0] + m[1] * rotation[1][1] + m[2] * rotation[1][2];
    		result[2] << m[0] * rotation[2][0] + m[1] * rotation[2][1] + m[2] * rotation[2][2];
    		result[3] << m[3];

            return result;
        }

        x::graphics::matrix matrix::scale(const x::graphics::matrix & m, const x::graphics::vector & v)
        {
            x::graphics::matrix result;
            result[0] << m[0] * v[0];
            result[1] << m[1] * v[1];
            result[2] << m[2] * v[2];
            result[3] << m[3];
            return result;
        }

        x::graphics::matrix matrix::translate(const x::graphics::matrix & m, const x::graphics::vector & v)
        {
            x::graphics::matrix result = m;
            result[3] << (m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3]);
            return result;
        }

        x::graphics::matrix matrix::perspective(float32 fovy, float32 aspect, float32 near, float32 far)
        {
            x::console::out << "=========================" << x::endl;
            float32 half = x::math::tan(fovy / 2.0f);
            x::console::out << fovy << x::endl;
            x::console::out << half << x::endl;
            x::graphics::matrix result;
            result[0][0] = 1.0f / (aspect * half);
            result[1][1] = 1.0f / half;
            result[2][2] = (far + near) / (near - far);
            result[2][3] = -1.0f;
            result[3][2] = -(2.0f * far * near) / (far - near);
            return result;
        }

        x::graphics::matrix matrix::lookat(const vector & eye, const vector & center, const vector & up)
        {
            vector f = vector::normalize(center - eye);
            vector s = vector::normalize(vector::cross(f, up));
            vector u = vector::cross(s, f);
            matrix result = matrix::identity();

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

        matrix::matrix()
        :   x::matrix<x::float32>(4, 4)
        {
        }

        matrix::matrix(const matrix & o)
        :   x::matrix<x::float32>(o)
        {
        }

        matrix::matrix(matrix && o) noexcept
        :   x::matrix<x::float32>(x::move(o))
        {
        }

        matrix::~matrix()
        {
        }

        matrix & matrix::operator=(const matrix & o)
        {
            if(&o != this)
            {
                x::matrix<x::float32>::operator=(o);
            }
            return *this;
        }

        matrix & matrix::operator=(matrix && o) noexcept
        {
            if(&o != this)
            {
                x::matrix<x::float32>::operator=(x::move(o));
            }
            return *this;
        }
    }
}
