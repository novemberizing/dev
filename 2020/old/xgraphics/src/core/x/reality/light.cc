#include "light.hh"

namespace x
{
    namespace reality
    {
        x::reality::light x::reality::light::__main({30.0f, 4.0f, -14.0f}, {1.0f, 1.0f, 1.0f}, 0.8f);

        light::light(const x::initializer<x::real> & location, const x::initializer<x::real> & color, x::real ambient)
        :   __location(location),
            __color(color),
            __ambient(ambient)
        {
        }

        light::light()
        :   __location(),
            __color(),
            __ambient()
        {
        }

        light::light(const x::reality::light & o)
        :   __location(o.__location),
            __color(o.__color),
            __ambient(o.__ambient)
        {
        }

        light::light(x::reality::light && o) noexcept
        :   __location(x::move(o.__location)),
            __color(x::move(o.__color)),
            __ambient(o.__ambient)
        {
            o.__ambient = 0.0f;
        }

        light::~light()
        {
        }

        x::reality::light & light::operator=(const x::reality::light & o)
        {
            if(&o != this)
            {
                __location = o.__location;
                __color = o.__color;
                __ambient = o.__ambient;
            }
            return *this;
        }

        x::reality::light & light::operator=(x::reality::light && o) noexcept
        {
            if(&o != this)
            {
                __location = x::move(o.__location);
                __color = x::move(o.__color);
                __ambient = o.__ambient;
            }
            return *this;
        }

        void light::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            if(index < strings.size())
            {
                if(strings[index] == "location")
                {
                    __location.exec(strings, ++index);
                }
                else if(strings[index] == "color")
                {
                    __color.exec(strings, ++index);
                }
                else if(strings[index] == "ambient")
                {
                    index = index + 1;
                    if(index < strings.size())
                    {
                        __ambient = x::real32::from(strings[index]);
                    }
                    else
                    {
                        x::console::out << __ambient << x::endl;
                    }
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
                                << "\"location\": " << __location << ","
                                << "\"color\": " << __color << ","
                                << "\"ambient\": " << __ambient
                                << "}"
                                << x::endl;
            }
        }
    }
}
