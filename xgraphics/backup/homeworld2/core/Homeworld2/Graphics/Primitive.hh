#ifndef   __HOMEWORLD2_GRAPHICS__PRIMITIVE__HH__
#define   __HOMEWORLD2_GRAPHICS__PRIMITIVE__HH__

#include <x/graphics/primitive.hh>
#include <x/graphics/application.hh>

#include <Homeworld2/Graphics/Material.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Primitive : public x::graphics::primitive
        {
        protected:  x::uint32 __index;
        protected:  Material * __material;
        protected:  x::array<x::graphics::texture> * __textures;
        public:     inline void set(x::array<x::graphics::texture> * o){ __textures = o; }
        public:     inline void set(x::array<Material> & materials)
                    {
                        x::graphics::application & application = x::graphics::application::get();

                        __material = &materials[__index];
                        __program = &application.programs[__material->shader()];

                        assertion(__program == nullptr);
                    }
        public:     inline void material(x::uint32 v){ __index = v; }
        public:     x::boolean bind(const x::string & name, x::uint32 id, const x::reality::matrix & matrix) override;
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
