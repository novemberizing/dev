#ifndef   __X_GRAPHICS_PRIMITIVES__RECTANGLE__HH__
#define   __X_GRAPHICS_PRIMITIVES__RECTANGLE__HH__

#include <x/graphics/primitive.hh>

namespace x
{
    namespace graphics
    {
        namespace primitives
        {
            class rectangle : public x::graphics::primitive
            {
            public:     x::graphics::primitives::rectangle & operator=(const x::graphics::primitives::rectangle & o) = delete;
            public:     x::graphics::primitives::rectangle & operator=(x::graphics::primitives::rectangle && o) noexcept = delete;
            protected:  rectangle(const x::string & name);
            protected:  rectangle(x::string && name);
            public:     rectangle();
            public:     rectangle(const x::graphics::primitives::rectangle & o) = delete;
            public:     rectangle(x::graphics::primitives::rectangle && o) noexcept = delete;
            public:     ~rectangle() override;
            };
        }
    }
}

#endif // __X_GRAPHICS_PRIMITIVES__RECTANGLE__HH__
