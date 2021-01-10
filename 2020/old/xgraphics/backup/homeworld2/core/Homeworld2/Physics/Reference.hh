#ifndef   __HOMEWORLD2_PHYSICS__REFERENCE__HH__
#define   __HOMEWORLD2_PHYSICS__REFERENCE__HH__

#include <x/physics/reference.hh>

namespace Homeworld2
{
    namespace Physics
    {
        class Reference : public x::physics::reference
        {
        protected:  x::real __length;
        protected:  x::real __width;
        protected:  x::real __height;
        protected:  x::real __mass;
        protected:  x::real __energy;
        public:     const x::real weight() const override;
        public:     void weight(x::real v) override;
        public:     const x::real energy() const override;
        public:     void energy(x::real v) override;
        public:     Homeworld2::Physics::Reference & operator=(const Homeworld2::Physics::Reference & o);
        public:     Homeworld2::Physics::Reference & operator=(Homeworld2::Physics::Reference && o) noexcept;
        public:     Reference(const x::string & name);
        public:     Reference(x::string && name);
        public:     Reference(x::real weight, x::real energy);
        public:     Reference(const x::string & name, x::real weight, x::real energy);
        public:     Reference(x::string && name, x::real weight, x::real energy);
        public:     Reference();
        public:     Reference(const Homeworld2::Physics::Reference & o);
        public:     Reference(Homeworld2::Physics::Reference && o) noexcept;
        public:     ~Reference() override;
        };
    }
}

#endif // __HOMEWORLD2_PHYSICS__REFERENCE__HH__
