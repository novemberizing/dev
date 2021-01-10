#ifndef   __HOMEWORLD2_GRAPHICS__COLLISION__HH__
#define   __HOMEWORLD2_GRAPHICS__COLLISION__HH__

#include <Homeworld2/Graphics/Box.hh>
#include <Homeworld2/Graphics/Sphere.hh>
#include <Homeworld2/Graphics/Triangle.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Collision
        {
            public:     void add(Box && o)
                        {
                        }
            public:     void add(Sphere && o)
                        {
                        }
            public:     void add(Triangle && o)
                        {
                        }
            public:     void add(const Box & o)
                        {
                        }
            public:     void add(const Sphere & o)
                        {
                        }
            public:     void add(const Triangle & o)
                        {
                        }
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__COLLISION__HH__
