#ifndef   __X_SPACE_OBJECTS__UNIT__HH__
#define   __X_SPACE_OBJECTS__UNIT__HH__

#include <xSpace/Object.hh>

namespace xSpace
{
    namespace Objects
    {
        class Unit : public xSpace::Object
        {
        public:     Unit(const x::string & name, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, x::graphics::object * graphics);
        public:     ~Unit() override;
        public:     Unit() = delete;
        public:     Unit(const xSpace::Objects::Unit & o) = delete;
        public:     Unit(xSpace::Objects::Unit && o) noexcept = delete;
        public:     xSpace::Objects::Unit & operator=(const xSpace::Objects::Unit & o) = delete;
        public:     xSpace::Objects::Unit & operator=(xSpace::Objects::Unit && o) noexcept = delete;
        };
    }
}

#endif // __X_SPACE_OBJECTS__UNIT__HH__
