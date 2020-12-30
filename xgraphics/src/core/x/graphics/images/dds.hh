#ifndef   __X_GRAPHICS_IMAGES__DDS__HH__
#define   __X_GRAPHICS_IMAGES__DDS__HH__

#include <x/graphics/mipmap.hh>
#include <x/graphics/texture.hh>
#include <x/array.hh>
#include <x/string.hh>
#include <x/file.hh>
#include <x/console.hh>
#include <x/uinteger32.hh>

namespace x
{
    namespace graphics
    {
        namespace images
        {
            class dds
            {
            public:     static x::graphics::images::dds load(const x::string & path);
            protected:  x::uint32 __width;
            protected:  x::uint32 __height;
            protected:  x::uint32 __linear;
            protected:  x::uint32 __count;
            protected:  x::uint32 __format;
            public:     x::array<x::graphics::mipmap> mipmaps;
            public:     x::graphics::texture build(const x::string & name);
            public:     x::graphics::texture build(x::string && name);
            public:     x::graphics::images::dds & operator=(const x::graphics::images::dds & o);
            public:     x::graphics::images::dds & operator=(x::graphics::images::dds && o) noexcept;
            public:     dds();
            public:     dds(const x::graphics::images::dds & o);
            public:     dds(x::graphics::images::dds && o) noexcept;
            public:     virtual ~dds();
            };
        }
    }
}

#endif // __X_GRAPHICS_IMAGES__DDS__HH__
