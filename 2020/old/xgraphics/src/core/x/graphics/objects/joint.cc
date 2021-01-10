#include "joint.hh"

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            joint::joint(const x::reality::vector & location, const x::reality::vector & rotation, const x::reality::vector & scale, const x::reality::vector & axis)
            :   x::graphics::object(),
                __location(location),
                __rotation(rotation),
                __scale(scale),
                __axis(axis),
                __model(),
                __children(),
                __objects()
            {
            }

            joint::~joint()
            {
                __children.each([](x::var<x::graphics::objects::joint *>::type & joint){
                    delete joint;
                    joint = nullptr;
                });
                __objects.each([](x::var<x::graphics::object *>::type & object){
                    delete object;
                    object = nullptr;
                });
            }

            void joint::start(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __model = model;

                __model = x::reality::matrix::translate(__model, __location);

                __model = x::reality::matrix::rotate(__model, __axis.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.y(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::rotate(__model, __rotation.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.y(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::scale(__model, __scale);

                __objects.each([this, &center](x::var<x::graphics::object *>::type & object){
                    object->start(__model, center);
                });

                __children.each([this, &center](x::var<x::graphics::objects::joint *>::type & joint){
                    joint->start(__model, center);
                });
            }

            void joint::update(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __model = model;

                __model = x::reality::matrix::translate(__model, __location);

                __model = x::reality::matrix::rotate(__model, __axis.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.y(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::rotate(__model, __rotation.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.y(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::scale(__model, __scale);

                __objects.each([this, &center](x::var<x::graphics::object *>::type & object){
                    object->update(__model, center);
                });

                __children.each([this, &center](x::var<x::graphics::objects::joint *>::type & joint){
                    joint->update(__model, center);
                });
            }

            void joint::render(const x::reality::vector & position, const x::reality::vector & center)
            {
                __objects.each([&position, &center](x::var<x::graphics::object *>::type & object){
                    object->render(position, center);
                });

                __children.each([&position, &center](x::var<x::graphics::objects::joint *>::type & joint){
                    joint->render(position, center);
                });
            }

            void joint::add(x::graphics::objects::joint * o)
            {
                __children.append(o);
            }

            void joint::dock(x::graphics::object * o)
            {
                __objects.append(o);
            }
        }
    }
}
