#ifndef   __X_GRAPHICS__LAYER__HH__
#define   __X_GRAPHICS__LAYER__HH__

#include <x/graphics/object.hh>
#include <x/graphics/vertices.hh>
#include <x/graphics/buffer.hh>
#include <x/graphics/program.hh>

namespace x
{
    namespace graphics
    {
        class layer
        {
        protected:  x::string __name;
        protected:  x::array<x::graphics::object *> __objects;
        public:     inline const x::string & name() const { return __name; }
        public:     inline void add(x::graphics::object * o) { __objects.append(o); }
        public:     virtual void start();
        public:     virtual void update();
        public:     virtual void render();
        public:     virtual x::boolean on(const x::reality::event & event);
        public:     layer(const x::string & name);
        public:     virtual ~layer();
        public:     x::graphics::layer & operator=(const x::graphics::layer & o) = delete;
        public:     x::graphics::layer & operator=(x::graphics::layer && o) noexcept = delete;
        public:     layer() = delete;
        public:     layer(const x::graphics::layer & o) = delete;
        public:     layer(x::graphics::layer && o) noexcept = delete;
        };
    }
}

#endif // __X_GRAPHICS__LAYER__HH__
