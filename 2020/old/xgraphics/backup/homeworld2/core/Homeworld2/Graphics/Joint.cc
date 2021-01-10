#include "Joint.hh"

#include <x/graphics/application.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        Joint::Joint()
        :   __name(),
            __parent(),
            __location(),
            __rotation(),
            __scale(),
            __axis(),
            __freedom(),
            __references(),
            __children(),
            __model()
        {
        }

        Joint::Joint(const Joint & o)
        :   __name(o.__name),
            __parent(o.__parent),
            __location(o.__location),
            __rotation(o.__rotation),
            __scale(o.__scale),
            __axis(o.__axis),
            __freedom(o.__freedom),
            __references(o.__references),
            __children(o.__children),
            __model(o.__model)
        {

        }

        Joint::Joint(Joint && o) noexcept
        :   __name(x::move(o.__name)),
            __parent(x::move(o.__parent)),
            __location(x::move(o.__location)),
            __rotation(x::move(o.__rotation)),
            __scale(x::move(o.__scale)),
            __axis(x::move(o.__axis)),
            __freedom(x::move(o.__freedom)),
            __references(x::move(o.__references)),
            __children(x::move(o.__children)),
            __model(x::move(o.__model))
        {

        }

        Joint::~Joint()
        {

        }

        Joint & Joint::operator=(const Joint & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __parent = o.__parent;
                __location = o.__location;
                __rotation = o.__rotation;
                __scale = o.__scale;
                __axis = o.__axis;
                __freedom = o.__freedom;
                __references = o.__references;
                __children = o.__children;
                __model = o.__model;
            }
            return *this;
        }

        Joint & Joint::operator=(Joint && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __parent = x::move(o.__parent);
                __location = x::move(o.__location);
                __rotation = x::move(o.__rotation);
                __scale = x::move(o.__scale);
                __axis = x::move(o.__axis);
                __freedom = x::move(o.__freedom);
                __references = x::move(o.__references);
                __children = x::move(o.__children);
                __model = x::move(o.__model);
            }
            return *this;
        }

        Object * Joint::build()
        {
            Object * object = new Object(__name, __location, __rotation, __scale, __axis);

            __references.each([object](x::var<x::graphics::reference *>::type & reference) {
                object->add(reference);
            });

            __children.each([object](x::var<Joint *>::type & joint){
                object->add(joint->build());
            });

            return object;
        }
    }
}
