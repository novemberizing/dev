#include "Reference.hh"

namespace Homeworld2
{
    Reference::Reference(const x::string & name, Homeworld2::Graphics::Reference * graphics, Homeworld2::Physics::Reference * physics)
    :   x::reality::reference(name),
        x::graphics::reference(),
        x::physics::reference(),
        __graphics(graphics),
        __physics(physics)
    {
    }

    Reference::~Reference()
    {
        if(__graphics)
        {
            delete __graphics;
            __graphics = nullptr;
        }

        if(__physics)
        {
            delete __physics;
            __physics = nullptr;
        }
    }

    void Reference::load()
    {
        assertion(__graphics == nullptr);

        __graphics->load();
    }

    void Reference::unload()
    {
        assertion(__graphics == nullptr);

        __graphics->unload();
    }

    void Reference::render(const x::reality::matrix & model)
    {
        assertion(__graphics == nullptr);

        __graphics->render(model);
    }

    const x::real Reference::weight() const
    {
        assertion(__physics == nullptr);

        return __physics->weight();
    }

    void Reference::weight(x::real v)
    {
        assertion(__physics == nullptr);

        __physics->weight(v);
    }

    const x::real Reference::energy() const
    {
        assertion(__physics == nullptr);

        return __physics->energy();
    }

    void Reference::energy(x::real v)
    {
        assertion(__physics == nullptr);

        __physics->energy(v);
    }
}
