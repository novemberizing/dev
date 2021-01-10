#ifndef   __X_GRAPHICS__VERTEX__HH__
#define   __X_GRAPHICS__VERTEX__HH__

#include <x/graphics/type.hh>
#include <x/graphics/vector.hh>
#include <x/graphics/coordinate.hh>
#include <x/graphics/color.hh>

namespace x
{
    namespace graphics
    {
        class vertex
        {
        public:     static const x::uint32 stride = 88;
        protected:  x::graphics::vector __position;
        protected:  x::graphics::vector __normal;
        protected:  x::graphics::color __color;
        protected:  x::graphics::coordinate __texture;
        protected:  x::graphics::vector __tangent;
        protected:  x::graphics::vector __binormal;
        public:     inline const x::graphics::vector & position() const { return __position; }
        public:     inline const x::graphics::vector & normal() const { return __normal; }
        public:     inline const x::graphics::color & color() const { return __color; }
        public:     inline const x::graphics::coordinate & texture() const { return __texture; }
        public:     inline const x::graphics::vector & tangent() const { return __tangent; }
        public:     inline const x::graphics::vector & binormal() const { return __binormal; }
        public:     inline void position(x::float32 x, x::float32 y, x::float32 z, x::float32 w){ __position.set(x, y, z, w); }
        public:     inline void position(x::float32 x, x::float32 y, x::float32 z){ __position.set(x, y, z, 1.0f); }
        public:     inline void normal(x::float32 x, x::float32 y, x::float32 z, x::float32 w){ __normal.set(x, y, z, w); }
        public:     inline void normal(x::float32 x, x::float32 y, x::float32 z){ __normal.set(x, y, z, 0.0f); }
        public:     inline void color(x::float32 r, x::float32 g, x::float32 b){ __color.set(r, g, b); }
        public:     inline void color(x::float32 r, x::float32 g, x::float32 b, x::float32 a){ __color.set(r, g, b, a); }
        public:     inline void texture(x::float32 x, x::float32 y) { __texture.set(x, y); }
        public:     inline void tangent(x::float32 x, x::float32 y, x::float32 z){ __tangent.set(x, y, z, 0.0f); }
        public:     inline void binormal(x::float32 x, x::float32 y, x::float32 z){ __binormal.set(x, y, z, 0.0f); }
        public:     inline void position(const x::graphics::vector & o){ __position = o; }
        public:     inline void normal(const x::graphics::vector & o){ __normal = o; }
        public:     inline void color(const x::graphics::color & o){ __color = o; }
        public:     inline void texture(const x::graphics::coordinate & o){ __texture = o; }
        public:     inline void tangent(const x::graphics::vector & o){ __tangent = o; }
        public:     inline void binormal(const x::graphics::vector & o){ __binormal = o; }
        public:     inline void position(x::graphics::vector && o){ __position = x::move(o); }
        public:     inline void normal(x::graphics::vector && o){ __normal = x::move(o); }
        public:     inline void color(x::graphics::color && o){ __color = x::move(o); }
        public:     inline void texture(x::graphics::coordinate && o){ __texture = x::move(o); }
        public:     inline void tangent(x::graphics::vector && o){ __tangent = x::move(o); }
        public:     inline void binormal(x::graphics::vector && o){ __binormal = x::move(o); }
        public:     vertex & operator=(const vertex & o);
        public:     vertex & operator=(vertex && o) noexcept;
        public:     vertex(const x::initializer<x::float32> & position, const x::initializer<x::float32> & normal);
        public:     vertex();
        public:     vertex(const vertex & o);
        public:     vertex(vertex && o) noexcept;
        public:     virtual ~vertex();
        };
    }
}

#endif // __X_GRAPHICS__VERTEX__HH__
