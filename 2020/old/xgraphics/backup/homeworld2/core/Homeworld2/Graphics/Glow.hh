#ifndef   __HOMEWORLD2_GRAPHICS__GLOW__HH__
#define   __HOMEWORLD2_GRAPHICS__GLOW__HH__

#include <Homeworld2/Graphics/Information.hh>
#include <Homeworld2/Graphics/Singlemesh.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Glow
        {
        public:     void add(Singlemesh && o){}
        public:     void add(const Singlemesh & o){}
        public:     void add(Information && o){}
        public:     void add(const Information & o){}
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__GLOW__HH__
