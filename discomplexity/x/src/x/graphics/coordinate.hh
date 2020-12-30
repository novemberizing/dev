#ifndef   __X_GRAPHICS__COORDINATE__HH__
#define   __X_GRAPHICS__COORDINATE__HH__

#include <x/graphics/type.hh>

namespace x
{
    namespace graphics
    {
        class coordinate : public x::vector<x::float32>
        {
        public:     inline x::float32 x() const { return x::vector<x::float32>::operator[](0); }
        public:     inline x::float32 y() const { return x::vector<x::float32>::operator[](1); }
        public:     inline void x(x::float32 v){ x::vector<x::float32>::operator[](0) = v; }
        public:     inline void y(x::float32 v){ x::vector<x::float32>::operator[](0) = v; }
        public:     virtual void set(x::float32 x, x::float32 y);
        public:     coordinate & operator=(const x::initializer<x::float32> & list);
        public:     coordinate & operator=(const coordinate & o);
        public:     coordinate & operator=(coordinate && o) noexcept;
        public:     coordinate(const x::initializer<x::float32> & list);
        public:     coordinate(x::float32 x, x::float32 y);
        public:     coordinate();
        public:     coordinate(const coordinate & o);
        public:     coordinate(coordinate && o) noexcept;
        public:     ~coordinate() override;
        };
    }
}

#endif // __X_GRAPHICS__COORDINATE__HH__
