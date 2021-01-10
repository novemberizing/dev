#include "root.hh"

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            root::root(x::graphics::objects::joint * root)
            :   x::graphics::object(),
                __root(root)
            {
            }

            root::~root()
            {
                delete __root;
                __root = nullptr;
            }

            void root::start(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __root->start(model, center);
            }

            void root::update(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __root->update(model, center);
            }

            void root::render(const x::reality::vector & position, const x::reality::vector & center)
            {
                __root->render(position, center);
            }
        }
    }
}
