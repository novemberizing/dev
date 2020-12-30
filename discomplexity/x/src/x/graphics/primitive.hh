#ifndef   __X_GRAPHICS__PRIMITIVE__HH__
#define   __X_GRAPHICS__PRIMITIVE__HH__

#include <x/graphics/object.hh>
#include <x/graphics/vertices.hh>
#include <x/graphics/program.hh>
#include <x/graphics/matrix.hh>

namespace x
{
    namespace graphics
    {
        class primitive : public object
        {
        protected:  x::graphics::vertices __vertices;
        protected:  x::graphics::buffer __buffer;
        protected:  x::graphics::program * __program;
        protected:  x::array<x::uint32> __indices;
        public:     void load() override;
        public:     void unload() override;
        public:     void render(const x::graphics::matrix & model, x::uint32 level) override;
        public:     inline void program(x::graphics::program * o) { __program = o; }
        public:     inline void mode(x::uint32 v){ __vertices.mode(v); }
        public:     inline void target(x::uint32 v){ __buffer.target(v); }
        public:     inline void usage(uint32 type, uint32 mode){ __buffer.usage(type, mode); }
        public:     inline const x::graphics::vertices & vertices() const { return __vertices; }
        public:     inline x::graphics::vertices & vertices() { return __vertices; }
        public:     inline const x::graphics::buffer & buffer() const { return __buffer; }
        public:     inline x::graphics::buffer & buffer() { return __buffer; }
        public:     inline void push(x::graphics::vertex && o){ __vertices.push(x::move(o)); }
        public:     inline void push(const x::graphics::vertex & o){ __vertices.push(o); }
        public:     inline void push(x::uint32 index){ __indices.push(index); }
        public:     primitive & operator=(const primitive & o);
        public:     primitive & operator=(primitive && o) noexcept;
        public:     primitive(const x::string & name);
        public:     primitive(x::string && name);
        public:     primitive();
        public:     primitive(const primitive & o);
        public:     primitive(primitive && o) noexcept;
        public:     ~primitive() override;
        };
    }
}

#endif // __X_GRAPHICS__PRIMITIVE__HH__
