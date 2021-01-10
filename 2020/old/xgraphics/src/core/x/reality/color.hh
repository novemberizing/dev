#ifndef   __X_REALITY__COLOR__HH__
#define   __X_REALITY__COLOR__HH__

#include <x/vector.hh>
#include <x/string.hh>
#include <x/real32.hh>
#include <x/console.hh>

namespace x
{
    namespace reality
    {
        class color : protected x::vector<x::real>
        {
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     inline const x::real * data() const { return &x::vector<x::real>::data()[__offset]; }
        public:     inline x::real r() const { return x::vector<x::real>::operator[](0); }
        public:     inline x::real g() const { return x::vector<x::real>::operator[](1); }
        public:     inline x::real b() const { return x::vector<x::real>::operator[](2); }
        public:     inline x::real a() const { return x::vector<x::real>::operator[](3); }
        public:     inline x::real red() const { return x::vector<x::real>::operator[](0); }
        public:     inline x::real green() const { return x::vector<x::real>::operator[](1); }
        public:     inline x::real blue() const { return x::vector<x::real>::operator[](2); }
        public:     inline x::real alpha() const { return x::vector<x::real>::operator[](3); }
        public:     inline void r(x::real v){ x::vector<x::real>::operator[](0) = v; }
        public:     inline void g(x::real v){ x::vector<x::real>::operator[](1) = v; }
        public:     inline void b(x::real v){ x::vector<x::real>::operator[](2) = v; }
        public:     inline void a(x::real v){ x::vector<x::real>::operator[](3) = v; }
        public:     inline void red(x::real v){ x::vector<x::real>::operator[](0) = v; }
        public:     inline void green(x::real v){ x::vector<x::real>::operator[](1) = v; }
        public:     inline void blue(x::real v){ x::vector<x::real>::operator[](2) = v; }
        public:     inline void alpha(x::real v){ x::vector<x::real>::operator[](3) = v; }
        public:     virtual void set(x::real r, x::real g, x::real b);
        public:     virtual void set(x::real r, x::real g, x::real b, x::real a);
        public:     virtual void set(const x::initializer<x::real> & list);
        public:     inline const x::real & operator[](x::uint64 i) const { return x::vector<x::real>::operator[](i); }
        public:     inline x::real & operator[](x::uint64 i) { return x::vector<x::real>::operator[](i); }
        public:     x::reality::color & operator=(const x::initializer<x::real> & list);
        public:     x::reality::color & operator=(const x::reality::color & o);
        public:     x::reality::color & operator=(x::reality::color && o) noexcept;
        public:     color(const x::initializer<x::real> & list);
        public:     color(x::real r, x::real g, x::real b);
        public:     color(x::real r, x::real g, x::real b, x::real a);
        public:     color();
        public:     color(const x::reality::color & o);
        public:     color(x::reality::color && o) noexcept;
        public:     ~color() override;
        public:     friend x::output::stream & operator<<(x::output::stream & os, const x::reality::color & o)
                    {
                        os << "["
                           << o.red() << ","
                           << o.green() << ","
                           << o.blue() << ","
                           << o.alpha()
                           << "]";
                        return os;
                    }
        };
    }
}

#endif // __X_REALITY__COLOR__HH__
