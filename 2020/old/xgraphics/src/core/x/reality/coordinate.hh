#ifndef   __X_REALITY__COORDINATE__HH__
#define   __X_REALITY__COORDINATE__HH__

#include <x/vector.hh>

namespace x
{
    namespace reality
    {
        class coordinate : public x::vector<x::real>
        {
        public:     inline x::real x() const { return x::vector<x::real>::operator[](0); }
        public:     inline x::real y() const { return x::vector<x::real>::operator[](1); }
        public:     inline void x(x::real v){ x::vector<x::real>::operator[](0) = v; }
        public:     inline void y(x::real v){ x::vector<x::real>::operator[](0) = v; }
        public:     virtual void set(x::real x, x::real y);
        public:     x::reality::coordinate & operator=(const x::initializer<x::real> & list);
        public:     x::reality::coordinate & operator=(const x::reality::coordinate & o);
        public:     x::reality::coordinate & operator=(x::reality::coordinate && o) noexcept;
        public:     coordinate(const x::initializer<x::real> & list);
        public:     coordinate(x::real x, x::real y);
        public:     coordinate();
        public:     coordinate(const x::reality::coordinate & o);
        public:     coordinate(x::reality::coordinate && o) noexcept;
        public:     ~coordinate() override;
        public:     friend x::reality::coordinate operator*(const x::reality::coordinate & x, x::real y)
                    {
                        x::reality::coordinate result = x;
                        result *= y;
                        return result;
                    }
        public:     friend x::reality::coordinate operator*(x::real x, const x::reality::coordinate & y)
                    {
                        x::reality::coordinate result = y;
                        result *= x;
                        return result;
                    }
        };
    }
}

#endif // __X_REALITY__COORDINATE__HH__
