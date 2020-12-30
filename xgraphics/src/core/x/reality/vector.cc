#include "vector.hh"

namespace x
{
    namespace reality
    {
        const x::reality::vector vector::center({0.0f, 0.0f, 0.0f, 1.0f});
        const x::reality::vector vector::up({0.0f, 1.0f, 0.0f});
        const x::reality::vector vector::front({0.0f, 0.0f, 1.0f});

        const x::reality::vector x::reality::vector::zero({0.0f, 0.0f, 0.0f});
        const x::reality::vector x::reality::vector::one({1.0f, 1.0f, 1.0f});

        x::reality::vector vector::radian(const x::reality::vector & o)
        {
            x::reality::vector result;
            result[0] = x::radian(o[0]);
            result[1] = x::radian(o[1]);
            result[2] = x::radian(o[2]);
            return result;
        }

        x::reality::vector vector::degree(const x::reality::vector & o)
        {
            x::reality::vector result;
            result[0] = x::degree(o[0]);
            result[1] = x::degree(o[1]);
            result[2] = x::degree(o[2]);
            return result;
        }

        x::reality::vector vector::normalize(const x::reality::vector & o)
        {
            x::real dot = x::sqrt<x::real>(x::reality::vector::dot(o, o));
            const x::array<x::real> & container = o.__reference.get();
            x::reality::vector result;
            for(x::uint64 i = 0; i < o.__length; i++)
            {
                result[i] = container[o.__offset + i] / dot;
            }
            return result;
        }

        x::reality::vector vector::cross(const x::reality::vector & x, const x::reality::vector & y)
        {
            assertion(x.__length != y.__length || x.__length < 3);
            x::reality::vector result;
            result[0] = (x[1] * y[2] - x[2] * y[1]);
            result[1] = (x[2] * y[0] - x[0] * y[2]);
            result[2] = (x[0] * y[1] - x[1] * y[0]);
            return result;
        }

        x::real vector::dot(const x::reality::vector & x, const x::reality::vector & y)
        {
            assertion(x.__length != y.__length || x.__length == 0);

            x::real result = x[0] * y[0];
            for(x::uint64 i = 1; i < x.__length; i++)
            {
                result += (x[i] * y[i]);
            }
            return result;
        }

        vector::vector(const x::reference<x::array<x::real> > reference, x::uint64 offset, x::uint64 length)
        :   x::vector<x::real>(reference, offset, length)
        {
        }

        vector::vector(x::array<x::real> && o)
        :   x::vector<x::real>(x::move(o))
        {
        }

        vector::vector()
        :   x::vector<x::real>(4)
        {
        }

        vector::vector(const x::reality::vector & o)
        :   x::vector<x::real>(o)
        {
        }

        vector::vector(x::reality::vector && o) noexcept
        :   x::vector<x::real>(x::move(o))
        {
        }

        vector::vector(const x::initializer<x::real> & list)
        :   x::vector<x::real>(4)
        {
            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 4; ++it)
            {
                x::vector<x::real>::operator[](i++) = *it;
            }
        }

        vector::vector(const x::initializer<x::real> & list, x::real w)
        :   x::vector<x::real>(4)
        {
            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 3; ++it)
            {
                x::vector<x::real>::operator[](i++) = *it;
            }
            x::vector<x::real>::operator[](3) = w;
        }

        vector::vector(x::real x, x::real y, x::real z)
        :   x::vector<x::real>(4)
        {
            x::vector<x::real>::operator[](0) = x;
            x::vector<x::real>::operator[](1) = y;
            x::vector<x::real>::operator[](2) = z;
        }

        vector::vector(x::real x, x::real y, x::real z, x::real w)
        :   x::vector<x::real>(4)
        {
            x::vector<x::real>::operator[](0) = x;
            x::vector<x::real>::operator[](1) = y;
            x::vector<x::real>::operator[](2) = z;
            x::vector<x::real>::operator[](3) = w;
        }

        vector::~vector()
        {
        }

        x::reality::vector & vector::operator=(const x::reality::vector & o)
        {
            if(&o != this)
            {
                x::vector<x::real>::operator=(o);
            }
            return *this;
        }

        x::reality::vector & vector::operator=(x::reality::vector && o) noexcept
        {
            if(&o != this)
            {
                x::vector<x::real>::operator=(x::move(o));
            }
            return *this;
        }

        x::reality::vector & vector::operator=(const x::initializer<x::real> & list)
        {
            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 3; ++it)
            {
                x::vector<x::real>::operator[](i++) = *it;
            }
            return *this;
        }

        x::reality::vector & vector::operator-=(const x::reality::vector & o)
        {
            if(&o != this)
            {
                x::vector<x::real>::operator[](0) -= o[0];
                x::vector<x::real>::operator[](1) -= o[1];
                x::vector<x::real>::operator[](2) -= o[2];
                x::vector<x::real>::operator[](3) -= o[3];
            }
            else
            {
                x::vector<x::real>::operator[](0) = 0;
                x::vector<x::real>::operator[](1) = 0;
                x::vector<x::real>::operator[](2) = 0;
                x::vector<x::real>::operator[](3) = 0;
            }
            return *this;
        }

        x::reality::vector & vector::operator+=(const x::reality::vector & o)
        {
            if(&o != this)
            {
                x::vector<x::real>::operator[](0) += o[0];
                x::vector<x::real>::operator[](1) += o[1];
                x::vector<x::real>::operator[](2) += o[2];
                x::vector<x::real>::operator[](3) += o[3];
            }
            else
            {
                x::vector<x::real>::operator[](0) = 2 * x::vector<x::real>::operator[](0);
                x::vector<x::real>::operator[](1) = 2 * x::vector<x::real>::operator[](1);
                x::vector<x::real>::operator[](2) = 2 * x::vector<x::real>::operator[](2);
                x::vector<x::real>::operator[](3) = 2 * x::vector<x::real>::operator[](3);
            }
            return *this;
        }

        x::reality::vector & vector::operator*=(const x::real & v)
        {
            x::vector<x::real>::operator[](0) *= v;
            x::vector<x::real>::operator[](1) *= v;
            x::vector<x::real>::operator[](2) *= v;
            x::vector<x::real>::operator[](3) *= v;
            return *this;
        }

        void vector::set(x::real x, x::real y, x::real z, x::real w)
        {
            x::vector<x::real>::operator[](0) = x;
            x::vector<x::real>::operator[](1) = y;
            x::vector<x::real>::operator[](2) = z;
            x::vector<x::real>::operator[](3) = w;
        }

        void vector::exec(const x::array<x::string> & strings, x::uint64 index, function<x::real (x::real)> in, function<x::real (x::real)> out)
        {
            if(index < strings.size())
            {
                if(strings[index] == "x")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        x(in ? in(x::real32::from(strings[index])) : x::real32::from(strings[index]));
                    }
                    else
                    {
                        x::console::out << (out ? out(x()) : x()) << x::endl;
                    }
                }
                else if(strings[index] == "y")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        y(in ? in(x::real32::from(strings[index])) : x::real32::from(strings[index]));
                    }
                    else
                    {
                        x::console::out << (out ? out(y()) : y()) << x::endl;
                    }
                }
                else if(strings[index] == "z")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        z(in ? in(x::real32::from(strings[index])) : x::real32::from(strings[index]));
                    }
                    else
                    {
                        x::console::out << (out ? out(z()) : z()) << x::endl;
                    }
                }
                else
                {
                    x(in ? in(x::real32::from(strings[index++])) : x::real32::from(strings[index++]));
                    y(in ? in(x::real32::from(strings[index++])) : x::real32::from(strings[index++]));
                    z(in ? in(x::real32::from(strings[index++])) : x::real32::from(strings[index++]));
                }
            }
            else
            {
                x::console::out << "["
                                << (out ? out(x()) : x()) << ","
                                << (out ? out(y()) : y()) << ","
                                << (out ? out(z()) : z()) << ","
                                << (out ? out(w()) : w())
                                << "]"
                                << x::endl;
            }
        }

        void vector::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            exec(strings, index, nullptr, nullptr);
        }
    }
}
