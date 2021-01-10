#include "coordinate.hh"

namespace x
{
    namespace reality
    {
        coordinate::coordinate(const x::initializer<x::real> & list)
        :   x::vector<x::real>(2)
        {
            assertion(list.size() < 2);

            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 2; ++it, ++i)
            {
                x::vector<x::real>::operator[](i) = *it;
            }
        }

        coordinate::coordinate(x::real x, x::real y)
        :   x::vector<x::real>(2)
        {
            x::vector<x::real>::operator[](0) = x;
            x::vector<x::real>::operator[](1) = y;
        }

        coordinate::coordinate()
        :   x::vector<x::real>(2)
        {
        }

        coordinate::coordinate(const x::reality::coordinate & o)
        :   x::vector<x::real>(o)
        {
        }

        coordinate::coordinate(x::reality::coordinate && o) noexcept
        :   x::vector<x::real>(x::move(o))
        {
        }

        coordinate::~coordinate()
        {
        }

        x::reality::coordinate & coordinate::operator=(const x::reality::coordinate & o)
        {
            if(&o != this)
            {
                x::vector<x::real>::operator=(o);
            }
            return *this;
        }

        x::reality::coordinate & coordinate::operator=(x::reality::coordinate && o) noexcept
        {
            if(&o != this)
            {
                x::vector<x::real>::operator=(x::move(o));
            }
            return *this;
        }

        x::reality::coordinate & coordinate::operator=(const x::initializer<x::real> & list)
        {
            assertion(list.size() < 2);

            x::uint64 i = 0;
            for(typename x::initializer<x::real>::iterator it = list.begin(); it != list.end() && i < 2; ++it, ++i)
            {
                x::vector<x::real>::operator[](i) = *it;
            }
            return *this;
        }

        void coordinate::set(x::real x, x::real y)
        {
            x::vector<x::real>::operator[](0) = x;
            x::vector<x::real>::operator[](1) = y;
        }
    }
}
