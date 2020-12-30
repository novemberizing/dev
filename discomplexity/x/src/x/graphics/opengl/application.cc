#include "application.hh"
#include "../opengl.hh"
#include "shaders/standard.hh"
#include "shaders/simple.hh"
#include "shaders/coordinate.system.hh"
#include "programs/standard.hh"
#include "programs/simple.hh"
#include "programs/coordinate.system.hh"
#include "../key.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            static GLenum getDrawMode(uint32 mode, uint32 type, uint32 adjacency)
            {
                switch(mode)
                {
                    case x::graphics::vertices::point:
                        if(type == x::graphics::vertices::none && adjacency == x::graphics::vertices::none)
                        {
                            return GL_POINTS;
                        }
                        exceptional();
                    case x::graphics::vertices::line:
                        switch(type)
                        {
                            case x::graphics::vertices::strip:
                                if(adjacency == x::graphics::vertices::adjacent)
                                {
                                    return GL_LINE_STRIP_ADJACENCY;
                                }
                                else if(adjacency == x::graphics::vertices::none)
                                {
                                    return GL_LINE_STRIP;
                                }
                                exceptional();
                            case x::graphics::vertices::loop:
                                if(adjacency == x::graphics::vertices::none)
                                {
                                    return GL_LINE_LOOP;
                                }
                                exceptional();
                            case x::graphics::vertices::none:
                                if(adjacency == x::graphics::vertices::adjacent)
                                {
                                    return GL_LINES_ADJACENCY;
                                }
                                else if(adjacency == x::graphics::vertices::none)
                                {
                                    return GL_LINES;
                                }
                                exceptional();
                            default:
                                exceptional();
                        }
                    case x::graphics::vertices::patch:
                        if(type == x::graphics::vertices::none && adjacency == x::graphics::vertices::none)
                        {
                            return GL_PATCHES;
                        }
                        exceptional();
                    case x::graphics::vertices::triangle:
                        switch(type)
                        {
                            case x::graphics::vertices::strip:
                                if(adjacency == x::graphics::vertices::adjacent)
                                {
                                    return GL_TRIANGLE_STRIP_ADJACENCY;
                                }
                                else if(adjacency == x::graphics::vertices::none)
                                {
                                    return GL_TRIANGLE_STRIP;
                                }
                                exceptional();
                            case x::graphics::vertices::fan:
                                if(adjacency == x::graphics::vertices::none)
                                {
                                    return GL_TRIANGLE_FAN;
                                }
                                exceptional();
                            case x::graphics::vertices::none:
                                if(adjacency == x::graphics::vertices::adjacent)
                                {
                                    return GL_TRIANGLES_ADJACENCY;
                                }
                                else if(adjacency == x::graphics::vertices::none)
                                {
                                    return GL_TRIANGLES;
                                }
                                exceptional();
                            default:
                                exceptional();
                        }
                        exceptional();
                    default:
                        exceptional();
                }
            }

            static uint32 getBufferTarget(uint32 target)
            {
                switch(target)
                {
                case x::graphics::buffer::array:                return GL_ARRAY_BUFFER;
                case x::graphics::buffer::atomic_counter:       return GL_ATOMIC_COUNTER_BUFFER;
                case x::graphics::buffer::copy_read:            return GL_COPY_READ_BUFFER;
                case x::graphics::buffer::copy_write:           return GL_COPY_WRITE_BUFFER;
                case x::graphics::buffer::dispatch_indirect:    return GL_DISPATCH_INDIRECT_BUFFER;
                case x::graphics::buffer::draw_indirect:        return GL_DRAW_INDIRECT_BUFFER;
                case x::graphics::buffer::element_array:        return GL_ELEMENT_ARRAY_BUFFER;
                case x::graphics::buffer::pixel_pack:           return GL_PIXEL_PACK_BUFFER;
                case x::graphics::buffer::pixel_unpack:         return GL_PIXEL_UNPACK_BUFFER;
                case x::graphics::buffer::query:                return GL_QUERY_BUFFER;
                case x::graphics::buffer::shader_storage:       return GL_SHADER_STORAGE_BUFFER;
                case x::graphics::buffer::texture:              return GL_TEXTURE_BUFFER;
                case x::graphics::buffer::transform_feedback:   return GL_TRANSFORM_FEEDBACK_BUFFER;
                case x::graphics::buffer::uniform:              return GL_UNIFORM_BUFFER;
                default:                                        exceptional();
                }
            }

            static uint32 getBufferUsage(uint32 usage)
            {
                uint32 type = ((usage & 0xFFFF0000U) >> 16U);
                uint32 mode = (usage & 0x0000FFFFU);
                switch(type)
                {
                    case x::graphics::buffer::stream:       switch(mode){
                                                                case x::graphics::buffer::draw:  return GL_STREAM_DRAW;
                                                                case x::graphics::buffer::read:  return GL_STREAM_READ;
                                                                case x::graphics::buffer::copy:  return GL_STREAM_COPY;
                                                                default:                         exceptional();
                                                            }
                    case x::graphics::buffer::statical:     switch(mode){
                                                                case x::graphics::buffer::draw:  return GL_STATIC_DRAW;
                                                                case x::graphics::buffer::read:  return GL_STATIC_READ;
                                                                case x::graphics::buffer::copy:  return GL_STATIC_COPY;
                                                                default:                         exceptional();
                                                            }
                    case x::graphics::buffer::dynamical:    switch(mode){
                                                                case x::graphics::buffer::draw:  return GL_DYNAMIC_DRAW;
                                                                case x::graphics::buffer::read:  return GL_DYNAMIC_READ;
                                                                case x::graphics::buffer::copy:  return GL_DYNAMIC_COPY;
                                                                default:                         exceptional();
                                                            }
                    default:                                                                     exceptional();
                }
            }

            static GLuint getShaderType(uint32 category, uint32 type)
            {
                switch(category)
                {
                    case x::graphics::shader::vertex: return GL_VERTEX_SHADER;
                    case x::graphics::shader::fragment: return GL_FRAGMENT_SHADER;
                    case x::graphics::shader::compute: return GL_COMPUTE_SHADER;
                    case x::graphics::shader::geometry: return GL_GEOMETRY_SHADER;
                    case x::graphics::shader::tessellation: {
                        if(type == x::graphics::shader::control)
                        {
                            return GL_TESS_CONTROL_SHADER;
                        }
                        else if(type == x::graphics::shader::evaluation)
                        {
                            return GL_TESS_EVALUATION_SHADER;
                        }
                        else
                        {
                            exceptional();
                        }
                    }
                    default: exceptional();
                }
            }

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
                // Graphics::Application & application = Application::get();
                // application.key(key, x, y);
            }

            static void special(int key, int x, int y)
            {
                // Graphics::Application & application = Application::get();
                // application.special(getKeyType(key), x, y);
            }

            x::graphics::application & application::init(int argc, char ** argv)
            {
                if(__singleton == nullptr)
                {
                    static x::graphics::opengl::application o;
                    // TODO: APPLICATION INIT
                    __singleton = &o;

                    o.add(x::graphics::opengl::shaders::simple::vertex);
                    o.add(x::graphics::opengl::shaders::simple::fragment);
                    o.add(x::graphics::opengl::shaders::coordinate::system::vertex);
                    o.add(x::graphics::opengl::shaders::coordinate::system::fragment);
                    o.add(x::graphics::opengl::shaders::standard::vertex);
                    o.add(x::graphics::opengl::shaders::standard::fragment);

                    o.add(x::graphics::opengl::programs::simple::program);
                    o.add(x::graphics::opengl::programs::standard::program);
                    o.add(x::graphics::opengl::programs::coordinate::system::program);

                    glutInit(&argc, argv);
                }
                return *__singleton;
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

            void application::render()
            {
                render(__surface);
            }

            void application::render(x::graphics::surface & surface)
            {
                const x::graphics::color & background = surface.background();
                x::map<x::string, x::graphics::reference> & objects = surface.objects();

                glClearColor(background[0], background[1], background[2], background[3]);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                objects.each([](const x::string & key, x::graphics::reference & reference){
                    reference.render();
                });

                glutSwapBuffers();

                GLenum err;
                while((err = glGetError()) != GL_NO_ERROR)
                {
                    x::console::out << "gl error => " << err << x::endl;
                }
            }

            void application::render(x::graphics::primitive & o)
            {
                exceptional();
                // x::console::out<< o.name() << " render 2" << x::endl;
                // bind(o.program());
                // bind(o.program(), "mvp", __matrix);
                // bind(o.program(), "cameraPos", camera.position());
                // bind(o.program(), "lightColor", light.color());
                // bind(o.program(), "lightPos", light.position());
                // bind(o.program(), "ambientStrength", light.ambient());
            }

            void application::idle()
            {
                __engine.cycle();
            }

            void application::load(x::graphics::shader & o)
            {
                if(o.id() == 0)
                {
                    GLuint identity = glCreateShader(getShaderType(o.category(), o.type()));
                    const char * source = o.code();
                    glShaderSource(identity, 1, &source, NULL);
                    glCompileShader(identity);
                    GLint result = GL_FALSE;
                    glGetShaderiv(identity, GL_COMPILE_STATUS, &result);
                    if(!result)
                    {
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

            void application::unload(x::graphics::shader & o)
            {
                if(o.id() != 0)
                {
                    glDeleteShader(o.id());
                    o.id(0);
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
                    x::map<x::string, x::uint32> & uniforms = o.uniforms();
                    uniforms.each([&o](const x::string & key, x::uint32 & value){
                        if(value == -1)
                        {
                            value = glGetUniformLocation(o.id(), key.str());
                        }
                    });
                }
                else
                {
                    exceptional();
                }
            }

            void application::unload(x::graphics::program & o)
            {
                if(o.id() != 0)
                {
                    exceptional();
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

            void application::unload(x::graphics::vertices & o)
            {
                if(o.id() != 0)
                {
                    GLuint identity = o.id();
                    glDeleteVertexArrays(1, &identity);
                    o.id(0);
                }
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
                    glBindBuffer(getBufferTarget(o.target()), identity);
                    glBufferData(getBufferTarget(o.target()), o.size(), o.data(), getBufferUsage(o.usage()));
                    o.id(identity);
                }
                else
                {
                    glBindBuffer(getBufferTarget(o.target()), o.id());
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

            void application::load(x::graphics::primitive & o)
            {
                x::graphics::vertices & vertices = o.vertices();

                vertices.serialize(o.buffer());

                load(vertices);
                load(o.buffer());
            }

            void application::unload(x::graphics::primitive & o)
            {

            }

            void application::bind(x::graphics::program & o)
            {
                glUseProgram(o.id());
            }

            void application::bind(x::graphics::program & o, const x::string & name, const x::graphics::matrix & matrix)
            {
                try
                {
                    x::map<x::string, x::uint32> & uniforms = o.uniforms();
                    glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, matrix.data());
                }
                catch(const x::exception & e)
                {
                    // x::console::out << "not found" << x::endl;
                }
            }

            void application::bind(x::graphics::program & o, const x::string & name, const x::graphics::vector & vector)
            {
                try
                {
                    x::map<x::string, x::uint32> & uniforms = o.uniforms();
                    glUniform4fv(uniforms[name], 1, vector.data());
                }
                catch(const x::exception & e)
                {
                    // x::console::out << "not found" << x::endl;
                }
            }

            void application::bind(x::graphics::program & o, const x::string & name, const x::graphics::color & color)
            {
                try
                {
                    x::map<x::string, x::uint32> & uniforms = o.uniforms();
                    glUniform4fv(uniforms[name], 1, color.data());
                }
                catch(const x::exception & e)
                {
                    // x::console::out << "not found" << x::endl;
                }
            }

            void application::bind(x::graphics::program & o, const x::string & name, x::float32 v)
            {
                try
                {
                    x::map<x::string, x::uint32> & uniforms = o.uniforms();
                    glUniform1f(uniforms[name], v);
                }
                catch(const x::exception & e)
                {
                    x::console::out << "not found" << x::endl;
                }
            }

            void application::bind(x::graphics::vertices & o)
            {
                // x::console::out << "bind vertex array => " << o.id() << x::endl;
                glBindVertexArray(o.id());
            }

            void application::bind(x::graphics::buffer & o)
            {
                // x::console::out << "bind buffer => " << o.id() << x::endl;
                glBindBuffer(getBufferTarget(o.target()), o.id());
            }

            void application::bind(x::uint32 index, x::graphics::buffer & buffer, x::uint32 stride, x::uint64 position)
            {
                glEnableVertexAttribArray(index);
                // glBindBuffer(getBufferTarget(buffer.target()), buffer.id());
                glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid *) position);
            }

            void application::unbind(x::uint32 index)
            {
                  glDisableVertexAttribArray(index);
            }

            void application::draw(const x::graphics::vertices & vertices, const x::array<x::uint32> & indices)
            {
                if(vertices.size() > 0  && indices.size() > 0)
                {
                    glDrawElements(getDrawMode(vertices.mode(), vertices.type(), vertices.adjacency()), indices.size(), GL_UNSIGNED_INT, indices.data());
                }
                else if(vertices.size() > 0)
                {
                    glDrawArrays(getDrawMode(vertices.mode(), vertices.type(), vertices.adjacency()), 0, vertices.size());
                }
                else
                {
                    // [[1.086396,-0.993682,-0.686132,-0.685994],[0.000000,2.070171,-0.514599,-0.514496],[-1.448528,-0.745262,-0.514599,-0.514496],[0.000000,-0.000001,5.632099,5.830953]]}
                    // [[1.086396,-0.993682,-0.686132,-0.685994],[0.000000,2.070171,-0.514599,-0.514496],[-1.448528,-0.745262,-0.514599,-0.514496],[0.000000, 0.000000,5.632099,5.830953]]
                    exceptional();
                }
            }

            x::int32 application::run()
            {
                glutInitContextVersion(__major, __minor);
                glutInitDisplayMode(__mode);
                glutInitWindowSize(__width, __height);
                glutInitWindowPosition(__x, __y);
                glutCreateWindow(__name.str());

                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glewInit();

                __engine.init();

                __programs.each([](const x::string & name, x::graphics::program & program){
                    x::graphics::application & application = x::graphics::application::get();
                    application.load(program);
                });

                __objects.each([](const x::string name, x::graphics::object * object){
                    if(object)
                    {
                        object->load();
                    }
                });

                glutDisplayFunc(x::graphics::opengl::render);
                glutIdleFunc(x::graphics::opengl::idle);
                glutKeyboardFunc(x::graphics::opengl::keyboard);
                glutSpecialFunc(x::graphics::opengl::special);

                // REMOVE THIS CODE
                // exec("object sample enable Weapon_BigGun_Latitude_mesh");
                // exec("object sample enable Weapon_BigGun_Muzzle_mesh");
                // exec("object sample enable Weapon_BigGun_Position_mesh");
                // exec("object sample enable Weapon_FrontGun2Slave1_Latitude_mesh");
                // exec("object sample enable Weapon_FrontGun2Slave2_Position_mesh");
                // exec("object sample enable Weapon_FrontGun2Slave2_Position_mesh");
                // exec("object sample enable Weapon_FrontGun3Slave_Position_mesh");
                // exec("object sample enable Weapon_FrontGun2Slave_Position_mesh");
                // exec("object sample enable Weapon_FrontGun2_Latitude_mesh");
                // exec("object sample enable Weapon_FrontGun3Slave1_Latitude_mesh");
                // exec("object sample enable Weapon_FrontGun3Slave2_Position_mesh");
                // exec("object sample enable Weapon_FrontGun3Slave_Position_mesh");
                // exec("object sample enable Weapon_FrontGun3_Latitude_mesh");
                // exec("object sample enable Weapon_FrontGun4_Position_mesh");
                // exec("object sample enable Weapon_FrontGun5_Position_mesh");
                // exec("object sample enable Weapon_FrontGun6_Position_mesh");
                // exec("object sample enable Weapon_FrontGun7_Position_mesh");
                // exec("object sample enable Weapon_FrontGun_Latitude_mesh");
                // exec("object sample disable Weapon_TurretTop1_Latitude_mesh");
                // exec("object sample disable Weapon_TurretTop1_Position_mesh");
                // exec("object sample disable Weapon_TurretTop2_Latitude_mesh");
                // exec("object sample disable Weapon_TurretTop2_Position_mesh");
                // exec("object sample enable Root_goblins");
                // exec("object sample enable Weapon_BigGun_Latitude_goblins");
                // exec("object sample enable Weapon_BigGun_Muzzle_goblins");
                // exec("object sample enable Weapon_BigGun_Position_goblins");
                // exec("object sample enable Weapon_FrontGun2Slave1_Latitude_goblins");
                // exec("object sample enable Weapon_FrontGun3Slave1_Latitude_goblins");
                // exec("object sample enable Weapon_FrontGun4_Position_goblins");
                // exec("object sample enable Weapon_FrontGun5_Position_goblins");
                // exec("object sample enable Weapon_FrontGun6_Position_goblins");
                // exec("object sample enable Weapon_FrontGun7_Position_goblins");
                // exec("object sample enable Weapon_FrontGun_Latitude_goblins");
                // exec("object sample enable Weapon_TurretTop1_Latitude_goblins");
                // exec("object sample enable Weapon_TurretTop1_Position_goblins");
                // exec("object sample enable Weapon_TurretTop2_Latitude_goblins");
                // exec("object sample enable Weapon_TurretTop2_Position_goblins");
                // REMOVE THIS CODE

                glutMainLoop();

                __objects.each([](const x::string name, x::graphics::object * object){
                    if(object)
                    {
                        object->unload();
                    }
                });

                __programs.each([](const x::string & name, x::graphics::program & program){
                    x::graphics::application & application = x::graphics::application::get();
                    application.unload(program);
                });

                __engine.term();

                return 0;
            }
        }
    }
}
