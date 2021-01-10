#ifndef   __X_GRAPHICS__OPENGL__HH__
#define   __X_GRAPHICS__OPENGL__HH__

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace x
{
    namespace graphics
    {
        inline x::output::stream & operator<<(x::output::stream & os, const glm::vec3 & o)
        {
            os << "[";
            for(x::uint64 j = 0; j < 3; j++)
            {
                os << o[j];
                if(j + 1 != 3)
                {
                    os << ",";
                }
            }
            os << "]";
            return os;
        }

        inline x::output::stream & operator<<(x::output::stream & os, const glm::mat4 & o)
        {
            os << "[";
            for(x::uint64 i = 0; i < 4; i++)
            {
                os << "[";
                for(x::uint64 j = 0; j < 4; j++)
                {
                    os << o[i][j];
                    if(j + 1 != 4)
                    {
                        os << ",";
                    }
                }
                os << "]";
                if(i + 1 != 4)
                {
                    os << ",";
                }
            }
            os << "]";
            return os;
        }
    }
}

#endif // __X_GRAPHICS__OPENGL__HH__
