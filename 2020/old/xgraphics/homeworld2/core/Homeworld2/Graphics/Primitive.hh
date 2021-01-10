#ifndef   __HOMEWORLD2_GRAPHICS__PRIMITIVE__HH__
#define   __HOMEWORLD2_GRAPHICS__PRIMITIVE__HH__

#include <x/graphics/primitive.hh>
#include <x/graphics/application.hh>

#include <Homeworld2/Graphics/Objects/Base.hh>
#include <Homeworld2/Graphics/Material.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Primitive : public x::graphics::primitive
        {
        protected:  x::uint32 __index;
        protected:  Material * __material;
        public:     virtual Homeworld2::Graphics::Objects::Base * build(x::array<x::graphics::texture> & textures, x::array<Material> & materials);
        public:     inline void material(x::uint32 v){ __index = v; }
        public:     Primitive & operator=(const Primitive & o);
        public:     Primitive & operator=(Primitive && o) noexcept;
        public:     Primitive();
        public:     Primitive(const Primitive & o);
        public:     Primitive(Primitive && o) noexcept;
        public:     ~Primitive() override;
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__PRIMITIVE__HH__
