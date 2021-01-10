#include "Resource.hh"

namespace xSpace
{
    xSpace::Resource * xSpace::Resource::__singleton = nullptr;

    xSpace::Resource & Resource::init(x::graphics::application & application)
    {
        if(__singleton == nullptr)
        {
            static xSpace::Resource o(application.environment.root(), Homeworld2::Resource::get());

            __singleton = &o;

            // LOAD HOMEWORLD2 RESOURCE
            // o.
            // LOAD SENARIO NAME

        }
        return *__singleton;
    }

    xSpace::Resource & Resource::get()
    {
        assertion(__singleton == nullptr);

        return *__singleton;
    }

    Resource::Resource(const x::string & root, Homeworld2::Resource & homeworld2)
    :   __root(root),
        __homeworld2(homeworld2),
        __senarios()
    {
    }

    Resource::~Resource()
    {
        __senarios.each([](const x::string & name, x::var<xSpace::Senario *>::type & senario){
            delete senario;
            senario = nullptr;
        });
    }

    void Resource::load(x::graphics::application & application)
    {
        // LOAD SHADER PROGRAM
        application.add(program(application.environment.root(), "radar"));
        application.add(program(application.environment.root(), "radar-unit"));

        // LOAD HOMEWORLD2 RESOURCE
        __homeworld2.load(application);
        // LOAD SENARIO NAME
        x::file directory(__root + "/res/senario");
        directory.children.each([this](const x::file & f){
            __senarios.put(f.name(), nullptr);
        });
    }

    xSpace::Senario * Resource::senario(const x::string & name)
    {
        xSpace::Senario * senario = __senarios[name];

        if(senario == nullptr)
        {
            senario = xSpace::Senario::build(__root + "/res/senario/" + name + "/map.spec");

            __senarios.put(name, senario);

            // x::json::object * object = x::json::object::from(x::file::text());
            // x::console::out << *object << x::endl;
            // delete object;
        }

        return senario;
    }

    x::graphics::program Resource::program(const x::string & root, const x::string & name)
    {
        // CREATE PROGRAM
        x::graphics::program program("space " + name);

        // CREATE SHADER (VERTEX & FRAGMENT)
        program.add(x::graphics::shader("space " + name + " vertex shader", x::graphics::shader::vertex, x::file::text(root + "/res/shader/" + name + "/vertex.shader")));
        program.add(x::graphics::shader("space " + name + " fragment shader", x::graphics::shader::fragment, x::file::text(root + "/res/shader/" + name + "/fragment.shader")));

        // LOAD PROGRAM PARAMETERS FROM JSON
        x::json::array * uniforms = x::json::array::from(root + "/res/shader/" + name + "/program.json");

        uniforms->each([&program](const x::var<x::json::value *>::type & value){
            program.add(x::json::value::as::string(value));
        });

        delete uniforms;

        // RETURN
        return program;
    }

    xSpace::Object * Resource::unit(xSpace::Senarios::Unit & o)
    {
        if(o.mod() == "homeworld2")
        {
            return new xSpace::Object(__homeworld2.build(o.name(), o.type(), nullptr, o.force(), o.position(), o.front(), o.up()), o.relationship());
        }
        else
        {
            exceptional();
        }
        return nullptr;
    }
}
