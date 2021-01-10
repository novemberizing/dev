#ifndef   __HOMEWORLD2__GOBLINMESH__HH__
#define   __HOMEWORLD2__GOBLINMESH__HH__

#include <Homeworld2/Graphics/Singlemesh.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Goblinmesh : public x::graphics::reference
        {
        public:     Singlemesh singlemesh;
        protected:  x::string __parent;
        public:     void load() override;
        public:     void unload() override;
        public:     void render(const x::reality::matrix & model) override;
        public:     inline const x::string & parent() const { return __parent; }
        public:     inline void parent(const x::string & v) { __parent = v; }
        public:     inline void parent(x::string && v) { __parent = x::move(v); }
        // public:     inline void set(Singlemesh && o) { singlemesh = x::move(o); }
        // public:     inline void set(const Singlemesh & o) { singlemesh = o; }
        public:     Goblinmesh & operator=(const Goblinmesh & o);
        public:     Goblinmesh & operator=(Goblinmesh && o) noexcept;
        public:     Goblinmesh();
        public:     Goblinmesh(const Goblinmesh & o);
        public:     Goblinmesh(Goblinmesh && o) noexcept;
        public:     ~Goblinmesh() override;
        };
    }
}

#endif // __HOMEWORLD2__GOBLINMESH__HH__
