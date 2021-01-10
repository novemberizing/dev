#ifndef   __X_PHYSICS__REFERENCE__HH__
#define   __X_PHYSICS__REFERENCE__HH__

#include <x/reality/reference.hh>

namespace x
{
    namespace physics
    {
        class reference : public x::reality::reference
        {
        public:     virtual const x::real mass() const { return 0.0f; }
        public:     virtual const x::real energy() const { return 0.0f; }
        public:     virtual const x::real velocity() const { return 0.0f; }
        public:     x::physics::reference & operator=(const x::physics::reference & o) = delete;
        public:     x::physics::reference & operator=(x::physics::reference && o) noexcept = delete;
        public:     reference();
        public:     reference(const x::physics::reference & o) = delete;
        public:     reference(x::physics::reference && o) noexcept = delete;
        public:     ~reference() override;
        };
    }
}

#endif // __X_PHYSICS__REFERENCE__HH__
