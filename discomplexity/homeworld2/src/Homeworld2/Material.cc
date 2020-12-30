#include "Material.hh"

namespace Homeworld2
{
    Material::Material() :
        __name(),
        __shader(),
        __parameters()
    {
    }

    Material::Material(const Material & o) :
        __name(o.__name),
        __shader(o.__shader),
        __parameters(o.__parameters)
    {
    }

    Material::Material(Material && o) noexcept :
        __name(x::move(o.__name)),
        __shader(x::move(o.__shader)),
        __parameters(x::move(o.__parameters))
    {
    }

    Material::~Material()
    {
        __parameters.clear([](x::pair<x::string, x::variable *> && o){
            if(o.second())
            {
                delete o.second();
            }
        });
    }

    Material & Material::operator=(const Material & o)
    {
        if(&o != this)
        {
            __name = o.__name;
            __shader = o.__shader;
            __parameters = o.__parameters;
        }
        return *this;
    }

    Material & Material::operator=(Material && o) noexcept
    {
        if(&o != this)
        {
            __name = x::move(o.__name);
            __shader = x::move(o.__shader);
            __parameters = x::move(o.__parameters);
        }
        return *this;
    }
}
