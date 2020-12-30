#ifndef   __X_GRAPHICS_OBJECTS__SINGLE__HH__
#define   __X_GRAPHICS_OBJECTS__SINGLE__HH__

#include <x/graphics/object.hh>

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            class single : public x::graphics::object
            {
            protected:  x::graphics::object * __object;
            public:     void start(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void update(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
            public:     single(x::graphics::object * object);
            public:     ~single() override;
            public:     x::graphics::objects::single & operator=(const x::graphics::objects::single & o) = delete;
            public:     x::graphics::objects::single & operator=(x::graphics::objects::single && o) noexcept = delete;
            public:     single() = delete;
            public:     single(const x::graphics::objects::single & o) = delete;
            public:     single(x::graphics::objects::single && o) noexcept = delete;
            };
        }
    }
}

#endif // __X_GRAPHICS_OBJECTS__SINGLE__HH__
