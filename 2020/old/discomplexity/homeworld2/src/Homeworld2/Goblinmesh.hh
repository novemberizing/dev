#ifndef   __HOMEWORLD2__GOBLINMESH__H__
#define   __HOMEWORLD2__GOBLINMESH__H__

#include <Homeworld2/Singlemesh.hh>

namespace Homeworld2
{
    class Goblinmesh : public x::graphics::object
    {
    protected:  Singlemesh __singlemesh;
    protected:  x::string __parent;
    public:     void status(x::uint32 v) override;
    public:     void load() override;
    public:     void unload() override;
    public:     void render(const x::graphics::matrix & model, x::uint32 level) override;
    public:     inline const x::string & parent() const { return __parent; }
    public:     inline void parent(const x::string & v) { __parent = v; }
    public:     inline void parent(x::string && v) { __parent = x::move(v); }
    public:     inline void set(Singlemesh && singlemesh) { __singlemesh = x::move(singlemesh); }
    public:     inline void set(const Singlemesh & singlemesh) { __singlemesh = singlemesh; }
    public:     Goblinmesh & operator=(const Goblinmesh & o);
    public:     Goblinmesh & operator=(Goblinmesh && o) noexcept;
    public:     Goblinmesh();
    public:     Goblinmesh(const Goblinmesh & o);
    public:     Goblinmesh(Goblinmesh && o) noexcept;
    public:     ~Goblinmesh() override;
    };
}

#endif // __HOMEWORLD2__GOBLINMESH__H__
