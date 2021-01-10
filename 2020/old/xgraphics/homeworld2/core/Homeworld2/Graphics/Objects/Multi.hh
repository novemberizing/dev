#ifndef   __HOMEWORLD2_GRAPHICS_OBJECTS__MULTI__HH__
#define   __HOMEWORLD2_GRAPHICS_OBJECTS__MULTI__HH__

#include <x/graphics/objects/multi.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            class Multi : public x::graphics::objects::multi
            {
            protected:  x::string __name;
            public:     const x::string & name() const override { return __name; }
            public:     Multi(const x::string & name);
            public:     ~Multi() override;
            public:     Multi() = delete;
            public:     Multi(const Homeworld2::Graphics::Objects::Multi & o) = delete;
            public:     Multi(Homeworld2::Graphics::Objects::Multi && o) noexcept = delete;
            public:     Homeworld2::Graphics::Objects::Multi & operator=(const Homeworld2::Graphics::Objects::Multi & o) = delete;
            public:     Homeworld2::Graphics::Objects::Multi & operator=(Homeworld2::Graphics::Objects::Multi && o) noexcept = delete;
            };
        }
    }
}

#endif // __HOMEWORLD2_GRAPHICS_OBJECTS__MULTI__HH__
