#ifndef   __X_GRAPHICS__VERTEX__HH__
#define   __X_GRAPHICS__VERTEX__HH__

#include <x/reality/vector.hh>
#include <x/reality/coordinate.hh>
#include <x/reality/color.hh>

namespace x
{
    namespace graphics
    {
        class vertex
        {
        public:     static const x::uint32 stride = 88;
        protected:  x::reality::vector __location;
        protected:  x::reality::vector __normal;
        protected:  x::reality::color __color;
        protected:  x::reality::coordinate __texture;
        protected:  x::reality::vector __tangent;
        protected:  x::reality::vector __binormal;
        public:     inline const x::reality::vector & location() const { return __location; }
        public:     inline const x::reality::vector & normal() const { return __normal; }
        public:     inline const x::reality::color & color() const { return __color; }
        public:     inline const x::reality::coordinate & texture() const { return __texture; }
        public:     inline const x::reality::vector & tangent() const { return __tangent; }
        public:     inline const x::reality::vector & binormal() const { return __binormal; }
        public:     inline void location(x::real x, x::real y, x::real z, x::real w){ __location.set(x, y, z, w); }
        public:     inline void location(x::real x, x::real y, x::real z){ __location.set(x, y, z, 1.0f); }
        public:     inline void normal(x::real x, x::real y, x::real z, x::real w){ __normal.set(x, y, z, w); }
        public:     inline void normal(x::real x, x::real y, x::real z){ __normal.set(x, y, z, 0.0f); }
        public:     inline void color(x::real r, x::real g, x::real b){ __color.set(r, g, b); }
        public:     inline void color(x::real r, x::real g, x::real b, x::real a){ __color.set(r, g, b, a); }
        public:     inline void texture(x::real x, x::real y) { __texture.set(x, y); }
        public:     inline void tangent(x::real x, x::real y, x::real z){ __tangent.set(x, y, z, 0.0f); }
        public:     inline void binormal(x::real x, x::real y, x::real z){ __binormal.set(x, y, z, 0.0f); }
        public:     inline void location(const x::reality::vector & o){ __location = o; }
        public:     inline void normal(const x::reality::vector & o){ __normal = o; }
        public:     inline void color(const x::reality::color & o){ __color = o; }
        public:     inline void texture(const x::reality::coordinate & o){ __texture = o; }
        public:     inline void tangent(const x::reality::vector & o){ __tangent = o; }
        public:     inline void binormal(const x::reality::vector & o){ __binormal = o; }
        public:     inline void location(x::reality::vector && o){ __location = x::move(o); }
        public:     inline void normal(x::reality::vector && o){ __normal = x::move(o); }
        public:     inline void color(x::reality::color && o){ __color = x::move(o); }
        public:     inline void texture(x::reality::coordinate && o){ __texture = x::move(o); }
        public:     inline void tangent(x::reality::vector && o){ __tangent = x::move(o); }
        public:     inline void binormal(x::reality::vector && o){ __binormal = x::move(o); }
        public:     vertex & operator=(const vertex & o);
        public:     vertex & operator=(vertex && o) noexcept;
        public:     vertex(const x::initializer<x::real> & location, const x::initializer<x::real> & normal);
        public:     vertex(const x::initializer<x::real> & location, const x::initializer<x::real> & normal, const x::initializer<x::real> & color, const x::initializer<x::real> & texture);
        public:     vertex();
        public:     vertex(const vertex & o);
        public:     vertex(vertex && o) noexcept;
        public:     virtual ~vertex();
        };
    }
}

#endif // __X_GRAPHICS__VERTEX__HH__
