#include "color.hh"

namespace x
{
    namespace reality
    {
        color::color(const x::initializer<x::real> & list)
        :   x::vector<x::real>(4)
        {
            assertion(list.size() < 3);

            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 4; ++it, ++i)
            {
                x::vector<x::real>::operator[](i) = *it;
            }
            if(list.size() == 3)
            {
                x::vector<x::real>::operator[](3) = 1.0f;
            }
        }

        color::color(x::real r, x::real g, x::real b)
        :   x::vector<x::real>(4)
        {
            x::vector<x::real>::operator[](0) = r;
            x::vector<x::real>::operator[](1) = g;
            x::vector<x::real>::operator[](2) = b;
            x::vector<x::real>::operator[](3) = 1.0f;
        }

        color::color(x::real r, x::real g, x::real b, x::real a)
        :   x::vector<x::real>(4)
        {
            x::vector<x::real>::operator[](0) = r;
            x::vector<x::real>::operator[](1) = g;
            x::vector<x::real>::operator[](2) = b;
            x::vector<x::real>::operator[](3) = a;
        }

        color::color()
        :   x::vector<x::real>(4)
        {
            x::vector<x::real>::operator[](3) = 1.0f;
        }

        color::color(const x::reality::color & o)
        :   x::vector<x::real>(o)
        {
        }

        color::color(x::reality::color && o) noexcept
        :   x::vector<x::real>(x::move(o))
        {
        }

        color::~color()
        {
        }

        x::reality::color & color::operator=(const x::reality::color & o)
        {
            if(&o != this)
            {
                x::vector<x::real>::operator=(o);
            }
            return *this;
        }

        x::reality::color & color::operator=(x::reality::color && o) noexcept
        {
            if(&o != this)
            {
                x::vector<x::real>::operator=(x::move(o));
            }
            return *this;
        }

        x::reality::color & color::operator=(const x::initializer<x::real> & list)
        {
            assertion(list.size() < 3);

            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 4; ++it, ++i)
            {
                x::vector<x::real>::operator[](i) = *it;
            }
            return *this;
        }

        void color::set(x::real r, x::real g, x::real b)
        {
            x::vector<x::real>::operator[](0) = r;
            x::vector<x::real>::operator[](1) = g;
            x::vector<x::real>::operator[](2) = b;
            x::vector<x::real>::operator[](3) = 1.0f;
        }

        void color::set(x::real r, x::real g, x::real b, x::real a)
        {
            x::vector<x::real>::operator[](0) = r;
            x::vector<x::real>::operator[](1) = g;
            x::vector<x::real>::operator[](2) = b;
            x::vector<x::real>::operator[](3) = a;
        }

        void color::set(const x::initializer<x::real> & list)
        {
            assertion(list.size() < 3);
            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 4; ++it, ++i)
            {
                x::vector<x::real>::operator[](i) = *it;
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
                        red(x::real32::from(strings[index]));
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
                        green(x::real32::from(strings[index]));
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
                        blue(x::real32::from(strings[index]));
                    }
                    else
                    {
                        x::console::out << blue() << x::endl;
                    }
                }
                else
                {
                    red(x::real32::from(strings[index++]));
                    green(x::real32::from(strings[index++]));
                    blue(x::real32::from(strings[index++]));
                }
            }
            else
            {
                x::console::out << *this << x::endl;
            }
        }
    }
}
