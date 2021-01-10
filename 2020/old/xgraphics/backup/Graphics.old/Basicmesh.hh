#ifndef   __HOMEWORLD2__BASICMESH__HH__
#define   __HOMEWORLD2__BASICMESH__HH__

#include <Homeworld2/Graphics/Description.hh>
#include <Homeworld2/Graphics/Box.hh>
#include <Homeworld2/Graphics/Sphere.hh>
#include <Homeworld2/Graphics/Triangle.hh>
#include <Homeworld2/Graphics/Subdivision.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Basicmesh
        {
            public:     void add(Description && o)
                        {
                        }
            public:     void add(Box && o)
                        {
                        }
            public:     void add(Sphere && o)
                        {
                        }
            public:     void add(Triangle && o)
                        {
                        }
            public:     void add(Subdivision && o)
                        {
                        }
            public:     void add(const Description & o)
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
            public:     void add(const Subdivision & o)
                        {
                        }
        };
    }
}

#endif // __HOMEWORLD2__BASICMESH__HH__
