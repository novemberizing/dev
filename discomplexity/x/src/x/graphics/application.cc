#include "application.hh"

namespace x
{
    namespace graphics
    {
        application::application()
        :   __x(100),
            __y(100),
            __width(800),
            __height(600),
            __name("x::graphics"),
            __shaders(),
            __programs(),
            __surface(800.0f / 600.0f),
            __engine(),
            __objects()
        {
        }

        application::~application()
        {
        }

        // void application::add(x::graphics::object * o)
        // {
        //     if(o)
        //     {
        //         x::reference<x::graphics::object *> reference(o);
        //         __objects.add(reference);
        //         // __surface.add(reference.get);
        //     }
        // }

        void application::exec(const x::string & command)
        {
            x::array<x::string> strings = command.split([](const char * s, x::uint64 & i, x::uint64 until){
                if(s[i] == ' ')
                {
                    i = i + 1;
                    return x::string();
                }
                else if(s[i] == '\"')
                {
                    for(i = i + 1; i < until; i++)
                    {
                        if(s[i] == '\"')
                        {
                            i = i + 1;
                            if(s[i] == ' ')
                            {
                                i = i + 1;
                                return x::string(&s[1], i - 3);
                            }
                            else
                            {
                                return x::string(&s[1], i - 2);
                            }
                        }
                    }
                }
                else
                {
                    for(i = i + 1; i < until; i++)
                    {
                        if(s[i] == ' ')
                        {
                            i = i + 1;
                            return x::string(s, i - 1);
                        }
                    }
                }
                return x::string(s, until);
            });
            exec(strings);
        }

        void application::exec(const x::array<x::string> & strings)
        {
            for(x::uint64 i = 0; i < strings.size(); i++)
            {
                x::console::out << strings[i] << x::endl;
            }
            if(strings.size() > 0)
            {
                try
                {
                    if(strings[0] == "camera")
                    {
                        x::graphics::camera & camera = __surface.camera();
                        camera.exec(strings, 1);
                    }
                    else if(strings[0] == "light")
                    {
                        x::graphics::light & light = __surface.light();
                        light.exec(strings, 1);
                    }
                    else if(strings[0] == "projection")
                    {
                        x::graphics::projection & projection = __surface.projection();
                        projection.exec(strings, 1);
                    }
                    else if(strings[0] == "object")
                    {
                        if(strings.size() == 1)
                        {
                            __objects.each([](const x::string & key, x::graphics::object * object){
                                x::console::out << object->name() << x::endl;
                            });
                        }
                        else
                        {
                            try
                            {
                                x::graphics::object * o = __objects[strings[1]];
                                o->exec(strings, 2);
                                // x::console::out << "object[\"" << strings[1] << "\"] exist" << x::endl;
                            }
                            catch(const x::exception & e)
                            {
                                x::console::out << "object[\"" << strings[1] << "\"] not found" << x::endl;
                            }
                        }
                    }
                    else if(strings[0] == "reference")
                    {
                        __surface.exec(strings);
                    }
                    else
                    {
                        x::graphics::util::unknown(strings);
                    }
                }
                catch(const x::exception & e)
                {
                    x::graphics::util::unknown(strings);
                }
            }
        }
    }
}
