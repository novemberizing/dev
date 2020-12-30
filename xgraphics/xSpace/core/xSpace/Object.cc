#include "Object.hh"

namespace xSpace
{
    Object::Object(const x::string & name, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, x::graphics::object * graphics)
    :   x::graphics::object(),
        __name(name),
        __position(position),
        __front(front),
        __up(up),
        __model(),
        __graphics(graphics),
        __velocity(0),
        __force(0)
    {
    }

    Object::~Object()
    {
        if(__graphics)
        {
            delete __graphics;
            __graphics = nullptr;
        }
    }

    void Object::start(const x::reality::matrix & model, const x::reality::vector & center)
    {
        __model = model;
        __model = x::reality::matrix::translate(__model, __position);

        __graphics->start(__model, center);
    }

    void Object::update(const x::reality::matrix & model, const x::reality::vector & center)
    {
        // __force
        // __velocity

        __model = model;
        __model = x::reality::matrix::translate(__model, __position);

        __graphics->update(__model, center);
    }

    void Object::render(const x::reality::vector & position, const x::reality::vector & center)
    {
        (void)(position);

        __graphics->render(__position, center);
    }

    xSpace::Object::Camera * xSpace::Object::Camera::__singleton = nullptr;

    xSpace::Object::Camera & xSpace::Object::Camera::get()
    {
        if(__singleton == nullptr)
        {
            static xSpace::Object::Camera o;

            __singleton = &o;
        }
        return *__singleton;
    }

    Object::Camera::Camera()
    :   x::reality::camera(),
        __object(nullptr)
    {
    }

    Object::Camera::~Camera()
    {
    }

    void Object::Camera::set(x::graphics::object * object)
    {
        __object = object;

        __location = object->position() + (-500.0f * object->front()) + (100.0f * object->up());
        __center = object->position() + (500.0f * object->front()) + (100.0f * object->up());
        __up = object->up();
    }
}
