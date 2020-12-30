#ifndef   __X_GRAPHICS_OBJECTS__ROOT__HH__
#define   __X_GRAPHICS_OBJECTS__ROOT__HH__

#include <x/graphics/objects/joint.hh>

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            class root : public x::graphics::object
            {
            protected:  x::graphics::objects::joint * __root;
            public:     void start(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void update(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
            public:     root(x::graphics::objects::joint * root);
            public:     ~root() override;
            public:     x::graphics::objects::root & operator=(const x::graphics::objects::root & o) = delete;
            public:     x::graphics::objects::root & operator=(x::graphics::objects::root && o) noexcept = delete;
            public:     root() = delete;
            public:     root(const x::graphics::objects::root & o) = delete;
            public:     root(x::graphics::objects::root && o) noexcept = delete;
            };
        }
    }
}

#endif // __X_GRAPHICS_OBJECTS__ROOT__HH__
