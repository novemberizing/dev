#include "Object.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Object::Object(const x::string & name, const x::reality::vector & location, const x::reality::vector & rotation, x::reality::vector & scale, x::reality::vector & axis)
        :   x::reality::object(name, {0.0f, 0.0f, 0.0f}),
            x::graphics::object(location, rotation, scale, axis),
            __objects(),
            __references()
        {
        }

        Object::Object()
        :   x::reality::object(),
            x::graphics::object(),
            __objects(),
            __references()
        {
        }

        Object::Object(Object && o) noexcept
        :   x::reality::object(x::move(o)),
            x::graphics::object(x::move(o)),
            __objects(x::move(o.__objects)),
            __references(x::move(o.__references))
        {
        }

        Object::~Object()
        {
            __objects.each([](const x::string & name, x::var<Object *>::type & object){
                if(object)
                {
                    delete object;
                    object = nullptr;
                }
            });
        }

        Object & Object::operator=(Object && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::object::operator=(x::move(o));

                __objects = x::move(o.__objects);
                __references = x::move(o.__references);
            }
            return *this;
        }

        void Object::render(const x::reality::matrix & model)
        {
            __model = model;

            __model = x::reality::matrix::translate(__model, __position);
            __model = x::reality::matrix::translate(__model, __location);

            __model = x::reality::matrix::rotate(__model, __axis.x(), {1.0f, 0.0f, 0.0f});
            __model = x::reality::matrix::rotate(__model, __axis.y(), {0.0f, 1.0f, 0.0f});
            __model = x::reality::matrix::rotate(__model, __axis.z(), {0.0f, 0.0f, 1.0f});

            __model = x::reality::matrix::rotate(__model, __location.x() > 0 ? __rotation.y() : -__rotation.y(), {1.0f, 0.0f, 0.0f});
            __model = x::reality::matrix::rotate(__model, __rotation.x(), {0.0f, 1.0f, 0.0f});
            __model = x::reality::matrix::rotate(__model, __rotation.z(), {0.0f, 0.0f, 1.0f});

            __model = x::reality::matrix::scale(__model, __scale);

            __references.each([this](x::var<x::graphics::reference *>::type reference){
                reference->render(__model);
            });

            __objects.each([this](const x::string & name, x::var<Object *>::type & object) {
                object->render(__model);
            });
        }
    }
}
