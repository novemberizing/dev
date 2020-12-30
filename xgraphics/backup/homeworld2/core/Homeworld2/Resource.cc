#include "Resource.hh"
#include "Graphics/ReferenceFile.hh"
#include "Physics/ReferenceFile.hh"

namespace Homeworld2
{
    Resource * Resource::__singleton = nullptr;

    Resource & Resource::init(const x::string & path)
    {
        if(__singleton == nullptr)
        {
            static Resource o(path);
            __singleton = &o;
        }

        return *__singleton;
    }

    Resource & Resource::get()
    {
        assertion(__singleton == nullptr);

        return *__singleton;
    }

    Resource::Resource(const x::string & path)
    :   __path(path),
        __references()
    {
    }

    Resource::~Resource()
    {
    }

    void Resource::load()
    {
        x::file resource(__path);

        resource.children.each([this](const x::file & main){
            if(main.name() == "unit")
            {
                main.children.each([this](const x::file & type) {
                    if(type.name() == "ship")
                    {
                        type.children.each([this](const x::file & unit) {
                            Homeworld2::Graphics::Reference * graphics = Homeworld2::Graphics::ReferenceFile::load(unit.find([](const x::file & file){ return file.extension() == "hod"; }), unit.name());
                            Homeworld2::Physics::Reference * physics = Homeworld2::Physics::ReferenceFile::load(unit.find([](const x::file & file){ return file.extension() == "spec"; }), unit.name());

                            __references.put(unit.name(), new Homeworld2::Reference(unit.name(), graphics, physics));
                        });
                    }
                    else
                    {
                        // x::console::out << type.name() << x::endl;
                    }
                });
            }
            else if(main.name() == "shader")
            {
                main.children.each([this](const x::file & type) {
                    if(type.name() == "ship")
                    {
                        x::graphics::program program(type.name());

                        program.add(shader(type.name(), type.find([](const x::file & file){ return file.title() == "vertex"; })));
                        program.add(shader(type.name(), type.find([](const x::file & file){ return file.title() == "fragment"; })));

                        x::json::array * uniforms = x::json::array::from(type.find([](const x::file & file){ return file.extension() == "spec"; }));
                        uniforms->each([this, &program](const x::var<x::json::value *>::type & value){
                            program.add(x::json::value::as::string(value));
                        });
                        delete uniforms;
                    }
                });
            }
            else if(main.name() == "map")
            {
                
            }
            else
            {
                exceptional();
            }
        });

        resource.get([](const x::file & f){
            if(f.type() == x::file::type::regular)
            {
                x::console::out << f.path() << x::endl;
            }
        });
        x::console::out << "load" << x::endl;
    }

    x::graphics::shader Resource::shader(const x::string & name, const x::file & f)
    {
        if(f.title() == "vertex")
        {
            return x::graphics::shader(name + " vertex shader", x::graphics::shader::vertex, x::file::text(f.path()));
        }
        else if(f.title() == "fragment")
        {
            return x::graphics::shader(name + " fragment shader", x::graphics::shader::fragment, x::file::text(f.path()));
        }
        else
        {
            exceptional();
        }
    }
}
