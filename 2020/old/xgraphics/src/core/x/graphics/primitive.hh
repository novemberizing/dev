#ifndef   __X_GRAPHICS__PRIMITIVE__HH__
#define   __X_GRAPHICS__PRIMITIVE__HH__

#include <x/graphics/reference.hh>
#include <x/graphics/vertices.hh>
#include <x/graphics/buffer.hh>
#include <x/graphics/program.hh>

namespace x
{
    namespace graphics
    {
        class primitive : public x::graphics::reference
        {
        public:     x::graphics::vertices vertices;
        public:     x::graphics::buffer buffer;
        public:     x::array<x::uint32> indices;
        protected:  x::string __name;
        public:     inline void mode(x::uint32 v){ vertices.mode(v); }
        public:     inline void target(x::uint32 v){ buffer.target(v); }
        public:     inline void usage(uint32 type, uint32 mode){ buffer.usage(type, mode); }
        public:     inline void push(x::graphics::vertex && o){ vertices.push(x::move(o)); }
        public:     inline void push(const x::graphics::vertex & o){ vertices.push(o); }
        public:     inline void push(x::uint32 index){ indices.push(index); }
        public:     const x::string & name() const override;
        public:     void load() override;
        public:     void unload() override;
        public:     void render() override;
        protected:  x::graphics::primitive & operator=(const x::graphics::primitive & o);
        protected:  x::graphics::primitive & operator=(x::graphics::primitive && o) noexcept;
        public:     primitive(const x::string & name);
        public:     primitive(x::string && name);
        public:     primitive();
        protected:  primitive(const x::graphics::primitive & o);
        protected:  primitive(x::graphics::primitive && o) noexcept;
        public:     ~primitive() override;
        };
    }
}

#endif // __X_GRAPHICS__PRIMITIVE__HH__
