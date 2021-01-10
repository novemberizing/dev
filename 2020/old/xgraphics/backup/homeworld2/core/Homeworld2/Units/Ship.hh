#ifndef   __HOMEWORLD2_UNIT__SHIP__HH__
#define   __HOMEWORLD2_UNIT__SHIP__HH__

#include <Homeworld2/Unit.hh>

namespace Homeworld2
{
    namespace Units
    {
        class Ship : public Homeworld2::Unit
        {
        protected:  Graphics::Object * __graphics;
        public:     Ship & operator=(const Ship & o) = delete;
        public:     Ship & operator=(Ship && o) noexcept = delete;
        public:     Ship(const x::string & name, x::real energy, Graphics::Object * graphics);
        public:     Ship(const x::string & name, const x::reality::vector & position, x::real energy, Graphics::Object * graphics);
        public:     Ship(const x::string & name, const x::reality::vector & position, x::real energy, const x::reality::vector & direction, Graphics::Object * graphics);
        public:     Ship() = delete;
        public:     Ship(const Ship & o) = delete;
        public:     Ship(Ship && o) noexcept = delete;
        public:     ~Ship() override;
        };
    }
}

#endif // __HOMEWORLD2_UNIT__SHIP__HH__
