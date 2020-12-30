#ifndef   __X_GRAPHICS__TEXTURE__HH__
#define   __X_GRAPHICS__TEXTURE__HH__

#include <x/bytes.hh>
#include <x/string.hh>
#include <x/graphics/mipmap.hh>

namespace x
{
    namespace graphics
    {
        class texture
        {
        protected:  x::string __name;
        protected:  x::uint32 __id;
        protected:  x::uint32 __format;
        public:     x::array<x::graphics::mipmap> mipmaps;
        public:     inline const x::string & name() const { return __name; }
        public:     inline x::uint32 id() const { return __id; }
        public:     inline x::uint32 format() const { return __format; }
        public:     inline void id(x::uint32 v){ __id = v; }
        public:     inline void name(const x::string & v){ __name = v; }
        public:     inline void name(x::string && v) { __name = x::move(v); }
        public:     inline void format(x::uint32 v){ __format = v; }
        public:     virtual void load();
        public:     virtual void unload();
        public:     x::graphics::texture & operator=(const x::graphics::texture & o);
        public:     x::graphics::texture & operator=(x::graphics::texture && o) noexcept;
        public:     texture(const x::string & name, const x::graphics::mipmap & image);
        public:     texture(x::string && name, const x::graphics::mipmap & image);
        public:     texture(const x::string & name, x::uint32 format, const x::array<x::graphics::mipmap> & images);
        public:     texture(x::string && name, x::uint32 format, const x::array<x::graphics::mipmap> & images);
        public:     texture();
        public:     texture(const x::graphics::texture & o);
        public:     texture(x::graphics::texture && o) noexcept;
        public:     virtual ~texture();
        };
    }
}

#endif // __X_GRAPHICS__TEXTURE__HH__
