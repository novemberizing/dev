#ifndef   __X_GRAPHICS__VERTICES__HH__
#define   __X_GRAPHICS__VERTICES__HH__

#include <x/graphics/type.hh>
#include <x/graphics/vertex.hh>
#include <x/graphics/buffer.hh>

namespace x
{
    namespace graphics
    {
        class vertices
        {
        public:     static const x::uint32 none = 0;
        public:     static const x::uint32 point = 1;
        public:     static const x::uint32 line = 2;
        public:     static const x::uint32 patch = 3;
        public:     static const x::uint32 triangle = 4;
        public:     static const x::uint32 strip = 1;
        public:     static const x::uint32 loop = 2;
        public:     static const x::uint32 fan = 3;
        public:     static const x::uint32 adjacent = 1;
        protected:  x::uint32 __mode;
        protected:  x::uint32 __type;
        protected:  x::uint32 __adjacency;
        protected:  x::uint32 __id;
        protected:  x::array<x::graphics::vertex> __vertices;
        public:     inline x::uint64 size() const { return __vertices.size(); }
        public:     inline void push(const x::graphics::vertex & o){ __vertices.push(o); }
        public:     inline void push(x::graphics::vertex && o){ __vertices.push(x::move(o)); }
        public:     inline x::uint32 id() const { return __id; }
        public:     inline x::uint32 mode() const { return __mode; }
        public:     inline x::uint32 adjacency() const { return __adjacency; }
        public:     inline x::uint32 type() const { return __type; }
        public:     inline void id(x::uint32 v){ __id = v; }
        public:     inline void mode(x::uint32 v) { __mode = v; }
        public:     virtual void serialize(x::graphics::buffer & buffer) const;
        public:     x::graphics::vertex & operator[](x::uint64 i){ return __vertices[i]; }
        public:     const x::graphics::vertex & operator[](x::uint64 i) const { return __vertices[i]; }
        public:     vertices & operator=(const vertices & o);
        public:     vertices & operator=(vertices && o) noexcept;
        public:     vertices();
        public:     vertices(const vertices & o);
        public:     vertices(vertices && o) noexcept;
        public:     virtual ~vertices();
        };
    }
}

#endif // __X_GRAPHICS__VERTICES__HH__
