#ifndef   __X_GRAPHICS_OBJECTS__BASE__HH__
#define   __X_GRAPHICS_OBJECTS__BASE__HH__

#include <x/graphics/object.hh>

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            class base : public x::graphics::object
            {
            protected:  x::graphics::reference * __reference;
            protected:  x::graphics::program * __program;
            protected:  x::graphics::texture * __texture;
            protected:  x::reality::matrix __model;
            public:     void start(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void update(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
            public:     x::boolean bind(const x::string & name, x::uint32 id) override;
            public:     base(x::graphics::reference * reference, x::graphics::program * program);
            public:     base(x::graphics::reference * reference, x::graphics::program * program, x::graphics::texture * texture);
            public:     ~base() override;
            public:     x::graphics::objects::base & operator=(const x::graphics::objects::base & o) = delete;
            public:     x::graphics::objects::base & operator=(x::graphics::objects::base && o) noexcept = delete;
            public:     base() = delete;
            public:     base(const x::graphics::objects::base & o) = delete;
            public:     base(x::graphics::objects::base && o) noexcept = delete;
            };
        }
    }
}

#endif // __X_GRAPHICS_OBJECTS__BASE__HH__
