#include "color.hh"

namespace x
{
    namespace graphics
    {
        color::color(const x::initializer<x::float32> & list)
        :   x::vector<x::float32>(4)
        {
            assertion(list.size() < 3);

            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end() && i < 4; ++it, ++i)
            {
                x::vector<x::float32>::operator[](i) = *it;
            }
            if(list.size() == 3)
            {
                x::vector<x::float32>::operator[](3) = 1.0f;
            }
        }

        color::color(x::float32 r, x::float32 g, x::float32 b)
        :   x::vector<x::float32>(4)
        {
            x::vector<x::float32>::operator[](0) = r;
            x::vector<x::float32>::operator[](1) = g;
            x::vector<x::float32>::operator[](2) = b;
            x::vector<x::float32>::operator[](3) = 1.0f;
        }

        color::color(x::float32 r, x::float32 g, x::float32 b, x::float32 a)
        :   x::vector<x::float32>(4)
        {
            x::vector<x::float32>::operator[](0) = r;
            x::vector<x::float32>::operator[](1) = g;
            x::vector<x::float32>::operator[](2) = b;
            x::vector<x::float32>::operator[](3) = a;
        }

        color::color()
        :   x::vector<x::float32>(4)
        {
        }

        color::color(const color & o)
        :   x::vector<x::float32>(o)
        {
        }

        color::color(color && o) noexcept
        :   x::vector<x::float32>(x::move(o))
        {
        }

        color::~color()
        {
        }

        color & color::operator=(const color & o)
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator=(o);
            }
            return *this;
        }

        color & color::operator=(color && o) noexcept
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator=(x::move(o));
            }
            return *this;
        }

        color & color::operator=(const x::initializer<x::float32> & list)
        {
            assertion(list.size() < 3);

            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end() && i < 4; ++it, ++i)
            {
                x::vector<x::float32>::operator[](i) = *it;
            }
            if(list.size() == 3)
            {
                x::vector<x::float32>::operator[](3) = 1.0f;
            }
            return *this;
        }

        void color::set(x::float32 r, x::float32 g, x::float32 b)
        {
            x::vector<x::float32>::operator[](0) = r;
            x::vector<x::float32>::operator[](1) = g;
            x::vector<x::float32>::operator[](2) = b;
            x::vector<x::float32>::operator[](3) = 1.0f;
        }

        void color::set(x::float32 r, x::float32 g, x::float32 b, x::float32 a)
        {
            x::vector<x::float32>::operator[](0) = r;
            x::vector<x::float32>::operator[](1) = g;
            x::vector<x::float32>::operator[](2) = b;
            x::vector<x::float32>::operator[](3) = a;
        }

        void color::set(const x::initializer<x::float32> & list)
        {
            assertion(list.size() < 3);
            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end() && i < 4; ++it, ++i)
            {
                x::vector<x::float32>::operator[](i) = *it;
            }
            if(list.size() == 3)
            {
                x::vector<x::float32>::operator[](3) = 1.0f;
            }
        }

        void color::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            if(index < strings.size())
            {
                if(strings[index] == "r" || strings[index] == "red")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        red(x::graphics::util::real32(strings[index]));
                    }
                    else
                    {
                        x::console::out << red() << x::endl;
                    }
                }
                else if(strings[index] == "g" || strings[index] == "green")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        green(x::graphics::util::real32(strings[index]));
                    }
                    else
                    {
                        x::console::out << green() << x::endl;
                    }
                }
                else if(strings[index] == "b" || strings[index] == "blue")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        blue(x::graphics::util::real32(strings[index]));
                    }
                    else
                    {
                        x::console::out << blue() << x::endl;
                    }
                }
                else
                {
                    red(x::graphics::util::real32(strings[index++]));
                    green(x::graphics::util::real32(strings[index++]));
                    blue(x::graphics::util::real32(strings[index++]));
                }
            }
            else
            {
                x::console::out << *this << x::endl;
            }
        }
    }
}
