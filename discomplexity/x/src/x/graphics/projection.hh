#ifndef   __X_GRAPHICS__PROJECTION__HH__
#define   __X_GRAPHICS__PROJECTION__HH__

#include <x/graphics/matrix.hh>

namespace x
{
    namespace graphics
    {
        class projection
        {
        protected:  x::float32 __fovy;
        protected:  x::float32 __aspect;
        protected:  x::float32 __near;
        protected:  x::float32 __far;
        protected:  x::graphics::matrix __matrix;
        public:     inline const x::graphics::matrix & matrix() const { return __matrix; }
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     virtual void refresh();
        public:     projection & operator=(const projection & o);
        public:     projection & operator=(projection && o) noexcept;
        public:     projection(x::float32 aspect);
        public:     projection();
        public:     projection(const projection & o);
        public:     projection(projection && o) noexcept;
        public:     virtual ~projection();
        };
    }
}

#endif // __X_GRAPHICS__PROJECTION__HH__
