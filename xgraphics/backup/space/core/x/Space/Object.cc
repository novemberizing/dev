#include "Object.hh"

namespace xSpace
{
    Object::Object(x::graphics::object * object, const x::string & relationship)
    :   x::graphics::object(),
        __object(object),
        __physics(object),
        __relationship(relationship),
        __selected(false)
    {
    }

    Object::~Object()
    {
        if(__object)
        {
            delete __object;
            __object = nullptr;
        }
    }

    void Object::selected(x::boolean v)
    {
        __selected = v;
        if(__selected)
        {
            // CTRL KEY DOWN (ADD) ELSE (CLEAR AND ONE)
        }
    }

    void Object::start(const x::reality::matrix & model, const x::reality::camera & camera)
    {
        // __physics->start(model, camera);

        x::console::out << "mass => " << __physics->mass() << x::endl << x::flush;

        __object->start(model, camera);
    }

    void Object::update(const x::reality::matrix & model, const x::reality::camera & camera)
    {
        // __physics->update(model, camera);

        __object->update(model, camera);
    }
}
