#ifndef   __HOMEWORLD2_GRAPHICS_OBJECTS__BASE__HH__
#define   __HOMEWORLD2_GRAPHICS_OBJECTS__BASE__HH__

#include <x/graphics/objects/base.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            class Base : public x::graphics::objects::base
            {
            public:     Base(x::graphics::reference * reference, x::graphics::program * program, x::graphics::texture * texture);
            public:     ~Base() override;
            public:     Homeworld2::Graphics::Objects::Base & operator=(const Homeworld2::Graphics::Objects::Base & o) = delete;
            public:     Homeworld2::Graphics::Objects::Base & operator=(Homeworld2::Graphics::Objects::Base && o) noexcept = delete;
            public:     Base() = delete;
            public:     Base(const Homeworld2::Graphics::Objects::Base & o) = delete;
            public:     Base(Homeworld2::Graphics::Objects::Base && o) noexcept = delete;
            };
        }
    }
}

#endif // __HOMEWORLD2_GRAPHICS_OBJECTS__BASE__HH__
