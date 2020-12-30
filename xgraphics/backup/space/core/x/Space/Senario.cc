#include "Senario.hh"

namespace xSpace
{
    xSpace::Senario * Senario::build(const x::string & path)
    {
        x::json::object * object = x::json::object::from(path);

        xSpace::Senario * senario = new xSpace::Senario(x::json::value::as::string(object->get("name")));

        x::json::array * units = x::json::cast::array(object->get("units"));

        for(x::uint64 i = 0; i < units->size(); i++)
        {
            senario->units.append(xSpace::Senarios::Unit::build(x::json::cast::object(units->at(i))));
        }


        delete object;

        return senario;
    }

    Senario::Senario(const x::string & name)
    :   __name(name),
        units()
    {
    }

    Senario::Senario()
    :   __name(),
        units()
    {
    }

    Senario::Senario(const xSpace::Senario & o)
    :   __name(o.__name),
        units(o.units)
    {
    }

    Senario::Senario(xSpace::Senario && o) noexcept
    :   __name(x::move(o.__name)),
        units(x::move(o.units))
    {
    }

    Senario::~Senario()
    {
    }

    xSpace::Senario & Senario::operator=(const xSpace::Senario & o)
    {
        if(&o != this)
        {
            __name = o.__name;
            units = o.units;
        }
        return *this;
    }

    xSpace::Senario & Senario::operator=(const xSpace::Senario && o) noexcept
    {
        if(&o != this)
        {
            __name = x::move(o.__name);
            units = x::move(o.units);
        }
        return *this;
    }
}
