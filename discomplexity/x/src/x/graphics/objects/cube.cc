#include "cube.hh"
#include "../application.hh"

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            static void load(x::graphics::buffer & o)
            {
                o.target(x::graphics::buffer::array);
                o.usage(x::graphics::buffer::statical, x::graphics::buffer::draw);
            }

            static void load(x::graphics::vertices & o)
            {
                o.mode(x::graphics::vertices::triangle);

                o.push(x::graphics::vertex({-1.0f,-1.0f,-1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f, 1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f, 1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}));

                o.push(x::graphics::vertex({ 1.0f, 1.0f,-1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f,-1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f,-1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}));

                o.push(x::graphics::vertex({ 1.0f,-1.0f, 1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f,-1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}));
                o.push(x::graphics::vertex({ 1.0f,-1.0f,-1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}));

                o.push(x::graphics::vertex({ 1.0f, 1.0f,-1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}));
                o.push(x::graphics::vertex({ 1.0f,-1.0f,-1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f,-1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}));

                o.push(x::graphics::vertex({-1.0f,-1.0f,-1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f, 1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f,-1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}));

                o.push(x::graphics::vertex({ 1.0f,-1.0f, 1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f, 1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f,-1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}));

                o.push(x::graphics::vertex({-1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f, 1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}));
                o.push(x::graphics::vertex({ 1.0f,-1.0f, 1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}));

                o.push(x::graphics::vertex({ 1.0f, 1.0f, 1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({ 1.0f,-1.0f,-1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({ 1.0f, 1.0f,-1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}));

                o.push(x::graphics::vertex({ 1.0f,-1.0f,-1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({ 1.0f, 1.0f, 1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}));
                o.push(x::graphics::vertex({ 1.0f,-1.0f, 1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}));

                o.push(x::graphics::vertex({ 1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}));
                o.push(x::graphics::vertex({ 1.0f, 1.0f,-1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f,-1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}));

                o.push(x::graphics::vertex({ 1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f,-1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}));

                o.push(x::graphics::vertex({ 1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}));
                o.push(x::graphics::vertex({-1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}));
                o.push(x::graphics::vertex({ 1.0f,-1.0f, 1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}));
            }

            cube::cube(const x::string & name)
            :   x::graphics::primitive(name)
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::objects::load(__buffer);
                x::graphics::objects::load(__vertices);

                __program = application.program("standard");
            }

            cube::cube(x::string && name)
            :   x::graphics::primitive(x::move(name))
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::objects::load(__buffer);
                x::graphics::objects::load(__vertices);
                __program = application.program("standard");
            }

            cube::cube()
            :   x::graphics::primitive()
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::objects::load(__buffer);
                x::graphics::objects::load(__vertices);
                __program = application.program("standard");
            }

            cube::cube(const cube & o)
            :   x::graphics::primitive(o)
            {
            }

            cube::cube(cube && o) noexcept
            :   x::graphics::primitive(x::move(o))
            {
            }

            cube::~cube()
            {
            }

            cube & cube::operator=(const cube & o)
            {
                if(&o != this)
                {
                    x::graphics::primitive::operator=(o);
                }
                return *this;
            }

            cube & cube::operator=(cube && o) noexcept
            {
                if(&o != this)
                {
                    x::graphics::primitive::operator=(x::move(o));
                }
                return *this;
            }

            void cube::render(const x::graphics::matrix & model, x::uint32 level)
            {
                // x::console::out << "render cube" << x::endl;

                x::graphics::application & application = x::graphics::application::get();
                const x::graphics::camera & camera = application.camera();
                const x::graphics::light & light = application.light();
                const x::graphics::projection & projection = application.projection();
#if 1
                // __mvp =
                // x::graphics::matrix projection = projection.matrix();
                //     // x::graphics::matrix::perspective(x::math::radian(45.0f), (float32) application.width() / (float32) application.height(), 0.1f, 1000.0f);
                // x::graphics::matrix view = x::graphics::matrix::lookat(camera.position(), camera.center(), camera.up());
                // x::graphics::matrix model = x::graphics::matrix::identity();
                x::graphics::matrix mvp = model * camera.matrix() * projection.matrix();

#if 0
                glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float32) application.width() / (float32) application.height(), 0.1f, 1000.0f);

                glm::mat4 View = glm::lookAt(
                    glm::vec3(camera.position().x(),camera.position().y(),camera.position().z()), // 카메라는 (4,3,3) 에 있다. 월드 좌표에서
                    glm::vec3(0,0,0), // 그리고 카메라가 원점을 본다
                    glm::vec3(0,1,0));  // 머리가 위쪽이다 (0,-1,0 으로 해보면, 뒤집어 볼것이다)

                glm::mat4 Model = glm::mat4(1.0f);
                glm::mat4 _mvp = Projection * View * Model;

                x::console::out << _mvp << x::endl;
#endif // 0
#endif // 1

                application.bind(__vertices);
                application.bind(*__program);
                application.bind(*__program, "mvp", mvp);
                application.bind(*__program, "cameraPos", camera.position());
                application.bind(*__program, "lightPos", light.position());
                application.bind(*__program, "lightColor", light.color());
                application.bind(*__program, "ambientStrength", light.ambient());

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
