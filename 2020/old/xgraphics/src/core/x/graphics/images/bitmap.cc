#include "bitmap.hh"

namespace x
{
    namespace graphics
    {
        namespace images
        {
            x::graphics::images::bitmap bitmap::load(const x::string & path)
            {
                x::graphics::images::bitmap result;
                x::bytes content = x::file::data(path);
                x::uint32 position = x::uinteger32::from(content.data(), 0x0A);
                x::uint32 size = x::uinteger32::from(content.data(), 0x22);
                x::uint32 width = x::uinteger32::from(content.data(), 0x12);
                x::uint32 height = x::uinteger32::from(content.data(), 0x16);

                result.__mipmap = x::graphics::mipmap(width, height, content.sub(position, size));

                return result;
            }

            bitmap::bitmap()
            {
            }

            bitmap::bitmap(const bitmap & o)
            {
            }

            bitmap::bitmap(bitmap && o) noexcept
            {
            }

            bitmap::~bitmap()
            {
            }

            bitmap & bitmap::operator=(const bitmap & o)
            {
                if(&o != this)
                {
                }
                return *this;
            }

            bitmap & bitmap::operator=(bitmap && o) noexcept
            {
                if(&o != this)
                {
                }
                return *this;
            }

            x::graphics::texture bitmap::build(const x::string & name)
            {
                return x::graphics::texture(name, __mipmap);
            }

            x::graphics::texture bitmap::build(x::string && name)
            {
                return x::graphics::texture(x::move(name), __mipmap);
            }
        }
    }
}
