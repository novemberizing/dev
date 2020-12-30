#include "Map.hh"

namespace Pioneer
{
    Map::Map()
    {
    }

    Map::Map(const Pioneer::Map & o)
    {
    }

    Map::Map(Pioneer::Map && o) noexcept
    {
    }

    Map::~Map()
    {
    }

    Pioneer::Map & Map::operator=(const Pioneer::Map & o)
    {
        return *this;
    }

    Pioneer::Map & Map::operator=(Pioneer::Map && o) noexcept
    {
        return *this;
    }    
}
