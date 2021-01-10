#ifndef   __HOMEWORLD2_GRAPHICS__ENGINESHAPE__HH__
#define   __HOMEWORLD2_GRAPHICS__ENGINESHAPE__HH__

#include <x/graphics/primitive.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Engineshape : public x::graphics::primitive
        {
        protected:  x::string __parent;
        public:     virtual void name(const x::string & v){ __name = v; }
        public:     virtual void name(x::string && v){ __name = x::move(v); }
        public:     const x::string & name() const override;
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
}

#endif // __HOMEWORLD2_GRAPHICS__ENGINESHAPE__HH__
