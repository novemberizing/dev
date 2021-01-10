#ifndef   __HOMEWORLD2_PHYSICS__REFERENCE_FILE__HH__
#define   __HOMEWORLD2_PHYSICS__REFERENCE_FILE__HH__

#include <Homeworld2/Physics/Reference.hh>

#include <x/file.hh>
#include <x/json.hh>

namespace Homeworld2
{
    namespace Physics
    {
        class ReferenceFile
        {
        public:     static Homeworld2::Physics::Reference * load(const x::file & f, const x::string & name);
        };
    }
}

#endif // __HOMEWORLD2_PHYSICS__REFERENCE_FILE__HH__
