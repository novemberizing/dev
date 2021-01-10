#ifndef   __X_GRAPHICS_PRIMITIVES__IMAGE__HH__
#define   __X_GRAPHICS_PRIMITIVES__IMAGE__HH__

#if 0

#include <x/graphics/primitive.hh>
#include <x/graphics/texture.hh>

namespace x
{
    namespace graphics
    {
        namespace primitives
        {
            class image : public x::graphics::rectangle
            {
            protected:  x::graphics::texture * __texture;
            public:     x::boolean bind(const x::string & name, x::uint32 id, const x::reality::matrix & matrix) override;
            public:     x::graphics::primitives::image & operator=(const x::graphics::primitives::image & o);
            public:     x::graphics::primitives::image & operator=(x::graphics::primitives::image && o) noexcept;
            public:     image(const x::string & name, x::graphics::texture * texture, const x::reality::vector & scale, const x::reality::vector & rotate, x::real repeat);
            public:     image(x::string && name, x::graphics::texture * texture, const x::reality::vector & scale, const x::reality::vector & rotate, x::real repeat);
            public:     image();
            public:     image(const x::graphics::primitives::image & o);
            public:     image(x::graphics::primitives::image && o) noexcept;
            public:     ~image() override;
            };
        }
    }
}

#endif // 0

#endif // __X_GRAPHICS_PRIMITIVES__IMAGE__HH__
