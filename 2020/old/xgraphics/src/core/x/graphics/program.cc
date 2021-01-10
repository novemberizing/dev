#include "program.hh"

namespace x
{
    namespace graphics
    {
        program::program(const x::string & name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms)
        :   __name(name),
            __id(0),
            __shaders(list),
            uniforms()
        {
            for(typename x::initializer<x::string>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
            {
                this->uniforms.put(*it, -1);
            }
        }

        program::program(x::string && name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms)
        :   __name(x::move(name)),
            __id(0),
            __shaders(list),
            uniforms()
        {
            for(typename x::initializer<x::string>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
            {
                this->uniforms.put(*it, -1);
            }
        }

        program::program(const x::string & name)
        :   __name(name),
            __id(0),
            __shaders(),
            uniforms()
        {
        }

        program::program(x::string && name)
        :   __name(x::move(name)),
            __id(0),
            __shaders(),
            uniforms()
        {
        }

        program::program(const x::string & name, const x::initializer<x::string> & uniforms)
        :   __name(name),
            __id(0),
            __shaders(),
            uniforms()
        {
            for(typename x::initializer<x::string>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
            {
                this->uniforms.put(*it, -1);
            }
        }

        program::program(x::string && name, const x::initializer<x::string> & uniforms)
        :   __name(x::move(name)),
            __id(0),
            __shaders(),
            uniforms()
        {
            for(typename x::initializer<x::string>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
            {
                this->uniforms.put(*it, -1);
            }
        }

        program::program(const x::string & name, const x::initializer<x::graphics::shader> & list)
        :   __name(name),
            __id(0),
            __shaders(list),
            uniforms()
        {
        }

        program::program(x::string && name, const x::initializer<x::graphics::shader> & list)
        :   __name(x::move(name)),
            __id(0),
            __shaders(list),
            uniforms()
        {
        }

        program::program()
        :   __name(),
            __id(),
            __shaders(),
            uniforms()
        {

        }

        program::program(const x::graphics::program & o)
        :   __name(o.__name),
            __id(o.__id),
            __shaders(o.__shaders),
            uniforms(o.uniforms)
        {

        }

        program::program(x::graphics::program && o) noexcept
        :   __name(x::move(o.__name)),
            __id(o.__id),
            __shaders(x::move(o.__shaders)),
            uniforms(x::move(o.uniforms))
        {
            o.__id = 0;
        }

        program::~program()
        {

        }

        x::graphics::program & program::operator=(const x::graphics::program & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __id = o.__id;
                __shaders = o.__shaders;
                uniforms = o.uniforms;
            }
            return *this;
        }

        x::graphics::program & program::operator=(x::graphics::program && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __id = o.__id;
                __shaders = x::move(o.__shaders);
                uniforms = x::move(o.uniforms);

                o.__id = 0;
            }
            return *this;
        }
    }
}
