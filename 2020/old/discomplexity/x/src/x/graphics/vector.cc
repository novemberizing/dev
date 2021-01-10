#include "vector.hh"

#include <x/console.hh>

namespace x
{
    namespace graphics
    {
        vector::vector(const x::reference<x::array<x::float32> > reference, x::uint64 offset, x::uint64 length)
        :   x::vector<x::float32>(reference, offset, length)
        {
        }

        vector::vector(x::array<x::float32> && o)
        :   x::vector<x::float32>(x::move(o))
        {
        }

        vector::vector()
        :   x::vector<x::float32>(4)
        {
        }

        vector::vector(const vector & o)
        :   x::vector<x::float32>(o)
        {
        }

        vector::vector(vector && o) noexcept
        :   x::vector<x::float32>(x::move(o))
        {
        }

        vector::vector(const x::initializer<x::float32> & list)
        :   x::vector<x::float32>(4)
        {
            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end(); ++it)
            {
                x::vector<x::float32>::operator[](i++) = *it;
            }
        }

        vector::vector(const x::initializer<x::float32> & list, x::float32 w)
        :   x::vector<x::float32>(4)
        {
            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end() && i < 3; ++it)
            {
                x::vector<x::float32>::operator[](i++) = *it;
            }
            x::vector<x::float32>::operator[](3) = w;
        }

        vector::vector(x::float32 x, x::float32 y, x::float32 z)
        :   x::vector<x::float32>(4)
        {
            x::vector<x::float32>::operator[](0) = x;
            x::vector<x::float32>::operator[](1) = y;
            x::vector<x::float32>::operator[](2) = z;
        }

        vector::vector(x::float32 x, x::float32 y, x::float32 z, x::float32 w)
        :   x::vector<x::float32>(4)
        {
            x::vector<x::float32>::operator[](0) = x;
            x::vector<x::float32>::operator[](1) = y;
            x::vector<x::float32>::operator[](2) = z;
            x::vector<x::float32>::operator[](3) = w;
        }

        vector::~vector()
        {
        }

        vector & vector::operator=(const vector & o)
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator=(o);
            }
            return *this;
        }

        vector & vector::operator=(vector && o) noexcept
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator=(x::move(o));
            }
            return *this;
        }

        vector & vector::operator=(const x::initializer<x::float32> & list)
        {
            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end(); ++it)
            {
                x::vector<x::float32>::operator[](i++) = *it;
            }
            for(; i < 4; i++)
            {
                x::vector<x::float32>::operator[](i) = 0;
            }
            return *this;
        }

        vector & vector::operator<<(const vector & o)
        {
            x::vector<x::float32>::operator[](0) = o[0];
            x::vector<x::float32>::operator[](1) = o[1];
            x::vector<x::float32>::operator[](2) = o[2];
            x::vector<x::float32>::operator[](3) = o[3];
        }

        vector & vector::operator-=(const vector & o)
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator[](0) -= o[0];
                x::vector<x::float32>::operator[](1) -= o[1];
                x::vector<x::float32>::operator[](2) -= o[2];
                x::vector<x::float32>::operator[](3) -= o[3];
                if(x::vector<x::float32>::operator[](3) != 0 && x::vector<x::float32>::operator[](3) != 1)
                {
                    // x::console::out << x::vector<x::float32>::operator[](3) << x::endl;
                    // exceptional();
                }
            }
            return *this;
        }

        vector & vector::operator+=(const vector & o)
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator[](0) += o[0];
                x::vector<x::float32>::operator[](1) += o[1];
                x::vector<x::float32>::operator[](2) += o[2];
                x::vector<x::float32>::operator[](3) += o[3];
                if(x::vector<x::float32>::operator[](3) != 0 && x::vector<x::float32>::operator[](3) != 1)
                {
                    // exceptional();
                }
            }
            return *this;
        }

        vector & vector::operator*=(const x::float32 & v)
        {
            x::vector<x::float32>::operator[](0) *= v;
            x::vector<x::float32>::operator[](1) *= v;
            x::vector<x::float32>::operator[](2) *= v;
            return *this;
        }

        void vector::set(x::float32 x, x::float32 y, x::float32 z, x::float32 w)
        {
            x::vector<x::float32>::operator[](0) = x;
            x::vector<x::float32>::operator[](1) = y;
            x::vector<x::float32>::operator[](2) = z;
            x::vector<x::float32>::operator[](3) = w;
        }

        void vector::exec(const x::array<x::string> & strings, x::uint64 index, function<float32 (float32)> in, function<float32 (float32)> out)
        {
            if(index < strings.size())
            {
                if(strings[index] == "x")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        x(in ? in(x::graphics::util::real32(strings[index])) : x::graphics::util::real32(strings[index]));
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
                        y(in ? in(x::graphics::util::real32(strings[index])) : x::graphics::util::real32(strings[index]));
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
                        z(in ? in(x::graphics::util::real32(strings[index])) : x::graphics::util::real32(strings[index]));
                    }
                    else
                    {
                        x::console::out << (out ? out(z()) : z()) << x::endl;
                    }
                }
                else
                {
                    x(in ? in(x::graphics::util::real32(strings[index++])) : x::graphics::util::real32(strings[index++]));
                    y(in ? in(x::graphics::util::real32(strings[index++])) : x::graphics::util::real32(strings[index++]));
                    z(in ? in(x::graphics::util::real32(strings[index++])) : x::graphics::util::real32(strings[index++]));
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
