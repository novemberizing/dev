#include "layer.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        layer::layer(const x::string & name)
        :   __name(name),
            __objects()
        {
        }

        layer::~layer()
        {
            __objects.each([](x::var<x::graphics::object *>::type & o){
                if(o)
                {
                    delete o;
                    o = nullptr;
                }
            });
        }

        void layer::start()
        {
            __objects.each([](x::var<x::graphics::object *>::type & o){
                o->start(x::reality::matrix::identity, x::reality::camera::eye());
            });
        }

        void layer::update()
        {
            __objects.each([](x::var<x::graphics::object *>::type & o){
                o->update(x::reality::matrix::identity, x::reality::camera::eye());
            });
        }

        void layer::render()
        {
            __objects.each([](x::var<x::graphics::object *>::type & o){
                o->render(x::reality::vector::center, x::reality::camera::eye());
            });
        }

        x::boolean layer::on(const x::reality::event & event)
        {
            return __objects.until([&event](x::var<x::graphics::object *>::type & object){
                return object->on(event);
            });
        }
    }
}
