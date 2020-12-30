#ifndef   __X_GRAPHICS__OPENGL__HH__
#define   __X_GRAPHICS__OPENGL__HH__

#include <x/core.hh>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <x/mouse.hh>

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            extern void debug();
            extern void debug(const char * file, x::uint32 line);

            namespace mouse
            {
                extern x::uint32 button(int v);
                extern x::uint32 state(int v);
            }

            namespace error
            {
                extern const char * title(GLenum v);
                extern const char * string(GLenum v);
            }

            namespace draw
            {
                GLenum mode(x::uint32 mode, x::uint32 type, x::uint32 adjacency);
            }

            namespace shader
            {
                extern GLuint type(x::uint32 category, x::uint32 type);
            }

            namespace buffer
            {
                extern GLuint target(x::uint32 target);
                extern GLuint usage(x::uint32 usage);
            }

            namespace image
            {
                extern GLenum format(x::uint32 v);
            }

            namespace key
            {
                extern x::uint32 get(GLenum key);
            }
        }
    }
}

#endif // __X_GRAPHICS__OPENGL__HH__
