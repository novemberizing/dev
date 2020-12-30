#ifndef   __HOMEWORLD2_GRAPHICS__SINGLEMESH__H__
#define   __HOMEWORLD2_GRAPHICS__SINGLEMESH__H__

#include <x/graphics/reference.hh>

#include <Homeworld2/Graphics/Primitive.hh>
#include <Homeworld2/Graphics/Objects/Lod.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Singlemesh : public x::graphics::reference
        {
        protected:  x::string __name;
        protected:  x::uint32 __index;
        protected:  x::uint32 __level;
        public:     x::array<Homeworld2::Graphics::Primitive> children;
        public:     inline void push(const Homeworld2::Graphics::Primitive & o){ children.push(o); }
        public:     inline void push(Homeworld2::Graphics::Primitive && o){ children.push(x::move(o));}
        public:     inline void level(x::uint32 v){ __level = v; }
        public:     inline x::uint32 level() const { return __level; }
        public:     virtual Homeworld2::Graphics::Objects::Lod * build(x::array<x::graphics::texture> & textures, x::array<Material> & materials);
        public:     virtual void name(const x::string & v){ __name = v; }
        public:     virtual void name(x::string && v){ __name = x::move(v); }
        public:     const x::string & name() const override;
        public:     void load() override;
        public:     void unload() override;
        public:     void render() override;
        public:     Homeworld2::Graphics::Singlemesh & operator=(const Homeworld2::Graphics::Singlemesh & o);
        public:     Homeworld2::Graphics::Singlemesh & operator=(Homeworld2::Graphics::Singlemesh && o) noexcept;
        public:     Singlemesh();
        public:     Singlemesh(const Homeworld2::Graphics::Singlemesh & o);
        public:     Singlemesh(Homeworld2::Graphics::Singlemesh && o) noexcept;
        public:     ~Singlemesh() override;
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__SINGLEMESH__H__'
