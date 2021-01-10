#ifndef   __X_GRAPHICS__PROJECTION__HH__
#define   __X_GRAPHICS__PROJECTION__HH__

#include <x/reality/matrix.hh>

namespace x
{
    namespace reality
    {
        class projection
        {
        protected:  static x::reality::projection __main;
        protected:  static x::reality::projection * __current;
        public:     static x::reality::projection & current() { return __current != nullptr ? *__current : __main; }
        public:     static x::reality::projection & main() { return __main; }
        protected:  x::real __fovy;
        protected:  x::real __aspect;
        protected:  x::real __near;
        protected:  x::real __far;
        protected:  x::reality::matrix __matrix;
        public:     inline const x::reality::matrix & matrix() const { return __matrix; }
        public:     x::reality::projection & operator=(const x::reality::projection & o);
        public:     x::reality::projection & operator=(x::reality::projection && o) noexcept;
        public:     projection(x::real aspect);
        public:     projection();
        public:     projection(const x::reality::projection & o);
        public:     projection(x::reality::projection && o) noexcept;
        public:     virtual ~projection();
        };
    }
}

#endif // __X_GRAPHICS__PROJECTION__HH__
