#ifndef   __HOMEWORLD2__MULTIMESH__H__
#define   __HOMEWORLD2__MULTIMESH__H__

#include <x/string.hh>
#include <x/map.hh>

#include <Homeworld2/Singlemesh.hh>

namespace Homeworld2
{
    class Multimesh : public x::graphics::object
    {
    protected:  x::string __parent;
    protected:  x::array<Singlemesh> __singlemeshs;
    public:     void status(x::uint32 v) override;
    public:     void load() override;
    public:     void unload() override;
    public:     void render(const x::graphics::matrix & model, x::uint32 level) override;
    public:     inline const x::string & parent() const { return __parent; }
    public:     inline void parent(const x::string & v) { __parent = v; }
    public:     inline void parent(x::string && v) { __parent = x::move(v); }
    public:     inline void add(Singlemesh && o) { __singlemeshs.push(x::move(o)); }
    public:     inline void add(const Singlemesh & o) { __singlemeshs.push(o); }
    public:     Multimesh & operator=(const Multimesh & o);
    public:     Multimesh & operator=(Multimesh && o) noexcept;
    public:     Multimesh();
    public:     Multimesh(const Multimesh & o);
    public:     Multimesh(Multimesh && o) noexcept;
    public:     ~Multimesh() override;
    //
    // public:     void load() override
    //             {
    //                 __singlemeshs.each([](Singlemesh & singlemesh){
    //                     singlemesh.load();
    //                 });
    //             }
    // public:     void unload() override
    //             {
    //                 __singlemeshs.each([](Singlemesh & singlemesh){
    //                     singlemesh.unload();
    //                 });
    //             }
    // public:     virtual void render(x::uint32 level)
    //             {
    //                 __singlemeshs.each([&level](Singlemesh & singlemesh){
    //                     // console::out << singlemesh.name() << ":" << singlemesh.level() << endl;
    //                     singlemesh.render(level);
    //                 });
    //             }
    // public:     void render() override
    //             {
    //                 __singlemeshs.each([](Singlemesh & singlemesh){
    //                     singlemesh.render();
    //                 });
    //             }
    // public:     inline x::uint64 size() const
    //             {
    //                 return __singlemeshs.size();
    //             }
    // public:     virtual const x::string & parent() const
    //             {
    //                 return __parent;
    //             }
    // public:     virtual void parent(const x::string & v)
    //             {
    //                 __parent = v;
    //             }
    // public:     virtual void parent(x::string && v)
    //             {
    //                 __parent = x::move(v);
    //             }

    // public:     Multimesh & operator=(const Multimesh & o);
    // public:     Multimesh & operator=(Multimesh && o) noexcept;
    // public:     Multimesh();
    // public:     Multimesh(const Multimesh & o);
    // public:     Multimesh(Multimesh && o) noexcept;
    // public:     virtual ~Multimesh();
    };
}

#endif // __HOMEWORLD2__MULTIMESH__H__
