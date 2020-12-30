#include "Joint.hh"

#include <x/graphics/application.hh>

namespace Homeworld2
{
    Joint::Joint()
    :   __name(),
        __parent(),
        __position(),
        __rotation(),
        __scale(),
        __axis(),
        __freedom(),
        __objects(),
        __children(),
        __model()
    {
    }

    Joint::Joint(const Joint & o)
    :   __name(o.__name),
        __parent(o.__parent),
        __position(o.__position),
        __rotation(o.__rotation),
        __scale(o.__scale),
        __axis(o.__axis),
        __freedom(o.__freedom),
        __objects(o.__objects),
        __children(o.__children),
        __model(o.__model)
    {

    }

    Joint::Joint(Joint && o) noexcept
    :   __name(x::move(o.__name)),
        __parent(x::move(o.__parent)),
        __position(x::move(o.__position)),
        __rotation(x::move(o.__rotation)),
        __scale(x::move(o.__scale)),
        __axis(x::move(o.__axis)),
        __freedom(x::move(o.__freedom)),
        __objects(x::move(o.__objects)),
        __children(x::move(o.__children)),
        __model(x::move(o.__model))
    {

    }

    Joint::~Joint()
    {

    }

    Joint & Joint::operator=(const Joint & o)
    {
        if(&o != this)
        {
            __name = o.__name;
            __parent = o.__parent;
            __position = o.__position;
            __rotation = o.__rotation;
            __scale = o.__scale;
            __axis = o.__axis;
            __freedom = o.__freedom;
            __objects = o.__objects;
            __children = o.__children;
            __model = o.__model;
        }
        return *this;
    }

    Joint & Joint::operator=(Joint && o) noexcept
    {
        if(&o != this)
        {
            __name = x::move(o.__name);
            __parent = x::move(o.__parent);
            __position = x::move(o.__position);
            __rotation = x::move(o.__rotation);
            __scale = x::move(o.__scale);
            __axis = x::move(o.__axis);
            __freedom = x::move(o.__freedom);
            __objects = x::move(o.__objects);
            __children = x::move(o.__children);
            __model = x::move(o.__model);
        }
        return *this;
    }

    void Joint::refresh(const x::graphics::matrix & model)
    {
        // x::console::out << __position << x::endl;
        // x::console::out << __rotation << x::endl;

        if(__axis.z()!=0 || __axis.x()!=0 || __axis.y()!=0)
        {
            x::console::out << __name << " => " << x::graphics::vector::degree(__axis) << x::endl;
        }

        // __model = x::graphics::matrix::translate(model, __position);
        //
        // if(__rotation.y() != 0)
        // {
        //     __model = x::graphics::matrix::rotate(__model, __rotation.y(), { 1.0f, 0.0f, 0.0f});
        // }
        // if(__rotation.x() != 0)
        // {
        //     __model = x::graphics::matrix::rotate(__model, __rotation.x(), { 0.0f, 1.0f, 0.0f});
        // }
        // if(__rotation.z() != 0)
        // {
        //     __model = x::graphics::matrix::rotate(__model, __rotation.z(), { 0.0f, 0.0f, 1.0f});
        // }
        // __model = x::graphics::matrix::scale(__model, __scale);
        //
        // x::graphics::matrix origin = __model;
        //
        // if(__axis.x() != 0)
        // {
        //     __model = x::graphics::matrix::rotate(__model, __axis.x(), { 0.0f, 1.0f, 0.0f});
        // }
        // if(__axis.y() != 0)
        // {
        //     __model = x::graphics::matrix::rotate(__model, __axis.y(), { 1.0f, 0.0f, 0.0f});
        // }
        // if(__axis.z() != 0)
        // {
        //     __model = x::graphics::matrix::rotate(__model, __axis.z(), { 0.0f, 0.0f, 1.0f});
        // }

        // __model = model * __model;
        // __children.each([this, &origin](Joint * joint){
        //     joint->refresh(origin);
        // });
    }

    void Joint::render(const x::graphics::matrix & model, x::uint32 level)
    {
        __model = x::graphics::matrix::translate(model, __position);

        if(__axis.x() != 0)
        {
            __model = x::graphics::matrix::rotate(__model, __axis.x(), { 1.0f, 0.0f, 0.0f});
        }
        if(__axis.y() != 0)
        {
            __model = x::graphics::matrix::rotate(__model, __axis.y(), { 0.0f, 1.0f, 0.0f});
        }
        if(__axis.z() != 0)
        {
            __model = x::graphics::matrix::rotate(__model, __axis.z(), { 0.0f, 0.0f, 1.0f});
        }

        if(__rotation.y() != 0)
        {
            __model = x::graphics::matrix::rotate(__model, __position.x() > 0 ? __rotation.y() : -__rotation.y(), { 1.0f, 0.0f, 0.0f});
        }
        if(__rotation.x() != 0)
        {
            __model = x::graphics::matrix::rotate(__model, __rotation.x(), { 0.0f, 1.0f, 0.0f});
        }
        if(__rotation.z() != 0)
        {
            __model = x::graphics::matrix::rotate(__model, __rotation.z(), { 0.0f, 0.0f, 1.0f});
        }

        __model = x::graphics::matrix::scale(__model, __scale);

        __objects.each([this, &level](x::graphics::object * o){
            o->render(__model, level);
        });
        __children.each([this, &level](Joint * joint){
            joint->render(__model, level);
        });
    }

    x::graphics::matrix Joint::axis(const x::graphics::matrix & model)
    {
        x::graphics::matrix result = model;
        if(__axis.x() != 0)
        {
            result = x::graphics::matrix::rotate(result, __axis.x(), { 0.0f, 1.0f, 0.0f});
        }
        if(__axis.y() != 0)
        {
            result = x::graphics::matrix::rotate(result, __axis.y(), { 1.0f, 0.0f, 0.0f});
        }
        if(__axis.z() != 0)
        {
            result = x::graphics::matrix::rotate(result, __axis.z(), { 0.0f, 0.0f, 1.0f});
        }
        return result;
    }

    void Joint::exec(const x::array<x::string> & strings, x::uint64 index)
    {
        if(index < strings.size())
        {
            if(strings[index] == "position")
            {
                __rotation.exec(strings, ++index);
                x::graphics::application::refresh();
            }
            else if(strings[index] == "rotation")
            {
                __rotation.exec(strings, ++index, [](x::float32 v){ return x::math::radian(v); }, [](x::float32 v){ return x::math::degree(v); });
                x::graphics::application::refresh();
            }
            else if(strings[index] == "axis")
            {
                __axis.exec(strings, ++index, [](x::float32 v){ return x::math::radian(v); }, [](x::float32 v){ return x::math::degree(v); });
                x::graphics::application::refresh();
            }
            else
            {
                x::graphics::util::unknown(strings);
            }
        }
        else
        {
            x::console::out << "{"
                            << "\"position\": " << __position << ","
                            << "\"rotation\": " << x::graphics::vector::degree(__rotation) << ","
                            << "\"axis\": " << x::graphics::vector::degree(__axis)
                            << "}"
                            << x::endl;
        }
    }
}
