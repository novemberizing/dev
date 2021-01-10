#include "Unit.hh"

namespace xSpace
{
    namespace Senarios
    {
        xSpace::Senarios::Unit Unit::build(x::json::object * json)
        {
            return xSpace::Senarios::Unit(x::json::value::as::string(json->get("name")),
                                          x::json::value::as::string(json->get("mod")),
                                          x::json::value::as::string(json->get("category")),
                                          x::json::value::as::string(json->get("type")),
                                          x::json::value::as::vector(json->get("position")),
                                          x::json::value::as::vector(json->get("front")),
                                          x::json::value::as::vector(json->get("up")),
                                          x::json::value::as::string(json->get("relationship")),
                                          x::json::value::as::number(json->get("force")));
        }

        Unit::Unit(const x::string & name, const x::string & mod, const x::string & category, const x::string & type, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, const x::string & relationship, x::real force)
        :   __name(name),
            __mod(mod),
            __category(category),
            __type(type),
            __position(position),
            __front(front),
            __up(up),
            __relationship(relationship),
            __force(force)
        {
        }

        Unit::Unit()
        :   __name(),
            __mod(),
            __category(),
            __type(),
            __position(),
            __front(),
            __up(),
            __relationship()
        {
        }

        Unit::Unit(const xSpace::Senarios::Unit & o)
        :   __name(o.__name),
            __mod(o.__mod),
            __category(o.__category),
            __type(o.__type),
            __position(o.__position),
            __front(o.__front),
            __up(o.__up),
            __relationship(o.__relationship)
        {
        }

        Unit::Unit(xSpace::Senarios::Unit && o) noexcept
        :   __name(x::move(o.__name)),
            __mod(x::move(o.__mod)),
            __category(x::move(o.__category)),
            __type(x::move(o.__type)),
            __position(x::move(o.__position)),
            __front(x::move(o.__front)),
            __up(x::move(o.__up)),
            __relationship(x::move(o.__relationship))
        {
        }

        Unit::~Unit()
        {
        }

        xSpace::Senarios::Unit & Unit::operator=(const xSpace::Senarios::Unit & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __mod = o.__mod;
                __category = o.__category;
                __type = o.__type;
                __position = o.__position;
                __front = o.__front;
                __up = o.__up;
                __relationship = o.__relationship;
            }
            return *this;
        }

        xSpace::Senarios::Unit & Unit::operator=(xSpace::Senarios::Unit && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __mod = x::move(o.__mod);
                __category = x::move(o.__category);
                __type = x::move(o.__type);
                __position = x::move(o.__position);
                __front = x::move(o.__front);
                __up = x::move(o.__up);
                __relationship = x::move(o.__relationship);
            }
            return *this;
        }
    }
}
