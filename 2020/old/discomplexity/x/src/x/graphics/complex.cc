#include "complex.hh"

namespace x
{
    namespace graphics
    {
        complex::complex()
        :   x::graphics::object(),
            __children()
        {
        }

        complex::complex(const complex & o)
        :   x::graphics::object(o),
            __children(o.__children)
        {
            exceptional();  // NEED TO DEEP COPY
        }

        complex::complex(complex && o) noexcept
        :   x::graphics::object(x::move(o)),
            __children(x::move(o.__children))
        {
        }

        complex::~complex()
        {
        }

        complex & complex::operator=(const complex & o)
        {
            if(&o != this)
            {
                exceptional();  // NEED TO DEEP COPY
                x::graphics::object::operator=(o);
                __children = o.__children;
            }
            return *this;
        }

        complex & complex::operator=(complex && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::object::operator=(x::move(o));
                __children = x::move(o.__children);
            }
            return *this;
        }

        void complex::load()
        {
            __children.each([](x::graphics::object * o){
                o->load();
            });
        }

        void complex::unload()
        {
            __children.each([](x::graphics::object * o){
                o->unload();
            });
        }

        void complex::render(const x::graphics::matrix & model, x::uint32 level)
        {
            __children.each([&model, &level](x::graphics::object * o){
                o->render(model, level);
            });
        }

        void complex::status(x::uint32 v)
        {
            __children.each([&v](x::graphics::object * o){
                o->status(v);
            });
        }
        //
        // void complex::level(x::uint32 v)
        // {
        //
        // }
    }
}
