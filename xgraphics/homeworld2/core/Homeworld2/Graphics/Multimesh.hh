#ifndef   __HOMEWORLD2__MULTIMESH__HH__
#define   __HOMEWORLD2__MULTIMESH__HH__

#include <x/string.hh>
#include <x/map.hh>

#include <Homeworld2/Graphics/Singlemesh.hh>
#include <Homeworld2/Graphics/Objects/Multi.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Multimesh : public x::graphics::reference
        {
        protected:  x::string __name;
        protected:  x::string __parent;
        public:     x::array<Singlemesh> singlemeshs;
        public:     virtual Homeworld2::Graphics::Objects::Multi * build(x::array<x::graphics::texture> & textures, x::array<Material> & materials);
        public:     virtual void name(const x::string & v){ __name = v; }
        public:     virtual void name(x::string && v){ __name = x::move(v); }
        public:     const x::string & name() const override;
        public:     void load() override;
        public:     void unload() override;
        public:     void render() override;
        public:     inline const x::string & parent() const { return __parent; }
        public:     inline void parent(const x::string & v) { __parent = v; }
        public:     inline void parent(x::string && v) { __parent = x::move(v); }
        public:     Multimesh & operator=(const Multimesh & o);
        public:     Multimesh & operator=(Multimesh && o) noexcept;
        public:     Multimesh();
        public:     Multimesh(const Multimesh & o);
        public:     Multimesh(Multimesh && o) noexcept;
        public:     ~Multimesh() override;
        };
    }
}

#endif // __HOMEWORLD2__MULTIMESH__HH__
