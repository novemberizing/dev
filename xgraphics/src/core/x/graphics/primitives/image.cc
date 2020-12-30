#include "image.hh"
#include "../application.hh"


#if 0

namespace x
{
    namespace graphics
    {
        namespace primitives
        {
            static void load(x::graphics::buffer & o)
            {
                o.target(x::graphics::buffer::array);
                o.usage(x::graphics::buffer::statical, x::graphics::buffer::draw);
            }

            static void load(x::graphics::vertices & o)
            {
                o.mode(x::graphics::vertices::triangle);

                o.push(x::graphics::vertex({ 1.0f, 1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f }));
                o.push(x::graphics::vertex({-1.0f, 1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 1.0f }, {1.0f, 0.0f }));
                o.push(x::graphics::vertex({ 1.0f,-1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f }));

                o.push(x::graphics::vertex({-1.0f, 1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 1.0f }, {1.0f, 0.0f }));
                o.push(x::graphics::vertex({ 1.0f,-1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f }));
                o.push(x::graphics::vertex({-1.0f,-1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 1.0f }, {1.0f, 1.0f }));
            }

            image::image(const x::string & name, x::graphics::texture * texture, const x::reality::vector & scale, const x::reality::vector & rotation, x::real repeat)
            :   x::graphics::primitive(name),
                __texture(texture)
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::primitives::load(buffer);
                x::graphics::primitives::load(vertices);

                x::reality::matrix matrix = x::reality::matrix::scale(x::reality::matrix::identity(), scale);
                if(rotation.x())
                {
                    matrix = x::reality::matrix::rotate(matrix, x::radian(rotation.x()), {1.0f, 0.0f, 0.0f});
                }
                if(rotation.y())
                {
                    matrix = x::reality::matrix::rotate(matrix, x::radian(rotation.y()), {0.0f, 1.0f, 0.0f});
                }
                if(rotation.z())
                {
                    matrix = x::reality::matrix::rotate(matrix, x::radian(rotation.z()), {0.0f, 0.0f, 1.0f});
                }

                vertices.each([&matrix, &repeat](x::graphics::vertex & vertex){
                    vertex.location(matrix * vertex.location());
                    vertex.texture(vertex.texture() * repeat);
                });
            }

            image::image(x::string && name, x::graphics::texture * texture, const x::reality::vector & scale, const x::reality::vector & rotation, x::real repeat)
            :   x::graphics::primitive(x::move(name)),
                __texture(texture)
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::primitives::load(buffer);
                x::graphics::primitives::load(vertices);

                x::reality::matrix matrix = x::reality::matrix::scale(x::reality::matrix::identity(), scale);
                if(rotation.x())
                {
                    matrix = x::reality::matrix::rotate(matrix, x::radian(rotation.x()), {1.0f, 0.0f, 0.0f});
                }
                if(rotation.y())
                {
                    matrix = x::reality::matrix::rotate(matrix, x::radian(rotation.y()), {0.0f, 1.0f, 0.0f});
                }
                if(rotation.z())
                {
                    matrix = x::reality::matrix::rotate(matrix, x::radian(rotation.z()), {0.0f, 0.0f, 1.0f});
                }

                vertices.each([&matrix, &repeat](x::graphics::vertex & vertex){
                    vertex.location(matrix * vertex.location());
                    vertex.texture(vertex.texture() * repeat);
                });
            }

            image::image()
            :   x::graphics::primitive("image"),
                __texture(nullptr)
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::primitives::load(buffer);
                x::graphics::primitives::load(vertices);
            }

            image::image(const x::graphics::primitives::image & o)
            :   x::graphics::primitive(o),
                __texture(o.__texture)
            {
            }

            image::image(x::graphics::primitives::image && o) noexcept
            :   x::graphics::primitive(x::move(o)),
                __texture(o.__texture)
            {
                o.__texture = nullptr;
            }

            image::~image()
            {
                __texture = nullptr;
            }

            x::graphics::primitives::image & image::operator=(const x::graphics::primitives::image & o)
            {
                if(&o != this)
                {
                    x::graphics::primitive::operator=(o);

                    __texture = o.__texture;
                }
                return *this;
            }

            x::graphics::primitives::image & image::operator=(x::graphics::primitives::image && o) noexcept
            {
                if(&o != this)
                {
                    x::graphics::primitive::operator=(x::move(o));

                    __texture = o.__texture;

                    o.__texture = nullptr;
                }
                return *this;
            }

            x::boolean image::bind(const x::string & name, x::uint32 id, const x::reality::matrix & matrix)
            {
                if(!x::graphics::primitive::bind(name, id, matrix))
                {
                    x::graphics::application & application = x::graphics::application::get();

                    if(name == "_texture")
                    {
                        // x::console::out << "texture" << x::endl << x::flush;
                        application.bind(*__texture);
                        application.bind(id, 0);    // TEXTURE SLOT
                    }
                }
            }
        }
    }
}

#endif // 0
