#include "light.hh"
#include "application.hh"

#include <x/console.hh>

namespace x
{
    namespace graphics
    {
        light::light(const x::initializer<x::float32> & position, const x::initializer<x::float32> & color, x::float32 ambient)
        :   __position(position),
            __color(color),
            __ambient(ambient)
        {
        }

        light::light()
        :   __position(),
            __color(),
            __ambient()
        {
        }

        light::light(const light & o)
        :   __position(o.__position),
            __color(o.__color),
            __ambient(o.__ambient)
        {
        }

        light::light(light && o) noexcept
        :   __position(x::move(o.__position)),
            __color(x::move(o.__color)),
            __ambient(o.__ambient)
        {
            o.__ambient = 0.0f;
        }

        light::~light()
        {
        }

        light & light::operator=(const light & o)
        {
            if(&o != this)
            {
                __position = o.__position;
                __color = o.__color;
                __ambient = o.__ambient;
            }
            return *this;
        }

        light & light::operator=(light && o) noexcept
        {
            if(&o != this)
            {
                __position = x::move(o.__position);
                __color = x::move(o.__color);
                __ambient = o.__ambient;
            }
            return *this;
        }

        void light::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            if(index < strings.size())
            {
                if(strings[index] == "position")
                {
                    __position.exec(strings, ++index);
                    x::graphics::application::refresh();
                }
                else if(strings[index] == "color")
                {
                    __color.exec(strings, ++index);
                    x::graphics::application::refresh();
                }
                else if(strings[index] == "ambient")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        __ambient = x::graphics::util::real32(strings[index]);
                    }
                    else
                    {
                        x::console::out << __ambient << x::endl;
                    }
                    x::graphics::application::refresh();
                }
                else
                {
                    x::console::out << "unknown command => ";
                    for(x::uint64 i = 0; i < strings.size(); i++)
                    {
                        x::console::out << strings[i] << " ";
                    }
                    x::console::out << x::endl;
                }
            }
            else
            {
                x::console::out << "{"
                                << "\"position\": " << __position << ","
                                << "\"color\": " << __color << ","
                                << "\"ambient\": " << __ambient
                                << "}"
                                << x::endl;
            }
        }
    }
}
