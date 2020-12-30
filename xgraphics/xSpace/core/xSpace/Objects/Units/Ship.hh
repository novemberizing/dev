#ifndef   __X_SPACE_OBJECTS_UNITS__SHIP__HH__
#define   __X_SPACE_OBJECTS_UNITS__SHIP__HH__

#include <xSpace/Objects/Unit.hh>

namespace xSpace
{
    namespace Objects
    {
        namespace Units
        {
            class Ship : public xSpace::Objects::Unit
            {
            public:     Ship(const x::string & name, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, x::graphics::object * graphics);
            public:     ~Ship() override;
            public:     Ship() = delete;
            public:     Ship(const xSpace::Objects::Units::Ship & o) = delete;
            public:     Ship(xSpace::Objects::Units::Ship && o) noexcept = delete;
            public:     xSpace::Objects::Units::Ship & operator=(const xSpace::Objects::Units::Ship & o) = delete;
            public:     xSpace::Objects::Units::Ship & operator=(xSpace::Objects::Units::Ship && o) noexcept = delete;
            };
        }
    }
}

#endif // __X_SPACE_OBJECTS_UNITS__SHIP__HH__
