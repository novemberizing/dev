#ifndef   __X_GRAPHICS__SURFACE__HH__
#define   __X_GRAPHICS__SURFACE__HH__

#include <x/map.hh>

#include <x/reality/color.hh>
#include <x/reality/light.hh>
#include <x/reality/camera.hh>
#include <x/reality/projection.hh>
#include <x/reality/world.hh>
#include <x/graphics/object.hh>
#include <x/graphics/layer.hh>

namespace x
{
    namespace graphics
    {
        class surface
        {
        public:     x::reality::color background;
        public:     x::array<x::graphics::layer *> layers;
        public:     virtual void add(x::graphics::layer * layer){ layers.append(layer); }
        public:     virtual void render();
        public:     virtual void start();
        public:     virtual void update();
        public:     virtual x::boolean on(const x::reality::event & o);
        public:     surface();
        public:     surface(const x::reality::color & background);
        public:     virtual ~surface();
        public:     x::graphics::surface & operator=(const x::graphics::surface & o) = delete;
        public:     x::graphics::surface & operator=(x::graphics::surface && o) noexcept = delete;
        public:     surface(const x::graphics::surface & o) = delete;
        public:     surface(x::graphics::surface && o) noexcept = delete;
        };
    }
}

#endif // __X_GRAPHICS__SURFACE__HH__
