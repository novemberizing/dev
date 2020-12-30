#include "camera.hh"
#include "application.hh"

#include <x/console.hh>

namespace x
{
    namespace graphics
    {
        camera::camera(const x::initializer<x::float32> & position)
        :   __center(),
            __up({0.0f, 1.0f, 0.0f}),
            __position(position),
            __matrix()
        {
            __matrix = x::graphics::matrix::lookat(__position, __center, __up);
        }

        camera::camera()
        :   __center(),
            __up({0.0f, 1.0f, 0.0f}),
            __position(),
            __matrix()
        {
            __matrix = x::graphics::matrix::lookat(__position, __center, __up);
        }

        camera::camera(const camera & o)
        :   __center(o.__center),
            __up(o.__up),
            __position(o.__position),
            __matrix(o.__matrix)
        {
        }

        camera::camera(camera && o) noexcept
        :   __center(x::move(o.__center)),
            __up(x::move(o.__up)),
            __position(x::move(o.__position)),
            __matrix(x::move(o.__matrix))
        {
        }

        camera::~camera()
        {
        }

        camera & camera::operator=(const camera & o)
        {
            if(&o != this)
            {
                __center = o.__center;
                __up = o.__up;
                __position = o.__position;
                __matrix = o.__matrix;
            }
            return *this;
        }

        camera & camera::operator=(camera && o) noexcept
        {
            if(&o != this)
            {
                __center = x::move(o.__center);
                __up = x::move(o.__up);
                __position = x::move(o.__position);
                __matrix = x::move(o.__matrix);
            }
            return *this;
        }

        void camera::refresh()
        {
            __matrix = x::graphics::matrix::lookat(__position, __center, __up);
        }

        void camera::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            if(index < strings.size())
            {
                if(strings[index] == "position")
                {
                    __position.exec(strings, ++index);
                    x::graphics::application::refresh();
                }
                else if(strings[index] == "up")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        // TODO:
                        x::console::out << __up << x::endl;
                    }
                    else
                    {
                        x::console::out << __up << x::endl;
                    }
                    x::graphics::application::refresh();
                }
                else if(strings[index] == "center")
                {
                    __center.exec(strings, ++index);
                    x::graphics::application::refresh();
                }
                else
                {
                    x::graphics::util::unknown(strings);
                }
            }
            else
            {
                x::console::out << "{"
                                << "\"position\": " << __position << ","
                                << "\"center\": " << __center << ","
                                << "\"up\": " << __up << ","
                                << "}"
                                << x::endl;
            }
        }
    }
}
