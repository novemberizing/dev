#ifndef   __X_GRAPHICS__IMAGE__HH__
#define   __X_GRAPHICS__IMAGE__HH__

#include <x/bytes.hh>

namespace x
{
    namespace graphics
    {
        class image
        {
        protected:  x::uint32 __id;
        protected:  x::uint32 __width;
        protected:  x::uint32 __height;
        protected:  x::bytes __bytes;
        public:     inline x::uint64 size() const { return __bytes.size(); }
        public:     inline x::uint32 id() const { return __id; }
        public:     inline x::uint32 width() const { return __width; }
        public:     inline x::uint32 height() const { return __height; }
        public:     inline const x::bytes & bytes() const { return __bytes; }
        public:     inline const x::byte * data() const { return __bytes.data(); }
        public:     inline void id(x::uint32 v){ __id = v; }
        public:     inline void width(x::uint32 v){ __width = v; }
        public:     inline void height(x::uint32 v){ __height = v; }
        public:     inline void bytes(const x::bytes & v){ __bytes = v; }
        public:     inline void bytes(x::bytes && v){ __bytes = x::move(v); }
        public:     x::graphics::image & operator=(const x::graphics::image & o);
        public:     x::graphics::image & operator=(x::graphics::image && o) noexcept;
        public:     image(x::uint32 width, x::uint32 height, x::bytes && bytes);
        public:     image(x::uint32 width, x::uint32 height, const x::bytes & bytes);
        public:     image();
        public:     image(const x::graphics::image & o);
        public:     image(x::graphics::image && o) noexcept;
        public:     virtual ~image();
        };
    }
}

#endif // __X_GRAPHICS__IMAGE__HH__
