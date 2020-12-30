#include "surface.hh"

namespace x
{
    namespace graphics
    {
        surface::surface()
        :   background(),
            layers()
        {
        }

        surface::surface(const x::reality::color & background)
        :   background(background),
            layers()
        {
        }

        surface::~surface()
        {
            layers.each([](x::var<x::graphics::layer *>::type & layer){
                if(layer)
                {
                    delete layer;
                    layer = nullptr;
                }
            });
        }

        void surface::render()
        {
            layers.each([](x::var<x::graphics::layer *>::type & layer){
                layer->render();
            });
        }

        void surface::start()
        {
            layers.each([](x::var<x::graphics::layer *>::type & layer){
                layer->start();
            });
        }

        void surface::update()
        {
            layers.each([](x::var<x::graphics::layer *>::type & layer){
                layer->update();
            });
        }

        x::boolean surface::on(const x::reality::event & event)
        {
            return layers.until([&event](x::var<x::graphics::layer *>::type & layer){ return layer->on(event); });
        }

        // public:     virtual ;
        // public:     virtual void start();
        // public:     virtual void update();
        // public:     ;
        // public:     ;
        // public:     virtual ;

        // surface::surface()
        // :   background({0.0f, 0.0f, 0.0f, 1.0f}),
        //     layers()
        // {
        // }
        //
        // surface::surface(const x::reality::color & background)
        // :   background(background),
        //     layers()
        // {
        // }
        //
        // surface::~surface()
        // {
        // }
        //
        // void surface::render()
        // {
        //     layers.each([](x::var<x::graphics::layer *>::type & layer){ layer->render(); });
        // }
        //
        // void surface::start()
        // {
        //     layers.each([](x::var<x::graphics::layer *>::type & layer){ layer->start(); });
        // }
        //
        // void surface::update()
        // {
        //     layers.each([](x::var<x::graphics::layer *>::type & layer){ layer->update(); });
        // }
        //
        // x::boolean surface::mousemove(x::int32 x, x::int32 y)
        // {
        //     return layers.until([x, y](x::var<x::graphics::layer *>::type & layer){ return layer->mousemove(x, y); });
        // }
        //
        // x::boolean surface::mouse(x::int32 button, x::int32 state, x::int32 x, x::int32 y)
        // {
        //     return layers.until([button, state, x, y](x::var<x::graphics::layer *>::type & layer){ return layer->mouse(button, state, x, y); });
        // }
    }
}
