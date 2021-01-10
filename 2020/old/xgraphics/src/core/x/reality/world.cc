#include "world.hh"

namespace x
{
    namespace reality
    {
        // world::world()
        // :   __background({0.0f, 0.0f, 0.0f, 1.0f}),
        //     references(),
        //     light({ 18.0f, 7.0f, 30.0f, 1.0f }, {1.0f, 1.0f, 1.0f, 1.0f}, 0.3),
        //     camera({ 0.0f, 0.0f, 300.0f, 1.0f }),
        //     projection()
        // {
        // }
        //
        // world::world(x::reality::world && o) noexcept
        // :   __background(x::move(o.__background)),
        //     references(x::move(o.references)),
        //     light(x::move(o.light)),
        //     camera(x::move(o.camera)),
        //     projection(x::move(o.projection))
        // {
        // }
        //
        // world::~world()
        // {
        //     references.each([](const x::string & name, x::var<x::reality::object *>::type & reference){
        //         if(reference)
        //         {
        //             delete reference;
        //             reference = nullptr;
        //         }
        //     });
        // }
        //
        // x::reality::world & world::operator=(x::reality::world && o) noexcept
        // {
        //     if(&o != this)
        //     {
        //         __background = x::move(o.__background);
        //         references = x::move(o.references);
        //         light = x::move(o.light);
        //         camera = x::move(o.camera);
        //         projection = x::move(o.projection);
        //     }
        //     return *this;
        // }
        //
        // void world::render()
        // {
        //     // x::reality::matrix model = x::reality::matrix::identity;
        //
        //     // references.each([&model](const x::string & name, x::var<x::reality::object *>::type & reference){
        //     //     reference->render(model, x::reality::camera::current());
        //     // });
        // }
        //
        // void world::update()
        // {
        //     exceptional();
        // }
        //
        // void world::start()
        // {
        //     exceptional();
        // }
        //
        // void world::add(const x::string & name, x::reality::object * o)
        // {
        //     // TODO: REMOVE OLD OBJECT
        //     references.put(name, o);
        // }
    }
}
