#ifndef   __X_GRAPHICS__LIGHT__HH__
#define   __X_GRAPHICS__LIGHT__HH__

#include <x/graphics/vector.hh>
#include <x/graphics/color.hh>

namespace x
{
    namespace graphics
    {
        class light
        {
        protected:  x::graphics::vector __position;
        protected:  x::graphics::color __color;
        protected:  x::float32 __ambient;
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     inline x::float32 ambient() const { return __ambient; }
        public:     inline x::graphics::color & color() { return __color; }
        public:     inline const x::graphics::color & color() const { return __color; }
        public:     inline x::graphics::vector & position() { return __position; }
        public:     inline const x::graphics::vector & position() const { return __position; }
        public:     light & operator=(const light & o);
        public:     light & operator=(light && o) noexcept;
        public:     light(const x::initializer<x::float32> & position, const x::initializer<x::float32> & color, x::float32 ambient);
        public:     light();
        public:     light(const light & o);
        public:     light(light && o) noexcept;
        public:     virtual ~light();
        };
    }
}

#endif // __X_GRAPHICS__LIGHT__HH__
