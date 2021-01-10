#include "Joint.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            Joint::Joint(const x::string & name, const x::reality::vector & location, const x::reality::vector & rotation, const x::reality::vector & scale, const x::reality::vector & axis)
            :   x::graphics::objects::joint(location, rotation, scale, axis),
                __name(name)
            {
            }

            Joint::~Joint()
            {
            }

            void Joint::start(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __model = model;

                __model = x::reality::matrix::translate(__model, __location);

                __model = x::reality::matrix::rotate(__model, __axis.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.y(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::rotate(__model, __location.x() > 0 ? __rotation.y() : -__rotation.y(), {1.0f, 0.0f, 0.0f});__model = x::reality::matrix::rotate(__model, __rotation.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.x(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::scale(__model, __scale);

                __objects.each([this, &center](x::var<x::graphics::object *>::type & o){
                    o->start(__model, center);
                });

                __children.each([this, &center](x::var<x::graphics::objects::joint *>::type & joint){
                    joint->start(__model, center);
                });
            }

            void Joint::update(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __model = model;

                __model = x::reality::matrix::translate(__model, __location);

                __model = x::reality::matrix::rotate(__model, __axis.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.y(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __axis.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::rotate(__model, __location.x() > 0 ? __rotation.y() : -__rotation.y(), {1.0f, 0.0f, 0.0f});__model = x::reality::matrix::rotate(__model, __rotation.x(), {1.0f, 0.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.x(), {0.0f, 1.0f, 0.0f});
                __model = x::reality::matrix::rotate(__model, __rotation.z(), {0.0f, 0.0f, 1.0f});

                __model = x::reality::matrix::scale(__model, __scale);

                __objects.each([this, &center](x::var<x::graphics::object *>::type & o){
                    o->update(__model, center);
                });

                __children.each([this, &center](x::var<x::graphics::objects::joint *>::type & joint){
                    joint->update(__model, center);
                });
            }

            void Joint::render(const x::reality::vector & position, const x::reality::vector & center)
            {
                __objects.each([&position, &center](x::var<x::graphics::object *>::type & o){
                    o->render(position, center);
                });

                __children.each([&position, &center](x::var<x::graphics::objects::joint *>::type & joint){
                    joint->render(position, center);
                });
            }
        }
    }
}
