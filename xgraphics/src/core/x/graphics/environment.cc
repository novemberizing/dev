#include "environment.hh"

namespace x
{
    namespace graphics
    {
        environment::environment()
        :   __root()
        {
        }

        environment::environment(const x::graphics::environment & o)
        :   __root(o.__root)
        {
        }

        environment::environment(x::graphics::environment && o) noexcept
        :   __root(x::move(o.__root))
        {
        }

        environment::~environment()
        {
        }

        x::graphics::environment & environment::operator=(const x::graphics::environment & o)
        {
            if(&o != this)
            {
                __root = o.__root;
            }
            return *this;
        }

        x::graphics::environment & environment::operator=(x::graphics::environment && o) noexcept
        {
            if(&o != this)
            {
                __root = x::move(o.__root);
            }
            return *this;
        }
    }
}
