#ifndef   __X_SPACE_SENARIOS__UNIT__HH__
#define   __X_SPACE_SENARIOS__UNIT__HH__

#include <x/string.hh>
#include <x/json.hh>
#include <x/reality/vector.hh>

namespace xSpace
{
    namespace Senarios
    {
        class Unit
        {
        public:     static xSpace::Senarios::Unit build(x::json::object * json);
        protected:  x::string __name;
        protected:  x::string __mod;
        protected:  x::string __category;
        protected:  x::string __type;
        protected:  x::reality::vector __position;
        protected:  x::reality::vector __front;
        protected:  x::reality::vector __up;
        protected:  x::string __relationship;
        protected:  x::real __force;
        public:     inline const x::string & name() const { return __name; }
        public:     inline const x::string & mod() const { return __mod; }
        public:     inline const x::string & category() const { return __category; }
        public:     inline const x::string & type() const { return __type; }
        public:     inline const x::reality::vector & position() const { return __position; }
        public:     inline const x::reality::vector & front() const { return __front; }
        public:     inline const x::reality::vector & up() const { return __up; }
        public:     inline const x::string & relationship() const { return __relationship; }
        public:     inline x::real force() const { return __force; }
        public:     xSpace::Senarios::Unit & operator=(const xSpace::Senarios::Unit & o);
        public:     xSpace::Senarios::Unit & operator=(xSpace::Senarios::Unit && o) noexcept;
        public:     Unit(const x::string & name, const x::string & mod, const x::string & category, const x::string & type, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, const x::string & relationship, x::real force);
        public:     Unit();
        public:     Unit(const xSpace::Senarios::Unit & o);
        public:     Unit(xSpace::Senarios::Unit && o) noexcept;
        public:     virtual ~Unit();
        };
    }
}

#endif // __X_SPACE_SENARIOS__UNIT__HH__
