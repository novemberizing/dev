#ifndef   __HOMEWORLD2_SENARIOS__UNIT__HH__
#define   __HOMEWORLD2_SENARIOS__UNIT__HH__

#include <x/string.hh>
#include <x/reality/vector.hh>
#include <x/json.hh>

namespace Homeworld2
{
    namespace Senarios
    {
        class Unit
        {
        public:     static Homeworld2::Senarios::Unit from(const x::json::object * object);
        protected:  x::string __name;
        protected:  x::string __category;
        protected:  x::string __type;
        protected:  x::reality::vector __position;
        protected:  x::reality::vector __front;
        protected:  x::reality::vector __up;
        public:     Homeworld2::Senarios::Unit & operator=(const Homeworld2::Senarios::Unit & o);
        public:     Homeworld2::Senarios::Unit & operator=(Homeworld2::Senarios::Unit && o) noexcept;
        public:     Unit(const x::string & name, const x::string & category, const x::string & type, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up);
        public:     Unit();
        public:     Unit(const Homeworld2::Senarios::Unit & o);
        public:     Unit(Homeworld2::Senarios::Unit && o) noexcept;
        public:     virtual ~Unit();
        };
    }
}

#endif // __HOMEWORLD2_SENARIOS__UNIT__HH__
