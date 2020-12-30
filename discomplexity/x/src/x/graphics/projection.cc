#include "projection.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        projection::projection(x::float32 aspect)
        :   __fovy(45.0f),
            __aspect(aspect),
            __near(0.1f),
            __far(1000.0f),
            __matrix()
        {
            __matrix = x::graphics::matrix::perspective(x::math::radian(__fovy), __aspect, __near, __far);
        }

        projection::projection()
        :   __fovy(45.0f),
            __aspect(1.0f),
            __near(0.1f),
            __far(1000.0f),
            __matrix()
        {
            __matrix = x::graphics::matrix::perspective(x::math::radian(__fovy), __aspect, __near, __far);
        }

        projection::projection(const projection & o)
        :   __fovy(o.__fovy),
            __aspect(o.__aspect),
            __near(o.__near),
            __far(o.__far),
            __matrix(o.__matrix)
        {
        }

        projection::projection(projection && o) noexcept
        :   __fovy(o.__fovy),
            __aspect(o.__aspect),
            __near(o.__near),
            __far(o.__far),
            __matrix(o.__matrix)
        {
            o.__fovy = 45.0f;
            o.__aspect = 1.0f;
            o.__near = 0.1f;
            o.__far = 1000.0f;
            o.__matrix = x::graphics::matrix::perspective(x::math::radian(o.__fovy), o.__aspect, o.__near, o.__far);
        }

        projection::~projection()
        {
            __fovy = 45.0f;
            __aspect = 1.0f;
            __near = 0.1f;
            __far = 1000.0f;
        }

        projection & projection::operator=(const projection & o)
        {
            if(&o != this)
            {
                __fovy = o.__fovy;
                __aspect = o.__aspect;
                __near = o.__near;
                __far = o.__far;
                __matrix = o.__matrix;
            }
            return *this;
        }

        projection & projection::operator=(projection && o) noexcept
        {
            if(&o != this)
            {
                __fovy = o.__fovy;
                __aspect = o.__aspect;
                __near = o.__near;
                __far = o.__far;
                __matrix = o.__matrix;

                o.__fovy = 45.0f;
                o.__aspect = 1.0f;
                o.__near = 0.1f;
                o.__far = 1000.0f;
                o.__matrix = x::graphics::matrix::perspective(x::math::radian(o.__fovy), o.__aspect, o.__near, o.__far);
            }
            return *this;
        }

        void projection::refresh()
        {
            __matrix = x::graphics::matrix::perspective(x::math::radian(__fovy), __aspect, __near, __far);
        }

        void projection::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            if(index < strings.size())
            {
                if(strings[index] == "fovy")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        __fovy = x::graphics::util::real32(strings[index]);
                        x::graphics::application::refresh();
                    }
                    else
                    {
                        x::console::out << __fovy << x::endl;
                    }
                }
                else if(strings[index] == "aspect")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        __aspect = x::graphics::util::real32(strings[index]);
                        x::graphics::application::refresh();
                    }
                    else
                    {
                        x::console::out << __aspect << x::endl;
                    }
                }
                else if(strings[index] == "near")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        __near = x::graphics::util::real32(strings[index]);
                        x::graphics::application::refresh();
                    }
                    else
                    {
                        x::console::out << __near << x::endl;
                    }

                }
                else if(strings[index] == "far")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        __far = x::graphics::util::real32(strings[index]);
                        x::graphics::application::refresh();
                    }
                    else
                    {
                        x::console::out << __far << x::endl;
                    }
                }
                else
                {
                    x::graphics::util::unknown(strings);
                }
            }
            else
            {
                x::console::out << "{"
                                << "\"fovy\": " << __fovy << ","
                                << "\"aspect\": " << __aspect << ","
                                << "\"near\": " << __near << ","
                                << "\"far\": " << __far
                                << "}" << x::endl;
            }
        }
    }
}
