#ifndef   __X_GRAPHICS__COLOR__HH__
#define   __X_GRAPHICS__COLOR__HH__

#include <x/graphics/type.hh>
#include <x/console.hh>
#include <x/graphics/util.hh>

namespace x
{
    namespace graphics
    {
        class color : public x::vector<x::float32>
        {
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     inline x::float32 r() const { return x::vector<x::float32>::operator[](0); }
        public:     inline x::float32 g() const { return x::vector<x::float32>::operator[](1); }
        public:     inline x::float32 b() const { return x::vector<x::float32>::operator[](2); }
        public:     inline x::float32 a() const { return x::vector<x::float32>::operator[](3); }
        public:     inline x::float32 red() const { return x::vector<x::float32>::operator[](0); }
        public:     inline x::float32 green() const { return x::vector<x::float32>::operator[](1); }
        public:     inline x::float32 blue() const { return x::vector<x::float32>::operator[](2); }
        public:     inline x::float32 alpha() const { return x::vector<x::float32>::operator[](3); }
        public:     inline void r(x::float32 v){ x::vector<x::float32>::operator[](0) = v; }
        public:     inline void g(x::float32 v){ x::vector<x::float32>::operator[](1) = v; }
        public:     inline void b(x::float32 v){ x::vector<x::float32>::operator[](2) = v; }
        public:     inline void a(x::float32 v){ x::vector<x::float32>::operator[](3) = v; }
        public:     inline void red(x::float32 v){ x::vector<x::float32>::operator[](0) = v; }
        public:     inline void green(x::float32 v){ x::vector<x::float32>::operator[](1) = v; }
        public:     inline void blue(x::float32 v){ x::vector<x::float32>::operator[](2) = v; }
        public:     inline void alpha(x::float32 v){ x::vector<x::float32>::operator[](3) = v; }
        public:     virtual void set(x::float32 r, x::float32 g, x::float32 b);
        public:     virtual void set(x::float32 r, x::float32 g, x::float32 b, x::float32 a);
        public:     virtual void set(const x::initializer<x::float32> & list);
        public:     color & operator=(const x::initializer<x::float32> & list);
        public:     color & operator=(const color & o);
        public:     color & operator=(color && o) noexcept;
        public:     color(const x::initializer<x::float32> & list);
        public:     color(x::float32 r, x::float32 g, x::float32 b);
        public:     color(x::float32 r, x::float32 g, x::float32 b, x::float32 a);
        public:     color();
        public:     color(const color & o);
        public:     color(color && o) noexcept;
        public:     ~color() override;
        };
    }
}

#endif // __X_GRAPHICS__COLOR__HH__
