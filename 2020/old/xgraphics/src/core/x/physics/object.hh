#ifndef   __X_PHYSICS__OBJECT__HH__
#define   __X_PHYSICS__OBJECT__HH__

#include <x/reality/object.hh>
#include <x/reality/vector.hh>
#include <x/physics/force.hh>
#include <x/physics/direction.hh>
#include <x/physics/reference.hh>

namespace x
{
    namespace physics
    {
        class object : public x::reality::object
        {
        public:     virtual x::physics::reference * physics(){ return nullptr; }
        public:     virtual x::real velocity() const { return 0.0f; }
        public:     virtual x::real force() const { return 0.0f; }
        public:     virtual x::real energy() const { return 0.0f; }
        public:     x::physics::object & operator=(const x::physics::object & o) = delete;
        public:     x::physics::object & operator=(x::physics::object && o) noexcept = delete;
        protected:  object();
        public:     object(const x::physics::object & o) = delete;
        public:     object(x::physics::object && o) noexcept = delete;
        public:     virtual ~object();
        };
    }
}

#endif // __X_PHYSICS__OBJECT__HH__
