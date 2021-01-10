#ifndef   __HOMEWORLD2__COLLISION__HH__
#define   __HOMEWORLD2__COLLISION__HH__

#include <Homeworld2/Box.hh>
#include <Homeworld2/Sphere.hh>
#include <Homeworld2/Triangles.hh>

namespace Homeworld2
{
    class Collision
    {
        public:     void add(Box && o)
                    {
                    }
        public:     void add(Sphere && o)
                    {
                    }
        public:     void add(Triangles && o)
                    {
                    }
        public:     void add(const Box & o)
                    {
                    }
        public:     void add(const Sphere & o)
                    {
                    }
        public:     void add(const Triangles & o)
                    {
                    }
    };
}

#endif // __HOMEWORLD2__COLLISION__HH__
