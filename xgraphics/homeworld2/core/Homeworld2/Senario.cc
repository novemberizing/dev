#include "Senario.hh"

#include "Senarios/Unit.hh"

namespace Homeworld2
{
    Senario * Senario::open(const x::string & name, Homeworld2::Resource & resource)
    {
        x::graphics::application & application = x::graphics::application::get();

        x::json::object * json = x::json::object::from(application.environment.root() + "/res/homeworld2/senario/" + name + "/map.json");


        Senario * senario = new Senario();

        senario->__name = x::json::value::as::string(json->get("name"));

        const x::array<x::json::value *> & units = x::json::value::as::array(json->get("units"));

        units.each([senario](const x::var<x::json::value *>::type & value) {
            senario->__units.append(Homeworld2::Senarios::Unit::from(x::json::cast::object(value)));
        });

        delete json;

        x::console::out << "senario name => " << senario->__name << x::endl;

        return senario;

    }

//     Senario * Senario::load(const x::string & path)
//     {
//         x::json::object * json = x::json::object::from(path);
//
//         Senario * senario = new Senario();
//
// // public:     x::json::value * get(const x::string & key)
//         senario->__name = x::json::value::as::string(json->get("name"));
//
//         delete json;
//
//         x::console::out << "senario name => " << senario->__name;
//
//
//
//         return senario;
//     }

    Senario::Senario()
    :   __name(),
        __units()
    {
    }

    Senario::~Senario()
    {
    }
}
