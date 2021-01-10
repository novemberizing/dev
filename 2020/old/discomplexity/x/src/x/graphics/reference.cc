#include "reference.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        reference::reference(const x::string & name, x::graphics::object * object)
        :   __name(name),
            __object(object),
            __position(),
            __rotation(),
            __scale({1.0f, 1.0f, 1.0f}),
            __model(),
            __status(0),
            __children()
        {
            refresh();
        }

        reference::reference(x::string && name, x::graphics::object * object)
        :   __name(x::move(name)),
            __object(object),
            __position(),
            __rotation(),
            __scale({1.0f, 1.0f, 1.0f}),
            __model(),
            __status(0),
            __children()
        {
            refresh();
        }

        reference::reference()
        :   __name(),
            __object(nullptr),
            __position(),
            __rotation(),
            __scale({1.0f, 1.0f, 1.0f}),
            __model(),
            __status(0),
            __children()
        {
            refresh();
        }

        reference::reference(const reference & o)
        :   __name(o.__name),
            __object(o.__object),
            __position(o.__position),
            __rotation(o.__rotation),
            __scale(o.__scale),
            __model(o.__model),
            __status(o.__status),
            __children(o.__children)
        {
        }

        reference::reference(reference && o) noexcept
        :   __name(x::move(o.__name)),
            __object(o.__object),
            __position(x::move(o.__position)),
            __rotation(x::move(o.__rotation)),
            __scale(x::move(o.__scale)),
            __model(x::move(o.__model)),
            __status(o.__status),
            __children(o.__children)
        {
            o.__object = nullptr;
            o.__status = 0;
        }

        reference::~reference()
        {
        }

        reference & reference::operator=(const reference & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __object = o.__object;
                __position = o.__position;
                __rotation = o.__rotation;
                __scale = o.__scale;
                __model = o.__model;
                __status = o.__status;
                __children = o.__children;
            }
            return *this;
        }

        reference & reference::operator=(reference && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __object = o.__object;
                __position = x::move(o.__position);
                __rotation = x::move(o.__rotation);
                __scale = x::move(o.__scale);
                __model = x::move(o.__model);
                __status = o.__status;
                __children = x::move(o.__children);

                o.__object = nullptr;
                o.__status = 0;
            }
            return *this;
        }

        void reference::render()
        {
            __object->render(__model, level());
            __children.each([this](const x::string & name, x::graphics::reference & reference){
                reference.render(__model, level());
            });
        }

        void reference::render(const x::graphics::matrix & model, x::uint32 level)
        {
            exceptional();
            // __children.each([](const x::string & name, x::graphics::reference & reference){
            //     reference.render(__model);
            // });
        }

        void reference::start()
        {
        }

        void reference::update()
        {
        }

        void reference::refresh()
        {
            __model = x::graphics::matrix::translate(x::graphics::matrix::identity(), __position);
            if(__rotation.x() != 0)
            {
                __model = x::graphics::matrix::rotate(__model, __rotation.x(), { 1.0f, 0.0f, 0.0f});
            }
            if(__rotation.y() != 0)
            {
                __model = x::graphics::matrix::rotate(__model, __rotation.y(), { 0.0f, 1.0f, 0.0f});
            }
            if(__rotation.z() != 0)
            {
                __model = x::graphics::matrix::rotate(__model, __rotation.z(), { 0.0f, 0.0f, 1.0f});
            }
            __model = x::graphics::matrix::scale(__model, __scale);
            __object->refresh(__model);
        }

        void reference::exec(const x::array<x::string> & strings, x::uint64 index)
        {
            if(index < strings.size())
            {
                if(strings[index] == "position")
                {
                    __position.exec(strings, ++index);
                    refresh();
                    x::graphics::application::refresh();
                }
                else if(strings[index] == "rotation")
                {
                    __rotation.exec(strings, ++index, [](x::float32 v){ return x::math::radian(v); }, [](x::float32 v){ return x::math::degree(v); });
                    refresh();
                    x::graphics::application::refresh();
                }
                else if(strings[index] == "scale")
                {
                    __scale.exec(strings, ++index);
                    refresh();
                    x::graphics::application::refresh();
                }
                else if(strings[index] == "status")
                {
                    if(index + 1 < strings.size())
                    {
                        __status = x::graphics::util::uinteger32(strings[index + 1]);
                        refresh();
                        x::graphics::application::refresh();
                    }
                    else
                    {
                        x::console::out << __status << x::endl;
                    }
                }
                else
                {
                    x::graphics::util::unknown(strings);
                }
            }
            else
            {
                x::console::out << "{"
                                << "\"name\": \"" << __name << "\","
                                << "\"position\": " << __position << ","
                                << "\"rotation\": " << __rotation << ","
                                << "\"scale\": " << __scale << ","
                                << "\"status\": " << __status
                                << "}"
                                << x::endl;
            }
        }
    }
}
