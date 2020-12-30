#include "Resource.hh"

namespace Homeworld2
{
    Homeworld2::Resource * Homeworld2::Resource::__singleton = nullptr;

    Homeworld2::Resource & Resource::get()
    {
        if(__singleton == nullptr)
        {
            static Homeworld2::Resource o;
            __singleton = &o;
        }
        return *__singleton;
    }

    Resource::Resource()
    {
    }

    Resource::~Resource()
    {
    }

    /**
     * Create homeworld shader program object
     *
     * 쉐이더 프로그램의 디렉토리는 [루트 디렉토리]/shader/[프로그램 이름] 이란 디렉토리 밑에
     * fragment.shader, vertex.shader, program.json 으로 구성되어 있다. fragment.shader 는
     * 프레그먼트 쉐이터 소스 파일이며, vertex.shader 는 버텍스 쉐이더 소스 파일이다.
     * program.json 안에는 프로그램에서 사용되는 변수가 저장되어 있습니다.
     *
     * @param   | in | const x::string & | root | root directory |
     * @param   | in | const x::string & | name | shader program name |
     *
     * @return  | x::graphics::program | shader program object |
     */
    x::graphics::program Resource::program(const x::string & root, const x::string & name)
    {
        // CREATE PROGRAM
        x::graphics::program program("homeworld2 " + name);

        // CREATE SHADER (VERTEX & FRAGMENT)
        program.add(x::graphics::shader("homeworld2 " + name + " vertex shader", x::graphics::shader::vertex, x::file::text(root + "/res/homeworld2/shader/" + name + "/vertex.shader")));
        program.add(x::graphics::shader("homeworld2 " + name + " fragment shader", x::graphics::shader::fragment, x::file::text(root + "/res/homeworld2/shader/" + name + "/fragment.shader")));

        // LOAD PROGRAM PARAMETERS FROM JSON
        x::json::array * uniforms = x::json::array::from(root + "/res/homeworld2/shader/" + name + "/program.json");

        uniforms->each([&program](const x::var<x::json::value *>::type & value){
            program.add(x::json::value::as::string(value));
        });

        delete uniforms;

        // RETURN
        return program;
    }

    Homeworld2::Graphics::Reference * Resource::unit(const x::string & root, const x::string & type, const x::string & name)
    {
        x::graphics::application & application = x::graphics::application::get();

        // CREATE REFERENCE
        Homeworld2::Graphics::Reference * reference = Homeworld2::Graphics::ReferenceFile::load(root + "/res/homeworld2/unit/" + type + "/" + name + "/object.hod", name);

        // DISPATCH REFERENCE'S TEXTURE
        application.add(reference->textures());

        x::json::object * spec = x::json::object::from(root + "/res/homeworld2/unit/" + type + "/" + name + "/spec.json");

        x::console::out << *spec << x::endl << x::flush;

        reference->energy(x::json::value::as::number(spec->get("energy")));
        reference->velocity(x::json::value::as::number(spec->get("velocity")));
        reference->mass(x::json::value::as::number(spec->get("mass")));

        delete spec;

        x::console::out << root + "/res/homeworld2/unit/" + type + "/" + name + "/spec.json" << x::endl << x::flush;

        // RETURN
        return reference;
    }

    void Resource::load(x::graphics::application & application)
    {
        // LOAD SHADER PROGRAM
        application.add(program(application.environment.root(), "ship"));

        // LOAD UNIT
        application.add(unit(application.environment.root(), "mobilesuit", "zephyranthes"));
        application.add(unit(application.environment.root(), "mobilesuit", "rgm79c"));
        application.add(unit(application.environment.root(), "mobilesuit", "msm05"));

        application.add(unit(application.environment.root(), "destroyer", "salamis"));
    }

    Homeworld2::Graphics::Objects::Root * Resource::build(const x::string & source)
    {
        Homeworld2::Graphics::Reference * reference = Homeworld2::Graphics::Reference::get(source);

        assertion(reference == nullptr);

        return reference->build();
    }
}
