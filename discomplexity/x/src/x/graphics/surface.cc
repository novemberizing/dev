#include "surface.hh"

namespace x
{
    namespace graphics
    {
        surface::surface(x::float32 aspect)
        :   __background({ 0.0f, 0.0f, 0.0f, 1.0f }),
            __objects(),
            __light({ 18.0f, 7.0f, 30.0f, 1.0f }, {1.0f, 1.0f, 1.0f, 1.0f}, 0.3),
            __camera({ 0.0f, 0.0f, 90.0f, 1.0f }),
            __projection(aspect)
        {
            // 0.000000,30.000000,80.000000,1.000000
        }
        surface::surface()
        :   __background({ 0.0f, 0.0f, 0.0f, 1.0f }),
            __objects(),
            __light({ 18.0f, 7.0f, 30.0f, 1.0f }, {1.0f, 1.0f, 1.0f, 1.0f}, 0.3),
            __camera({ 0.0f, 0.0f, 90.0f, 1.0f }),
            __projection()
        {
        }

        surface::surface(const surface & o)
        :   __background(o.__background),
            __objects(o.__objects),
            __light(o.__light),
            __camera(o.__camera),
            __projection(o.__projection)
        {
            // TODO: NEED TO DEEP COPY
        }

        surface::surface(surface && o) noexcept
        :   __background(x::move(o.__background)),
            __objects(x::move(o.__objects)),
            __light(x::move(o.__light)),
            __camera(x::move(o.__camera)),
            __projection(x::move(o.__projection))
        {

        }

        surface::~surface()
        {
        }

        surface & surface::operator=(const surface & o)
        {
            if(&o != this)
            {
                __background = o.__background;
                __objects = o.__objects;
                __light = o.__light;
                __camera = o.__camera;
                __projection = o.__projection;
            }
            return *this;
        }

        surface & surface::operator=(surface && o) noexcept
        {
            if(&o != this)
            {
                __background = x::move(o.__background);
                __objects = x::move(o.__objects);
                __light = x::move(o.__light);
                __camera = x::move(o.__camera);
                __projection = x::move(o.__projection);
            }
            return *this;
        }

        void surface::refresh()
        {
            __camera.refresh();
            __projection.refresh();
        }

        x::graphics::reference & surface::reference(const x::string & name)
        {
            return __objects[name];
        }

        void surface::exec(const x::array<x::string> & strings)
        {
            if(strings[0] == "reference")
            {
                if(strings.size() == 1)
                {
                    __objects.each([](const x::string & name, x::graphics::reference & reference){
                        x::console::out << name << x::endl;
                    });
                }
                else
                {
                    x::graphics::reference & reference = __objects[strings[1]];
                    reference.exec(strings, 2);
                    //
                    // if(strings[1] == "position")
                    // {
                    //
                    // }
                    // else
                    // {
                    //     x::console::out << "todo" << x::endl;
                    // }
                }
            }
            else
            {
                x::graphics::util::unknown(strings);
            }
        }
    }
}
