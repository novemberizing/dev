#include "base.hh"

#include <x/graphics/application.hh>

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            base::base(x::graphics::reference * reference, x::graphics::program * program)
            :   x::graphics::object(),
                __reference(reference),
                __program(program),
                __texture(nullptr),
                __model(x::reality::matrix::identity)
            {
            }

            base::base(x::graphics::reference * reference, x::graphics::program * program, x::graphics::texture * texture)
            :   x::graphics::object(),
                __reference(reference),
                __program(program),
                __texture(texture),
                __model(x::reality::matrix::identity)
            {
            }

            base::~base()
            {
            }

            void base::start(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __model = model;
            }

            void base::update(const x::reality::matrix & model, const x::reality::vector & center)
            {
                __model = model;
            }

            void base::render(const x::reality::vector & position, const x::reality::vector & center)
            {
                x::graphics::application & application = x::graphics::application::get();

                application.bind(*__program, *this);
                application.render(*__reference);
            }

            x::boolean base::bind(const x::string & name, x::uint32 id)
            {
                if(name == "_matrix")
                {
                    x::graphics::application & application = x::graphics::application::get();
                    const x::reality::camera & camera = x::reality::camera::current();
                    const x::reality::projection & projection = x::reality::projection::current();

                    x::reality::matrix matrix = __model * camera.matrix() * projection.matrix();

                    application.bind(id, matrix);

                    return true;
                }
                else if(name == "_camera")
                {
                    x::graphics::application & application = x::graphics::application::get();
                    const x::reality::camera & camera = x::reality::camera::current();

                    application.bind(id, camera.location());

                    return true;
                }
                else if(name == "_texture")
                {
                    if(__texture)
                    {
                        x::graphics::application & application = x::graphics::application::get();

                        application.bind(*__texture);
                        application.bind(id, 0);        // TEXTURE SLOT
                        return true;
                    }
                }
                return false;
            }
        }
    }
}
