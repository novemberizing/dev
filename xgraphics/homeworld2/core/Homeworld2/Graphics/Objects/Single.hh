#ifndef   __HOMEWORLD2_GRAPHICS_OBJECTS__SINGLE__HH__
#define   __HOMEWORLD2_GRAPHICS_OBJECTS__SINGLE__HH__

#include <x/graphics/objects/single.hh>

#include <Homeworld2/Graphics/Objects/Lod.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            class Single : public x::graphics::objects::single
            {
            protected:  x::string __name;
            public:     const x::string & name() const override { return __name; }
            public:     Single(const x::string & name, Homeworld2::Graphics::Objects::Lod * object);
            public:     ~Single() override;
            public:     Homeworld2::Graphics::Objects::Single & operator=(const Homeworld2::Graphics::Objects::Single & o) = delete;
            public:     Homeworld2::Graphics::Objects::Single & operator=(Homeworld2::Graphics::Objects::Single && o) noexcept = delete;
            public:     Single() = delete;
            public:     Single(const Homeworld2::Graphics::Objects::Single & o) = delete;
            public:     Single(Homeworld2::Graphics::Objects::Single && o) noexcept = delete;
            };
        }
    }
}

#endif // __HOMEWORLD2_GRAPHICS_OBJECTS__SINGLE__HH__
