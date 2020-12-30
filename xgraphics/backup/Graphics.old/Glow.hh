#ifndef   __HOMEWORLD2_GRAPHICS__ENGINEGLOW__HH__
#define   __HOMEWORLD2_GRAPHICS__ENGINEGLOW__HH__

#include <Homeworld2/Graphics/Information.hh>
#include <Homeworld2/Graphics/Singlemesh.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Engineglow
        {
        public:     void add(Singlemesh && o){}
        public:     void add(const Singlemesh & o){}
        public:     void add(Information && o){}
        public:     void add(const Information & o){}
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__ENGINEGLOW__HH__
