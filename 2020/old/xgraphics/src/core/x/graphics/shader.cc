#include "shader.hh"

namespace x
{
    namespace graphics
    {
        shader::shader(const x::string & name, x::uint32 category, const x::string & code)
        :   __name(name),
            __category(category),
            __type(x::graphics::shader::none),
            __id(0),
            __code(code)
        {
        }

        shader::shader(x::string && name, x::uint32 category, x::string && code)
        :   __name(x::move(name)),
            __category(category),
            __type(x::graphics::shader::none),
            __id(0),
            __code(x::move(code))
        {
        }

        shader::shader()
        :   __name(),
            __category(x::graphics::shader::none),
            __type(x::graphics::shader::none),
            __id(0),
            __code()
        {
        }

        shader::shader(const x::graphics::shader & o)
        :   __name(o.__name),
            __category(o.__category),
            __type(o.__type),
            __id(o.__id),
            __code(o.__code)
        {
        }

        shader::shader(x::graphics::shader && o) noexcept
        :   __name(x::move(o.__name)),
            __category(o.__category),
            __type(o.__type),
            __id(o.__id),
            __code(x::move(o.__code))
        {
            o.__category = x::graphics::shader::none;
            o.__type = x::graphics::shader::none;
            o.__id = 0;
        }

        shader::~shader()
        {
        }

        x::graphics::shader & shader::operator=(const x::graphics::shader & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __category = o.__category;
                __type = o.__type;
                __id = o.__id;
                __code = o.__code;
            }
            return *this;
        }

        x::graphics::shader & shader::operator=(x::graphics::shader && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __category = o.__category;
                __type = o.__type;
                __id = o.__id;
                __code = x::move(o.__code);

                o.__category = x::graphics::shader::none;
                o.__type = x::graphics::shader::none;
                o.__id = 0;
            }
            return *this;
        }
    }
}
