#include "application.hh"

namespace x
{
    namespace graphics
    {
        application::application()
        :   __x(100),
            __y(100),
            __width(800),
            __height(600),
            __name("x graphics application"),
            __fps(1000.0f/60.0f),
            __surface(nullptr),
            shaders(),
            programs(),
            references(),
            textures(),
            __keyboard(nullptr),
            __special(nullptr),
            environment(),
            __timestamp(x::timestamp::current())
        {
        }

        application::~application()
        {
            references.each([](const x::string & name, x::var<x::graphics::reference *>::type & object){
                if(object)
                {
                    delete object;
                    object = nullptr;
                }
            });
        }

        void application::keyboard(unsigned char key, int x, int y)
        {
            if(__keyboard)
            {
                __keyboard(key, x, y);
            }
        }

        void application::special(int key, int x, int y)
        {
            if(__special)
            {
                __special(key, x, y);
            }
        }

        x::boolean application::mousemove(x::int32 x, x::int32 y)
        {
            // if(__surface)
            // {
            //     return __surface->mousemove(x, y);
            // }
            return false;
        }

        x::boolean application::mouse(x::int32 button, x::int32 state, x::int32 x, x::int32 y)
        {
            // if(__surface)
            // {
            //     return __surface->mouse(button, state, x, y);
            // }
            return false;
        }
    }
}
