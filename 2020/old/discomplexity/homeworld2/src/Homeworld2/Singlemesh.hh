#ifndef   __HOMEWORLD2__SINGLEMESH__H__
#define   __HOMEWORLD2__SINGLEMESH__H__

#include <x/graphics/complex.hh>
#include <x/graphics/primitive.hh>

namespace Homeworld2
{
    class Singlemesh : public x::graphics::complex
    {
    public:     void render(const x::graphics::matrix & model, x::uint32 level) override;
    public:     Singlemesh & operator=(const Singlemesh & o);
    public:     Singlemesh & operator=(Singlemesh && o) noexcept;
    public:     Singlemesh();
    public:     Singlemesh(const Singlemesh & o);
    public:     Singlemesh(Singlemesh && o) noexcept;
    public:     ~Singlemesh();
    };
}

#endif // __HOMEWORLD2__SINGLEMESH__H__'
