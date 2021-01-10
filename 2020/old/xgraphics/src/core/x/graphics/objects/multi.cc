#include "multi.hh"

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            multi::multi()
            :   x::graphics::object(),
                __objects()
            {
            }

            multi::~multi()
            {
                __objects.each([](x::var<x::graphics::object *>::type & object){
                    delete object;
                    object = nullptr;
                });
            }

            void multi::add(x::graphics::object * o)
            {
                __objects.append(o);
            }

            void multi::start(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __objects.each([&model, &center](x::var<x::graphics::object *>::type & object){
                    object->start(model, center);
                });
            }

            void multi::update(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __objects.each([&model, &center](x::var<x::graphics::object *>::type & object){
                    object->update(model, center);
                });
            }

            void multi::render(const x::reality::vector & position, const x::reality::vector & center)
            {
                __objects.each([&position, &center](x::var<x::graphics::object *>::type & object){
                    object->render(position, center);
                });
            }
        }
    }
}
