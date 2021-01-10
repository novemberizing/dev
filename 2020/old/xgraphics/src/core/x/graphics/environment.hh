#ifndef   __X_GRAPHICS__ENVIRONMENT__HH__
#define   __X_GRAPHICS__ENVIRONMENT__HH__

#include <x/string.hh>
#include <x/directory.hh>

namespace x
{
    namespace graphics
    {
        class environment
        {
        protected:  x::string __root;
        public:     inline const x::string & root() const { return __root; }
        public:     inline void root(const x::string & v){ __root = v; }
        public:     inline void root(x::string && v){ __root = x::move(v); }
        public:     x::graphics::environment & operator=(const x::graphics::environment & o);
        public:     x::graphics::environment & operator=(x::graphics::environment && o) noexcept;
        public:     environment();
        public:     environment(const x::graphics::environment & o);
        public:     environment(x::graphics::environment && o) noexcept;
        public:     virtual ~environment();
        };
    }
}

#endif // __X_GRAPHICS__ENVIRONMENT__HH__
