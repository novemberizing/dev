#include "../Object.hh"

namespace xSpace
{
    xSpace::Object::Camera * xSpace::Object::Camera::__singleton = nullptr;

    xSpace::Object::Camera & Object::Camera::get()
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

    void Object::Camera::set(xSpace::Object * o)
    {
        __object = o;

        if(__object)
        {
            __center = (100.0f * __object->front()) + __object->position();
            __location = (-100.0f * __object->front()) + __object->position() + x::reality::vector({0.0f, 95.0f, 0.0f});
            __up = __object->up();

            x::console::out << __center << x::endl << x::flush;
            x::console::out << __location << x::endl << x::flush;
            x::console::out << __up << x::endl << x::flush;

            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }
    }

    void Object::Camera::start()
    {
        if(__object)
        {
            __center = (100.0f * __object->front()) + __object->position();
            __location = (-100.0f * __object->front()) + __object->position() + x::reality::vector({0.0f, 95.0f, 0.0f});
            __up = __object->up();

            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }
    }

    void Object::Camera::update()
    {
        if(__object)
        {
            __center = (100.0f * __object->front()) + __object->position();
            __location = (-100.0f * __object->front()) + __object->position() + x::reality::vector({0.0f, 95.0f, 0.0f});
            __up = __object->up();

            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }
    }
}
