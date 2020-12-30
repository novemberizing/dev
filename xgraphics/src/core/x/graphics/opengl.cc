#include "opengl.hh"
#include "shader.hh"
#include "buffer.hh"
#include "vertices.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            void debug()
            {
                GLenum err = 0;
                while((err = glGetError()) != GL_NO_ERROR)
                {
                    x::console::out << "opengl error => " << err
                                    << "[" << x::graphics::opengl::error::title(err) << "] "
                                    << "" << x::graphics::opengl::error::string(err)
                                    << x::endl;
                }
            }

            void debug(const char * file, x::uint32 line)
            {
                GLenum err = 0;
                while((err = glGetError()) != GL_NO_ERROR)
                {
                    x::console::out << "opengl error [" << file << ":" << line << "] => " << err
                                    << "[" << x::graphics::opengl::error::title(err) << "] "
                                    << "" << x::graphics::opengl::error::string(err)
                                    << x::endl;
                }
            }

            namespace mouse
            {
                x::uint32 button(int v)
                {
                    switch(v)
                    {
                        case GLUT_LEFT_BUTTON: return x::mouse::left;
                        case GLUT_RIGHT_BUTTON: return x::mouse::right;
                        case GLUT_MIDDLE_BUTTON: return x::mouse::middle;
                        case 3: return x::mouse::scroll::up;
                        case 4: return x::mouse::scroll::down;
                        default: exceptional();
                    }
                }

                x::uint32 state(int v)
                {
                    switch(v)
                    {
                        case GLUT_DOWN: return x::mouse::down;
                        case GLUT_UP:   return x::mouse::up;
                        default: exceptional();
                    }
                }
            }

            namespace error
            {
                const char * title(GLenum v)
                {
                    switch(v)
                    {
                        case GL_NO_ERROR:                       return "no error";
                        case GL_INVALID_ENUM:                   return "invalid enum";
                        case GL_INVALID_VALUE:                  return "invalid value";
                        case GL_INVALID_OPERATION:              return "invalid operation";
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  return "invalid framebuffer operation";
                        case GL_OUT_OF_MEMORY:                  return "out of memory";
                        case GL_STACK_UNDERFLOW:                return "stack underflow";
                        case GL_STACK_OVERFLOW:                 return "stack overflow";
                        default:                                exceptional();
                    }
                }

                const char * string(GLenum v)
                {
                    switch(v)
                    {
                        case GL_NO_ERROR:                       return "No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
                        case GL_INVALID_ENUM:                   return "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
                        case GL_INVALID_VALUE:                  return "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
                        case GL_INVALID_OPERATION:              return "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  return "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
                        case GL_OUT_OF_MEMORY:                  return "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
                        case GL_STACK_UNDERFLOW:                return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
                        case GL_STACK_OVERFLOW:                 return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
                        default:                                exceptional();
                    }



                }
            }

            namespace image
            {
                GLenum format(x::uint32 v)
                {
                    switch(v)
                    {
                        case 0x44585435U: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                        case 0x35545844U: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                        case 0x44585433U: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                        case 0x33545844U: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;

                        default:          exceptional();
                    }
                }
            }

            namespace draw
            {
                GLenum mode(x::uint32 mode, x::uint32 type, x::uint32 adjacency)
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
            }

            namespace key
            {
                x::uint32 get(GLenum key)
                {
                    switch(key)
                    {
                        case GLUT_KEY_LEFT: return x::keyboard::left;
                        case GLUT_KEY_RIGHT: return x::keyboard::right;
                        case GLUT_KEY_UP: return x::keyboard::up;
                        case GLUT_KEY_DOWN: return x::keyboard::down;
                        case GLUT_KEY_PAGE_UP: return x::keyboard::top;
                        case GLUT_KEY_PAGE_DOWN: return x::keyboard::bottom;
                        default: return x::keyboard::unknown;
                    }
                }
            }

            namespace shader
            {
                GLuint type(x::uint32 category, x::uint32 type)
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
            }

            namespace buffer
            {
                GLuint target(x::uint32 target)
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

                GLuint usage(x::uint32 usage)
                {
                    x::uint32 type = ((usage & 0xFFFF0000U) >> 16U);
                    x::uint32 mode = (usage & 0x0000FFFFU);
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
            }
        }
    }
}
