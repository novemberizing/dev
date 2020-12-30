#ifndef   __X_GRAPHICS_PRIMITIVES__TRIANGLE__HH__
#define   __X_GRAPHICS_PRIMITIVES__TRIANGLE__HH__

#include <x/graphics/primitive.hh>

namespace x
{
    namespace graphics
    {
        namespace primitives
        {
            class triangle : public x::graphics::primitive
            {
            public:     x::graphics::primitives::triangle & operator=(const x::graphics::primitives::triangle & o) = delete;
            public:     x::graphics::primitives::triangle & operator=(x::graphics::primitives::triangle && o) noexcept = delete;
            protected:  triangle(const x::string & name);
            protected:  triangle(x::string && name);
            public:     triangle();
            public:     triangle(const x::graphics::primitives::triangle & o) = delete;
            public:     triangle(x::graphics::primitives::triangle && o) noexcept = delete;
            public:     ~triangle() override;
            };
        }
    }
}

#endif // __X_GRAPHICS_PRIMITIVES__TRIANGLE__HH__
