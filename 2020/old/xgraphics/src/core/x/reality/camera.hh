#ifndef   __X_GRAPHICS__CAMERA__HH__
#define   __X_GRAPHICS__CAMERA__HH__

#include <x/reality/vector.hh>
#include <x/reality/matrix.hh>
#include <x/console.hh>

namespace x
{
    namespace reality
    {
        class camera
        {
        protected:  static x::reality::camera __main;
        protected:  static x::reality::camera * __current;
        public:     static const x::reality::vector & eye();
        public:     static x::reality::camera & current();
        public:     static void current(x::reality::camera * o){ __current = o; }
        protected:  x::reality::vector __center;
        protected:  x::reality::vector __up;
        protected:  x::reality::vector __location;
        protected:  x::reality::matrix __matrix;
        public:     inline const x::reality::matrix & matrix() const { return __matrix; }
        public:     inline const x::reality::vector & center() const { return __center; }
        public:     inline const x::reality::vector & up() const { return __up; }
        public:     inline const x::reality::vector & location() const { return __location; }
        public:     virtual void start();
        public:     virtual void update();
        public:     camera & operator=(const camera & o);
        public:     camera & operator=(camera && o) noexcept;
        public:     camera(const x::reality::vector & location);
        public:     camera(const x::reality::vector & location, const x::reality::vector & center);
        public:     camera(const x::reality::vector & location, const x::reality::vector & center, const x::reality::vector & up);
        public:     camera();
        public:     camera(const camera & o);
        public:     camera(camera && o) noexcept;
        public:     virtual ~camera();
        };
    }
}

#endif // __X_GRAPHICS__CAMERA__HH__
