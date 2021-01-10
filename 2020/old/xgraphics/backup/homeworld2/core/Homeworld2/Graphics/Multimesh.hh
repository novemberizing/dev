#ifndef   __HOMEWORLD2__MULTIMESH__HH__
#define   __HOMEWORLD2__MULTIMESH__HH__

#include <x/string.hh>
#include <x/map.hh>

#include <Homeworld2/Graphics/Singlemesh.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Multimesh : public x::graphics::reference
        {
        protected:  x::string __parent;
        public:     x::array<Singlemesh> singlemeshs;
        public:     void load() override;
        public:     void unload() override;
        public:     void render(const x::reality::matrix & model) override;
        // public:     inline x::array<Singlemesh> & singlemeshs(){ return __singlemeshs; }
        public:     inline const x::string & parent() const { return __parent; }
        public:     inline void parent(const x::string & v) { __parent = v; }
        public:     inline void parent(x::string && v) { __parent = x::move(v); }
        // public:     inline void add(Singlemesh && o) { __singlemeshs.push(x::move(o)); }
        // public:     inline void add(const Singlemesh & o) { __singlemeshs.push(o); }
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
