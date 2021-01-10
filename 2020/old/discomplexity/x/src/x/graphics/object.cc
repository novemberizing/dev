#include "object.hh"
#include "application.hh"

#include <x/console.hh>

namespace x
{
    namespace graphics
    {
        object::object(const x::string & name)
        :   __name(name),
            __status(1),
            __level(0)
        {

        }

        object::object(x::string && name)
        :   __name(x::move(name)),
            __status(1),
            __level(0)
        {
        }

        object::object()
        :   __name(),
            __status(1),
            __level(0)
        {
        }

        object::object(const object & o)
        :   __name(o.__name),
            __status(o.__status),
            __level(o.__level)
        {
        }

        object::object(object && o) noexcept
        :   __name(x::move(o.__name)),
            __status(o.__status),
            __level(o.__level)
        {
            o.__status = 0;
            o.__level = 0;
        }

        object::~object()
        {
        }

        object & object::operator=(const object & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __status = o.__status;
                __level = o.__level;
            }
            return *this;
        }

        object & object::operator=(object && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __status = o.__status;
                __level = o.__level;

                o.__status = 0;
                o.__level = 0;
            }
            return *this;
        }

        void object::load()
        {
        }

        void object::unload()
        {
        }

        void object::render(const x::graphics::matrix & model, x::uint32 level)
        {

        }

        void object::refresh(const x::graphics::matrix & model)
        {

        }

        void object::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            x::graphics::util::unknown(strings);
        }
    }
}
