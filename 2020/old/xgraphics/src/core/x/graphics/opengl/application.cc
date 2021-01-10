#include "application.hh"
#include "shaders/coordinate.system.hh"
#include "shaders/standard.hh"
#include "shaders/simple.hh"
#include "shaders/image.hh"
#include "programs/coordinate.system.hh"
#include "programs/standard.hh"
#include "programs/simple.hh"
#include "programs/image.hh"
#include "../primitives/triangle.hh"
#include "../primitives/rectangle.hh"
#include "../primitives/cube.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace callback
            {
                static void idle()
                {
                    x::graphics::application & application = x::graphics::application::get();

                    application.idle();
                }

                static void render()
                {
                    x::graphics::application & application = x::graphics::application::get();

                    application.render();
                }

                static void keyboard(unsigned char key, int x, int y)
                {
                    x::graphics::application & application = x::graphics::application::get();
                    application.keyboard(key, x, y);
                }

                static void special(int key, int x, int y)
                {
                    x::graphics::application & application = x::graphics::application::get();
                    x::console::out << key << x::endl << x::flush;
                    application.special(x::graphics::opengl::key::get(key), x, y);
                }

                static void animation(int value)
                {
                    x::graphics::application & application = x::graphics::application::get();

                    application.animation();
                }

                static void mousemove(int x, int y)
                {
                    x::graphics::application & application = x::graphics::application::get();

                    if(!application.mousemove(x, y))
                    {
                        // x::console::out << "mousemove => " << x << "," << y << x::endl << x::flush;
                    }
                }

                static void mouse(int button, int state, int x, int y)
                {
                    x::graphics::application & application = x::graphics::application::get();

                    if(!application.mouse(x::graphics::opengl::mouse::button(button), x::graphics::opengl::mouse::state(state), x, y))
                    {
                        x::console::out << "mouse => " << x << "," << y << x::endl << x::flush;
                    }

                    if(state == GLUT_DOWN)
                    {
                        if(button == GLUT_LEFT_BUTTON)
                        {

                        }
                    }
                }
            }

            x::graphics::application & application::init(int argc, char ** argv, x::function<void (x::graphics::application &)> func)
            {
                if(x::graphics::application::__singleton == nullptr)
                {
                    static x::graphics::opengl::application o;

                    x::graphics::application::__singleton = &o;

                    x::string current = x::directory::current(argv[0]);

                    o.environment.root(current);

                    o.add(x::graphics::opengl::shaders::simple::vertex);
                    o.add(x::graphics::opengl::shaders::simple::fragment);
                    o.add(x::graphics::opengl::shaders::coordinate::system::vertex);
                    o.add(x::graphics::opengl::shaders::coordinate::system::fragment);
                    o.add(x::graphics::opengl::shaders::standard::vertex);
                    o.add(x::graphics::opengl::shaders::standard::fragment);
                    o.add(x::graphics::opengl::shaders::image::vertex);
                    o.add(x::graphics::opengl::shaders::image::fragment);

                    o.add(x::graphics::opengl::programs::simple::program);
                    o.add(x::graphics::opengl::programs::standard::program);
                    o.add(x::graphics::opengl::programs::coordinate::system::program);
                    o.add(x::graphics::opengl::programs::image::program);

                    o.add(new x::graphics::primitives::triangle());
                    o.add(new x::graphics::primitives::rectangle());
                    o.add(new x::graphics::primitives::cube());

                    glutInit(&argc, argv);

                    if(func != nullptr)
                    {
                        func(o);
                    }

                    glutInitContextVersion(o.__major, o.__minor);
                    glutInitDisplayMode(o.__mode);
                    glutInitWindowSize(o.__width, o.__height);
                    glutInitWindowPosition(o.__x, o.__y);
                    glutCreateWindow(o.__name.str());

                    glEnable(GL_DEPTH_TEST);
                    glDepthFunc(GL_LESS);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    glewInit();
                }

                return x::graphics::application::get();
            }

            application::application()
            :   x::graphics::application(),
                __mode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH),
                __major(4),
                __minor(5)
            {
            }

            application::~application()
            {
            }

            void application::animation()
            {
                x::timestamp current = x::timestamp::current();
                // render
                render();
                // update surface
                if(__surface)
                {
                    __surface->update();
                }
                // update camera
                x::reality::camera & camera = x::reality::camera::current();
                camera.update();
                // x::reality::camera & main
                __timestamp = x::timestamp::current();
                x::int64 millisecond = __timestamp.millisecond() - current.millisecond();
                if(millisecond < __fps)
                {
                    glutTimerFunc(__fps - millisecond, x::graphics::opengl::callback::animation, 0);
                }
                else
                {
                    // x::console::out << current.second() << ":" << current.micro() << x::endl;
                    // x::console::out << __timestamp.second() << ":" << __timestamp.micro() << x::endl;
                    // x::console::out << millisecond << x::endl;
                    // x::console::out << __fps << x::endl;
                    glutTimerFunc(0, x::graphics::opengl::callback::animation, 0);
                }
            }

            void application::render()
            {
                if(__surface)
                {
                    glClearColor(__surface->background[0], __surface->background[1], __surface->background[2], __surface->background[3]);

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    __surface->layers.each([](x::var<x::graphics::layer *>::type & layer){
                        layer->render();
                        glClear(GL_DEPTH_BUFFER_BIT);
                    });

                    glutSwapBuffers();
                }
                else
                {
                    exceptional();
                }
            }

            void application::render(x::graphics::reference & reference)
            {
                reference.render();
            }

            void application::idle()
            {
                x::graphics::opengl::debug();

                engine.cycle();
            }

            x::int32 application::run()
            {
                engine.initialize();

                textures.each([](const x::string & name, x::graphics::texture & texture) {
                    x::graphics::application & application = x::graphics::application::get();
                    application.load(texture);
                });

                programs.each([](const x::string & name, x::graphics::program & program){
                    x::graphics::application & application = x::graphics::application::get();
                    application.load(program);
                });

                references.each([](const x::string & name, x::var<x::graphics::reference *>::type & reference){
                    reference->load();
                });

                glutDisplayFunc(x::graphics::opengl::callback::render);
                glutIdleFunc(x::graphics::opengl::callback::idle);
                glutKeyboardFunc(x::graphics::opengl::callback::keyboard);
                glutSpecialFunc(x::graphics::opengl::callback::special);

                // glutMotionFunc(x::graphics::opengl::mousemove);
                // FOR DEBUG
                glutPassiveMotionFunc(x::graphics::opengl::callback::mousemove);
                glutMouseFunc(x::graphics::opengl::callback::mouse);

                __timestamp = x::timestamp::current();
                glutTimerFunc(__fps, x::graphics::opengl::callback::animation, 0);

                if(__surface)
                {
                    __surface->start();
                }

                glutMainLoop();


                programs.each([](const x::string & name, x::graphics::program & program){
                    x::graphics::application & application = x::graphics::application::get();
                    application.unload(program);
                });

                engine.terminate();

                return 0;
            }

            void application::load(x::graphics::shader & o)
            {
                if(o.id() == 0)
                {
                    GLuint identity = glCreateShader(x::graphics::opengl::shader::type(o.category(), o.type()));
                    const char * source = o.code();
                    glShaderSource(identity, 1, &source, NULL);
                    glCompileShader(identity);
                    GLint result = GL_FALSE;
                    glGetShaderiv(identity, GL_COMPILE_STATUS, &result);
                    if(!result)
                    {
                        // TODO: UPDATE THIS CODE!
                        GLint InfoLogLength;

                        glGetShaderiv(identity, GL_INFO_LOG_LENGTH, &InfoLogLength);
                        if (InfoLogLength > 0)
                        {
                            char fragmentError[1000];
                            glGetShaderInfoLog(identity, InfoLogLength, NULL,
                            &fragmentError[0]);
                            printf("%s\n", fragmentError);
                        }

                        glDeleteShader(identity);
                        exceptional();
                    }
                    else
                    {
                        o.id(identity);
                    }
                }
                else
                {
                    exceptional();
                }
            }

            void application::load(x::graphics::program & o)
            {
                if(o.id() == 0)
                {
                    GLuint identity = glCreateProgram();
                    x::array<x::graphics::shader> & shaders = o.shaders();
                    for(x::uint64 i = 0; i < shaders.size(); i++)
                    {
                        load(shaders[i]);
                        glAttachShader(identity, shaders[i].id());
                    }
                    glLinkProgram(identity);
                    GLint result = GL_FALSE;
                    glGetProgramiv(identity, GL_LINK_STATUS, &result);
                    if(!result)
                    {
                        for(x::uint64 i = 0; i < shaders.size(); i++)
                        {
                            glDetachShader(identity, shaders[i].id());
                            unload(shaders[i]);
                        }
                        exceptional();
                    }
                    else
                    {
                        o.id(identity);
                        for(x::uint64 i = 0; i < shaders.size(); i++)
                        {
                            glDetachShader(identity, shaders[i].id());
                            unload(shaders[i]);
                        }
                    }
                    // x::map<x::string, x::uint32> & uniforms = o.uniforms();
                    o.uniforms.each([&o](const x::string & key, x::uint32 & value){
                        if(value == -1)
                        {
                            value = glGetUniformLocation(o.id(), key.str());
                            // x::console::out << "program uniform > " << o.name() << " " << o.id() << " " << key << " : " << value << x::endl;
                        }
                    });
                }
                else
                {
                    exceptional();
                }
            }

            void application::load(x::graphics::primitive & o)
            {
                o.vertices.serialize(o.buffer);

                load(o.vertices);
                load(o.buffer);
            }

            void application::load(x::graphics::buffer & o)
            {
                if(o.id() == 0)
                {
                    if(o.size() == 0)
                    {
                        exceptional();
                    }
                    GLuint identity = 0;
                    glGenBuffers(1, &identity);
                    glBindBuffer(x::graphics::opengl::buffer::target(o.target()), identity);
                    glBufferData(x::graphics::opengl::buffer::target(o.target()), o.size(), o.data(), x::graphics::opengl::buffer::usage(o.usage()));
                    o.id(identity);
                }
                else
                {
                    glBindBuffer(x::graphics::opengl::buffer::target(o.target()), o.id());
                }
            }

            void application::load(x::graphics::vertices & o)
            {
                if(o.id() == 0)
                {
                    GLuint identity = 0;
                    glGenVertexArrays(1, &identity);
                    o.id(identity);
                }
                glBindVertexArray(o.id());
            }

            void application::load(x::graphics::texture & o)
            {
                // x::console::out << o.name() << x::endl;
                if(o.id() == 0)
                {
                    if(o.format() == 0)
                    {
                        GLuint identity = 0;
                        glGenTextures(1, &identity);
                        glBindTexture(GL_TEXTURE_2D, identity);
                        const x::graphics::mipmap & mipmap = o.mipmaps[0];
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mipmap.width(), mipmap.height(), 0, GL_BGR, GL_UNSIGNED_BYTE, mipmap.data());
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	                    glGenerateMipmap(GL_TEXTURE_2D);
                        o.id(identity);
                    }
                    else
                    {
                        GLuint identity = 0;
                        glGenTextures(1, &identity);
                        glBindTexture(GL_TEXTURE_2D, identity);
                        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                        for(x::uint64 level = 0; level < o.mipmaps.size(); level++)
                        {
                            const x::graphics::mipmap & mipmap = o.mipmaps[level];
                            glCompressedTexImage2D(GL_TEXTURE_2D, level, x::graphics::opengl::image::format(o.format()), mipmap.width(), mipmap.height(), 0, mipmap.size(), mipmap.data());
                        }

                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                        glGenerateMipmap(GL_TEXTURE_2D);

                        o.id(identity);
                    }
                }
            }

            void application::unload(x::graphics::texture & o)
            {
                exceptional();
            }

            void application::unload(x::graphics::vertices & o)
            {
                if(o.id() != 0)
                {
                    GLuint identity = o.id();
                    glDeleteVertexArrays(1, &identity);
                    o.id(0);
                }
            }

            void application::unload(x::graphics::buffer & o)
            {
                if(o.id() != 0)
                {
                    GLuint identity = o.id();
                    glDeleteBuffers(1, &identity);
                    o.id(0);
                }
            }

            void application::unload(x::graphics::primitive & o)
            {
                exceptional();
            }

            void application::unload(x::graphics::program & o)
            {
                if(o.id() != 0)
                {
                    exceptional();
                }
            }

            void application::unload(x::graphics::shader & o)
            {
                if(o.id() != 0)
                {
                    glDeleteShader(o.id());
                    o.id(0);
                }
            }

            void application::bind(x::graphics::texture & o)
            {
                glActiveTexture(GL_TEXTURE0);   // OPTIMIZE THIS
                glBindTexture(GL_TEXTURE_2D, o.id());
            }

            void application::bind(x::graphics::vertices & o)
            {
                glBindVertexArray(o.id());
            }

            void application::bind(x::graphics::buffer & o)
            {
                glBindBuffer(x::graphics::opengl::buffer::target(o.target()), o.id());
            }

            void application::bind(x::uint32 index, x::uint32 size, x::graphics::buffer & buffer, x::uint32 stride, x::uint64 position)
            {
                glEnableVertexAttribArray(index);
                glBindBuffer(x::graphics::opengl::buffer::target(buffer.target()), buffer.id());
                glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (GLvoid *) position);
            }

            void application::bind(x::graphics::program & o, x::graphics::object & object)
            {
                glUseProgram(o.id());
                o.uniforms.each([&object](const x::string & name, const x::uint32 & id){
                    object.bind(name, id);
                });
            }

            void application::bind(x::uint32 id, const x::reality::vector & vector)
            {
                glUniform4fv(id, 1, vector.data());
            }

            void application::bind(x::uint32 id, const x::reality::matrix & matrix)
            {
                glUniformMatrix4fv(id, 1, GL_FALSE, matrix.data());
            }

            void application::bind(x::uint32 id, const x::reality::color & color)
            {
                glUniform4fv(id, 1, color.data());
            }

            void application::bind(x::uint32 id, x::real v)
            {
                glUniform1f(id, v);
            }

            void application::bind(x::uint32 id, x::int32 v)
            {
                glUniform1i(id, v);
            }

            void application::draw(const x::graphics::vertices & vertices, const x::array<x::uint32> & indices)
            {
                if(vertices.size() > 0  && indices.size() > 0)
                {
                    glDrawElements(x::graphics::opengl::draw::mode(vertices.mode(), vertices.type(), vertices.adjacency()), indices.size(), GL_UNSIGNED_INT, indices.data());
                }
                else if(vertices.size() > 0)
                {
                    glDrawArrays(x::graphics::opengl::draw::mode(vertices.mode(), vertices.type(), vertices.adjacency()), 0, vertices.size());
                }
                else
                {
                    exceptional();
                }
            }

            void application::draw(const x::graphics::vertices & vertices)
            {
                glDrawArrays(x::graphics::opengl::draw::mode(vertices.mode(), vertices.type(), vertices.adjacency()), 0, vertices.size());
            }
        }
    }
}
