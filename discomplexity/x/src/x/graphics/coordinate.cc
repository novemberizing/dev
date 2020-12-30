#include "coordinate.hh"

namespace x
{
    namespace graphics
    {
        coordinate::coordinate(const x::initializer<x::float32> & list)
        :   x::vector<x::float32>(2)
        {
            assertion(list.size() < 2);

            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end() && i < 2; ++it, ++i)
            {
                x::vector<x::float32>::operator[](i) = *it;
            }
        }

        coordinate::coordinate(x::float32 x, x::float32 y)
        :   x::vector<x::float32>(2)
        {
            x::vector<x::float32>::operator[](0) = x;
            x::vector<x::float32>::operator[](1) = y;
        }

        coordinate::coordinate()
        :   x::vector<x::float32>(2)
        {
        }

        coordinate::coordinate(const coordinate & o)
        :   x::vector<x::float32>(o)
        {
        }

        coordinate::coordinate(coordinate && o) noexcept
        :   x::vector<x::float32>(x::move(o))
        {
        }

        coordinate::~coordinate()
        {
        }

        coordinate & coordinate::operator=(const coordinate & o)
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator=(o);
            }
            return *this;
        }

        coordinate & coordinate::operator=(coordinate && o) noexcept
        {
            if(&o != this)
            {
                x::vector<x::float32>::operator=(x::move(o));
            }
            return *this;
        }

        coordinate & coordinate::operator=(const x::initializer<x::float32> & list)
        {
            assertion(list.size() < 2);

            x::uint64 i = 0;
            for(typename x::initializer<x::float32>::iterator it = list.begin(); it != list.end() && i < 2; ++it, ++i)
            {
                x::vector<x::float32>::operator[](i) = *it;
            }
            return *this;
        }

        void coordinate::set(x::float32 x, x::float32 y)
        {
            x::vector<x::float32>::operator[](0) = x;
            x::vector<x::float32>::operator[](1) = y;
        }
    }
}
