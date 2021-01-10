#include "Resource.hh"

namespace Pioneer
{
    Resource::Resource()
    {
    }

    Resource::Resource(const Resource & o)
    {
    }

    Resource::Resource(Resource && o) noexcept
    {
    }

    Resource::~Resource()
    {
    }

    Resource & Resource::operator=(const Resource & o)
    {
        return *this;
    }

    Resource & Resource::operator=(Resource && o) noexcept
    {
        return *this;
    }
}
