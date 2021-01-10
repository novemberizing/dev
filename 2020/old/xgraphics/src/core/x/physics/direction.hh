#ifndef   __X_PHYSICS__DIRECTION__HH__
#define   __X_PHYSICS__DIRECTION__HH__

#include <x/reality/variable.hh>
#include <x/reality/vector.hh>

namespace x
{
    namespace physics
    {
        class direction : public x::reality::variable<x::reality::vector>
        {
        protected:  static x::real calculate(x::real value, x::real initial, x::real basis, x::real interval, x::real k);
        protected:  x::real __k;
        public:     inline x::real x() const { return __current.x(); }
        public:     inline x::real y() const { return __current.y(); }
        public:     inline x::real z() const { return __current.z(); }
        public:     void update() override;
        public:     x::physics::direction & operator=(const x::physics::direction & o);
        public:     x::physics::direction & operator=(x::physics::direction && o) noexcept;
        public:     direction(const x::reality::vector & direction);
        public:     direction();
        public:     direction(const x::physics::direction & o);
        public:     direction(x::physics::direction && o) noexcept;
        public:     ~direction() override;
        };
    }
}

#endif // __X_PHYSICS__DIRECTION__HH__
