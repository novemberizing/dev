#ifndef   __HOMEWORLD2_GRAPHICS__PRIMITIVE__HH__
#define   __HOMEWORLD2_GRAPHICS__PRIMITIVE__HH__

#include <x/graphics/primitive.hh>

#include <Homeworld2/Graphics/Material.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Primitive : public x::graphics::primitive
        {
        protected:  x::uint32 __index;
        protected:  Homeworld2::Graphics::Material * __material;
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
