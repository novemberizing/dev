#include "Unit.hh"

namespace Homeworld2
{
    namespace Senarios
    {
        Unit Unit::from(const x::json::object * object)
        {
            return Unit(x::json::value::as::string(object->get("name")),
                        x::json::value::as::string(object->get("category")),
                        x::json::value::as::string(object->get("type")),
                        x::json::value::as::vector(object->get("position")),
                        x::json::value::as::vector(object->get("front")),
                        x::json::value::as::vector(object->get("up")));
        }

        Unit::Unit(const x::string & name, const x::string & category, const x::string & type, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up)
        :   __name(name),
            __category(category),
            __type(type),
            __position(position),
            __front(front),
            __up(up)
        {
        }

        Unit::Unit()
        :   __name(),
            __category(),
            __type(),
            __position(),
            __front(),
            __up()
        {
        }

        Unit::Unit(const Homeworld2::Senarios::Unit & o)
        :   __name(o.__name),
            __category(o.__category),
            __type(o.__type),
            __position(o.__position),
            __front(o.__front),
            __up(o.__up)
        {
        }

        Unit::Unit(Homeworld2::Senarios::Unit && o) noexcept
        :   __name(x::move(o.__name)),
            __category(x::move(o.__category)),
            __type(x::move(o.__type)),
            __position(x::move(o.__position)),
            __front(x::move(o.__front)),
            __up(x::move(o.__up))
        {
        }

        Unit::~Unit()
        {
        }

        Homeworld2::Senarios::Unit & Unit::operator=(const Homeworld2::Senarios::Unit & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __category = o.__category;
                __type = o.__type;
                __position = o.__position;
                __front = o.__front;
                __up = o.__up;
            }
            return *this;
        }

        Homeworld2::Senarios::Unit & Unit::operator=(Homeworld2::Senarios::Unit && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __category = x::move(o.__category);
                __type = x::move(o.__type);
                __position = x::move(o.__position);
                __front = x::move(o.__front);
                __up = x::move(o.__up);
            }
            return *this;
        }
    }
}
