#ifndef   __X_GRAPHICS__MIPMAP__HH__
#define   __X_GRAPHICS__MIPMAP__HH__

#include <x/graphics/image.hh>

namespace x
{
    namespace graphics
    {
        class mipmap : public x::graphics::image
        {
        public:     x::graphics::mipmap & operator=(const x::graphics::mipmap & o);
        public:     x::graphics::mipmap & operator=(x::graphics::mipmap && o) noexcept;
        public:     mipmap(x::uint32 width, x::uint32 height, x::bytes && bytes);
        public:     mipmap(x::uint32 width, x::uint32 height, const x::bytes & bytes);
        public:     mipmap();
        public:     mipmap(const x::graphics::mipmap & o);
        public:     mipmap(x::graphics::mipmap && o) noexcept;
        public:     ~mipmap() override;
        };
    }
}

#endif // __X_GRAPHICS__MIPMAP__HH__
