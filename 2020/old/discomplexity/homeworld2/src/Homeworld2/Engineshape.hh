#ifndef   __HOMEWORLD2__ENGINESHAPE__H__
#define   __HOMEWORLD2__ENGINESHAPE__H__

#include <x/graphics/primitive.hh>

namespace Homeworld2
{
    class Engineshape : public x::graphics::primitive
    {
    protected:  x::string __parent;
    public:     inline void parent(const x::string & v) { __parent = v; }
    public:     inline void parent(x::string && v) { __parent = x::move(v); }
    public:     Engineshape & operator=(const Engineshape & o);
    public:     Engineshape & operator=(Engineshape && o) noexcept;
    public:     Engineshape();
    public:     Engineshape(const Engineshape & o);
    public:     Engineshape(Engineshape && o) noexcept;
    public:     ~Engineshape() override;
    };
}

#endif // __HOMEWORLD2__ENGINESHAPE__H__
