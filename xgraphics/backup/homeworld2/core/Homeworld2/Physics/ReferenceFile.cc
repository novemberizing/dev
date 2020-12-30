#include "ReferenceFile.hh"

namespace Homeworld2
{
    namespace Physics
    {
        Homeworld2::Physics::Reference * ReferenceFile::load(const x::file & f, const x::string & name)
        {
            x::json::object * object = x::json::object::from(f);

            if(object)
            {
                Homeworld2::Physics::Reference * reference = new Homeworld2::Physics::Reference(name);

                reference->weight(x::json::value::as::number(object->get("mass")));
                reference->energy(x::json::value::as::number(object->get("energy")));

                delete object;

                return reference;
            }
            
            return nullptr;
        }
    }
}
