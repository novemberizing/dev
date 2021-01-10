#ifndef   __X_GRAPHICS__CAMERA__HH__
#define   __X_GRAPHICS__CAMERA__HH__

#include <x/graphics/vector.hh>
#include <x/graphics/matrix.hh>
#include <x/output/stream.hh>

namespace x
{
    namespace graphics
    {
        class camera
        {
        protected:  x::graphics::vector __center;
        protected:  x::graphics::vector __up;
        protected:  x::graphics::vector __position;
        protected:  x::graphics::matrix __matrix;
        public:     virtual void refresh();
        public:     inline const x::graphics::matrix & matrix() const { return __matrix; }
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     inline x::graphics::vector & position() { return __position; }
        public:     inline const x::graphics::vector & position() const { return __position; }
        public:     inline const x::graphics::vector & up() const { return __up; }
        public:     inline const x::graphics::vector & center() const { return __center; }
        public:     camera & operator=(const camera & o);
        public:     camera & operator=(camera && o) noexcept;
        public:     camera(const x::initializer<x::float32> & position);
        public:     camera();
        public:     camera(const camera & o);
        public:     camera(camera && o) noexcept;
        public:     virtual ~camera();
        };
    }
}

#endif // __X_GRAPHICS__CAMERA__HH__
