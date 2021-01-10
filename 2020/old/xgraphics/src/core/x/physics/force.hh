#ifndef   __X_PHYSICS__FORCE__HH__
#define   __X_PHYSICS__FORCE__HH__

#include <x/math.hh>
#include <x/reality/variable.hh>
#include <x/console.hh>

namespace x
{
    namespace physics
    {
        class force : public x::reality::variable<x::real>
        {
        public:     static x::real acceleration(x::real f, x::real m);
        public:     static x::real acceleration(x::real f, x::real m, x::real velocity);
        protected:  static x::real calculate(x::real value, x::real initial, x::real basis, x::real interval, x::real k);



        protected:  x::real __k;
        public:     const x::real & value() const override { return this->__value; }
        public:     void value(const x::real & v) override;
        public:     void value(x::real && v) override;
        public:     void update() override;
        public:     x::physics::force & operator=(const x::physics::force & o);
        public:     x::physics::force & operator=(x::physics::force && o) noexcept;
        public:     force();
        public:     force(const x::physics::force & o);
        public:     force(x::physics::force && o) noexcept;
        public:     ~force() override;
        };
    }
}

#endif // __X_PHYSICS__FORCE__HH__
