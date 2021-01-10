#ifndef   __X_GRAPHICS_PRIMITIVES__CUBE__HH__
#define   __X_GRAPHICS_PRIMITIVES__CUBE__HH__

#include <x/graphics/primitive.hh>

namespace x
{
    namespace graphics
    {
        namespace primitives
        {
            class cube : public x::graphics::primitive
            {
            public:     x::graphics::primitives::cube & operator=(const x::graphics::primitives::cube & o) = delete;
            public:     x::graphics::primitives::cube & operator=(x::graphics::primitives::cube && o) noexcept = delete;
            public:     cube(const x::string & name);
            public:     cube(x::string && name);
            public:     cube();
            public:     cube(const x::graphics::primitives::cube & o) = delete;
            public:     cube(x::graphics::primitives::cube && o) noexcept = delete;
            public:     ~cube() override;
            };
        }
    }
}

#endif // __X_GRAPHICS_PRIMITIVES__CUBE__HH__
