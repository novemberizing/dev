#ifndef   __X_GRAPHICS__BUFFER__HH__
#define   __X_GRAPHICS__BUFFER__HH__

#include <x/bytes.hh>
#include <x/graphics/vertex.hh>
#include <x/reality/color.hh>
#include <x/reality/coordinate.hh>

namespace x
{
    namespace graphics
    {
        class buffer
        {
        public:     static const x::uint32 none = 0;
        public:     static const x::uint32 array = 1;
        public:     static const x::uint32 atomic_counter = 2;
        public:     static const x::uint32 copy_read = 3;
        public:     static const x::uint32 copy_write = 4;
        public:     static const x::uint32 dispatch_indirect = 5;
        public:     static const x::uint32 draw_indirect = 6;
        public:     static const x::uint32 element_array = 7;
        public:     static const x::uint32 pixel_pack = 8;
        public:     static const x::uint32 pixel_unpack = 9;
        public:     static const x::uint32 query = 10;
        public:     static const x::uint32 shader_storage = 11;
        public:     static const x::uint32 texture = 12;
        public:     static const x::uint32 transform_feedback = 13;
        public:     static const x::uint32 uniform = 14;
        public:     static const x::uint16 stream = 1;
        public:     static const x::uint16 statical = 2;
        public:     static const x::uint16 dynamical = 3;
        public:     static const x::uint16 draw = 1;
        public:     static const x::uint16 read = 2;
        public:     static const x::uint16 copy = 3;
        protected:  x::bytes __bytes;
        protected:  x::uint32 __target;
        protected:  x::uint32 __usage;
        protected:  x::uint32 __id;
        public:     virtual void push(const x::reality::vector & o);
        public:     virtual void push(const x::reality::color & o);
        public:     virtual void push(const x::reality::coordinate & o);
        public:     virtual void push(x::real v);
        public:     inline x::uint32 target() const { return __target; }
        public:     inline x::uint32 usage() const { return __usage; }
        public:     inline x::uint32 id() const { return __id; }
        public:     inline void id(x::uint32 v) { __id = v; }
        public:     inline x::uint64 size() const { return __bytes.size(); }
        public:     inline const x::byte * data() const { return __bytes.data(); }
        public:     inline void target(uint32 v) { __target = v; }
        public:     inline void usage(uint32 type, uint32 mode) { __usage = (type << 16U) | mode; }
        public:     buffer & operator=(const buffer & o);
        public:     buffer & operator=(buffer && o) noexcept;
        public:     buffer(x::uint32 target);
        public:     buffer();
        public:     buffer(const buffer & o);
        public:     buffer(buffer && o) noexcept;
        public:     virtual ~buffer();
        };
    }
}

#endif // __X_GRAPHICS__BUFFER__HH__
