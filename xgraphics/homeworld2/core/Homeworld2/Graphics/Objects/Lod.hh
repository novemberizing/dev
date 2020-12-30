#ifndef   __HOMEWORLD2_GRAPHICS_OBJECTS__LOD__HH__
#define   __HOMEWORLD2_GRAPHICS_OBJECTS__LOD__HH__

#include <x/graphics/objects/multi.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            class Lod : public x::graphics::objects::multi
            {
            protected:  x::uint32 __level;
            public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
            public:     Lod(x::uint32 level);
            public:     ~Lod() override;
            public:     Homeworld2::Graphics::Objects::Lod & operator=(const Homeworld2::Graphics::Objects::Lod & o) = delete;
            public:     Homeworld2::Graphics::Objects::Lod & operator=(Homeworld2::Graphics::Objects::Lod && o) noexcept = delete;
            public:     Lod() = delete;
            public:     Lod(const Homeworld2::Graphics::Objects::Lod & o) = delete;
            public:     Lod(Homeworld2::Graphics::Objects::Lod && o) noexcept = delete;
            };
        }
    }
}

#endif // __HOMEWORLD2_GRAPHICS_OBJECTS__LOD__HH__
