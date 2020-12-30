#ifndef   __X_GRAPHICS_OBJECTS__MULTI__HH__
#define   __X_GRAPHICS_OBJECTS__MULTI__HH__

#include <x/graphics/object.hh>

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            class multi : public x::graphics::object
            {
            protected:  x::array<x::graphics::object *> __objects;
            public:     virtual void add(x::graphics::object * o);
            public:     void start(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void update(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
            public:     multi();
            public:     ~multi() override;
            public:     x::graphics::objects::multi & operator=(const x::graphics::objects::multi & o) = delete;
            public:     x::graphics::objects::multi & operator=(x::graphics::objects::multi && o) noexcept = delete;
            public:     multi(const x::graphics::objects::multi & o) = delete;
            public:     multi(x::graphics::objects::multi && o) noexcept = delete;
            };
        }
    }
}

#endif // __X_GRAPHICS_OBJECTS__MULTI__HH__
