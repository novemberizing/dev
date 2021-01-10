#ifndef   __X_GRAPHICS_IMAGES__BITMAP__HH__
#define   __X_GRAPHICS_IMAGES__BITMAP__HH__

#include <x/string.hh>
#include <x/bytes.hh>
#include <x/file.hh>
#include <x/console.hh>
#include <x/uinteger32.hh>
#include <x/graphics/mipmap.hh>
#include <x/graphics/texture.hh>

namespace x
{
    namespace graphics
    {
        namespace images
        {
            class bitmap
            {
            public:     static x::graphics::images::bitmap load(const x::string & path);
            protected:  x::graphics::mipmap __mipmap;
            public:     x::graphics::texture build(const x::string & name);
            public:     x::graphics::texture build(x::string && name);
            public:     bitmap & operator=(const bitmap & o);
            public:     bitmap & operator=(bitmap && o) noexcept;
            public:     bitmap();
            public:     bitmap(const bitmap & o);
            public:     bitmap(bitmap && o) noexcept;
            public:     virtual ~bitmap();
            };
        }
    }
}

#endif // __X_GRAPHICS_IMAGES__BITMAP__HH__
