#include "primitive.hh"
#include "application.hh"

#include "opengl.hh"

namespace x
{
    namespace graphics
    {
        primitive::primitive(const x::string & name)
        :   x::graphics::object(name),
            __vertices(),
            __buffer(),
            __program(nullptr),
            __indices()
        {

        }
        primitive::primitive(x::string && name)
        :   x::graphics::object(x::move(name)),
            __vertices(),
            __buffer(),
            __program(nullptr),
            __indices()
        {

        }

        primitive::primitive()
        :   x::graphics::object(),
            __vertices(),
            __buffer(),
            __program(nullptr),
            __indices()
        {
        }

        primitive::primitive(const primitive & o)
        :   x::graphics::object(o),
            __vertices(o.__vertices),
            __buffer(o.__buffer),
            __program(o.__program),
            __indices(o.__indices)
        {
        }

        primitive::primitive(primitive && o) noexcept
        :   x::graphics::object(x::move(o)),
            __vertices(x::move(o.__vertices)),
            __buffer(x::move(o.__buffer)),
            __program(x::move(o.__program)),
            __indices(x::move(o.__indices))
        {
            o.__program = nullptr;
        }

        primitive::~primitive()
        {
        }

        primitive & primitive::operator=(const primitive & o)
        {
            if(&o != this)
            {
                x::graphics::object::operator=(o);
                __vertices = o.__vertices;
                __buffer = o.__buffer;
                __program = o.__program;
                __indices = o.__indices;
            }
            return *this;
        }

        primitive & primitive::operator=(primitive && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::object::operator=(x::move(o));
                __vertices = x::move(o.__vertices);
                __buffer = x::move(o.__buffer);
                __program = x::move(o.__program);
                __indices = x::move(o.__indices);

                o.__program = nullptr;
            }
            return *this;
        }

        void primitive::load()
        {
            x::graphics::application & application = x::graphics::application::get();
            // x::console::out << "load primitive => " << x::endl;
            application.load(*this);
        }

        void primitive::unload()
        {
            x::graphics::application & application = x::graphics::application::get();

            application.unload(*this);
        }

        void primitive::render(const x::graphics::matrix & model, x::uint32 level)
        {
            if(__status != 0)
            {
                if(level == __level)
                {
                    x::graphics::application & application = x::graphics::application::get();
                    const x::graphics::camera & camera = application.camera();
                    const x::graphics::light & light = application.light();
                    const x::graphics::projection & projection = application.projection();

                    x::graphics::matrix mvp = model * camera.matrix() * projection.matrix();

                    application.bind(__vertices);
                    if(__program)
                    {
                        application.bind(*__program);
                        // TODO REMOVE THIS
                        application.bind(*__program, "mvp", mvp);
                        application.bind(*__program, "cameraPos", camera.position());
                        application.bind(*__program, "lightPos", light.position());
                        application.bind(*__program, "lightColor", light.color());
                        application.bind(*__program, "ambientStrength", light.ambient());
                    }
                    else
                    {
                        x::console::out << "program not exist" << x::endl;
                    }


                    application.bind(__buffer);
                    application.bind(0, __buffer, x::graphics::vertex::stride, 0);
                    application.bind(1, __buffer, x::graphics::vertex::stride, 4 * sizeof(GLfloat));
                    application.bind(2, __buffer, x::graphics::vertex::stride, 8 * sizeof(GLfloat));
                    application.draw(__vertices, __indices);
                    application.unbind(2);
                    application.unbind(1);
                    application.unbind(0);
                }
            }
        }
    }
}
