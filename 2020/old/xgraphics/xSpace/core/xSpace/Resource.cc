#include "Resource.hh"
#include "Objects/Units/Ship.hh"

namespace xSpace
{
    xSpace::Resource * xSpace::Resource::__singleton = nullptr;

    xSpace::Resource & Resource::get()
    {
        if(__singleton == nullptr)
        {
            static xSpace::Resource o(Homeworld2::Resource::get());

            __singleton = &o;
        }
        return *__singleton;
    }

    Resource::Resource(Homeworld2::Resource & homeworld2)
    :   __homeworld2(homeworld2)
    {
    }

    Resource::~Resource()
    {
    }

    void Resource::load(x::graphics::application & application)
    {
        __homeworld2.load(application);
    }

    xSpace::Demo::Scene * Resource::demo()
    {
        xSpace::Demo::Scene * scene = new xSpace::Demo::Scene();

        // /homeworld2/unit/destroyer/salamis

        x::string mod = "homeworld";
        x::string category = "unit";
        x::string type = "salamis";
        x::string name = "salamis";
        x::reality::vector position(0.0f, 0.0f, 0.0f, 1.0f);
        x::reality::vector front(0.0f, 0.0f, 1.0f);
        x::reality::vector up(0.0f, 1.0f, 0.0f);

        xSpace::Objects::Units::Ship * salamis = new xSpace::Objects::Units::Ship(name, position, front, up, __homeworld2.build("salamis"));
        
        scene->add(salamis);

        xSpace::Object::Camera & camera = xSpace::Object::Camera::get();

        camera.set(salamis);

        x::reality::camera::current(&camera);

        return scene;
    }
}
