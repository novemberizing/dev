#include "program.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        program::program(const x::string & name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms)
        :   __name(name),
            __id(0),
            __shaders(list),
            __uniforms()
        {
            for(typename x::initializer<x::string>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
            {
                __uniforms.put(*it, -1);
            }
            x::console::out << __uniforms.size() << x::endl;
        }

        program::program(x::string && name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms)
        :   __name(x::move(name)),
            __id(0),
            __shaders(list),
            __uniforms()
        {
            for(typename x::initializer<x::string>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
            {
                __uniforms.put(*it, -1);
            }
            x::console::out << __uniforms.size() << x::endl;
        }

        program::program(const x::string & name, const x::initializer<x::graphics::shader> & list)
        :   __name(name),
            __id(0),
            __shaders(list),
            __uniforms()
        {
        }

        program::program(x::string && name, const x::initializer<x::graphics::shader> & list)
        :   __name(x::move(name)),
            __id(0),
            __shaders(list),
            __uniforms()
        {
        }

        program::program()
        :   __name(),
            __id(),
            __shaders(),
            __uniforms()
        {
        }

        program::program(const program & o)
        :   __name(o.__name),
            __id(o.__id),
            __shaders(o.__shaders),
            __uniforms(o.__uniforms)
        {
        }

        program::program(program && o) noexcept
        :   __name(x::move(o.__name)),
            __id(o.__id),
            __shaders(x::move(o.__shaders)),
            __uniforms(x::move(o.__uniforms))
        {
            o.__id = 0;
        }

        program::~program()
        {
        }

        program & program::operator=(const program & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __id = o.__id;
                __shaders = o.__shaders;
                __uniforms = o.__uniforms;
            }
            return *this;
        }

        program & program::operator=(program && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __id = o.__id;
                __shaders = x::move(o.__shaders);
                __uniforms = x::move(o.__uniforms);

                o.__id = 0;
            }
            return *this;
        }
    }
}
