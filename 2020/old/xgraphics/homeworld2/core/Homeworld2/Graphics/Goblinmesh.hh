#ifndef   __HOMEWORLD2__GOBLINMESH__HH__
#define   __HOMEWORLD2__GOBLINMESH__HH__

#include <Homeworld2/Graphics/Singlemesh.hh>
#include <Homeworld2/Graphics/Objects/Single.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Goblinmesh : public x::graphics::reference
        {
        public:     Homeworld2::Graphics::Singlemesh singlemesh;
        protected:  x::string __parent;
        protected:  x::string __name;
        public:     virtual Homeworld2::Graphics::Objects::Single * build(x::array<x::graphics::texture> & textures, x::array<Material> & materials);
        public:     virtual void name(const x::string & v) { __name = v; }
        public:     virtual void name(x::string && v) { __name = x::move(v); }
        public:     const x::string & name() const override;
        public:     void load() override;
        public:     void unload() override;
        public:     void render() override;
        public:     inline const x::string & parent() const { return __parent; }
        public:     inline void parent(const x::string & v) { __parent = v; }
        public:     inline void parent(x::string && v) { __parent = x::move(v); }
        public:     Homeworld2::Graphics::Goblinmesh & operator=(const Homeworld2::Graphics::Goblinmesh & o);
        public:     Homeworld2::Graphics::Goblinmesh & operator=(Homeworld2::Graphics::Goblinmesh && o) noexcept;
        public:     Goblinmesh();
        public:     Goblinmesh(const Homeworld2::Graphics::Goblinmesh & o);
        public:     Goblinmesh(Homeworld2::Graphics::Goblinmesh && o) noexcept;
        public:     ~Goblinmesh() override;
        };
    }
}

#endif // __HOMEWORLD2__GOBLINMESH__HH__
