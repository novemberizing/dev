#include "Material.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Material::Material() :
            __name(),
            __shader(),
            __diffuse(0),
            __glow(0)
        {
        }

        Material::Material(const Material & o) :
            __name(o.__name),
            __shader(o.__shader),
            __diffuse(o.__diffuse),
            __glow(o.__glow)
        {
        }

        Material::Material(Material && o) noexcept :
            __name(x::move(o.__name)),
            __shader(x::move(o.__shader)),
            __diffuse(o.__diffuse),
            __glow(o.__glow)
        {
            o.__diffuse = 0;
            o.__glow = 0;
        }

        Material::~Material()
        {
            __diffuse = 0;
            __glow = 0;
        }

        Material & Material::operator=(const Material & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __shader = o.__shader;
                __diffuse = o.__diffuse;
                __glow = o.__glow;
            }
            return *this;
        }

        Material & Material::operator=(Material && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __shader = x::move(o.__shader);
                __diffuse = o.__diffuse;
                __glow = o.__glow;

                o.__diffuse = 0;
                o.__glow = 0;
            }
            return *this;
        }
    }
}
