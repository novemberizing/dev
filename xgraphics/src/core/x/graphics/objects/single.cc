#include "single.hh"

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            single::single(x::graphics::object * object)
            :   x::graphics::object(),
                __object(object)
            {
            }

            single::~single()
            {
                delete __object;
                __object = nullptr;
            }

            void single::start(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __object->start(model, center);
            }

            void single::update(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __object->update(model, center);
            }

            void single::render(const x::reality::vector & position, const x::reality::vector & center)
            {
                __object->render(position, center);
            }
        }
    }
}
