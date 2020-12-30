#include "../Unit.hh"

namespace Homeworld2
{
    Unit::Camera::Camera()
    :   x::reality::camera(),
        __unit(nullptr),
        __view(Unit::Camera::Normal)
    {
    }

    Unit::Camera::Camera(const Unit::Camera & o)
    :   x::reality::camera(o),
        __unit(o.__unit),
        __view(o.__view)
    {
    }

    Unit::Camera::Camera(Unit::Camera && o) noexcept
    :   x::reality::camera(x::move(o)),
        __unit(o.__unit),
        __view(o.__view)
    {
        o.__unit = nullptr;
        o.__view = Unit::Camera::Normal;
    }

    Unit::Camera::~Camera()
    {
        __unit = nullptr;
        __view = Unit::Camera::Normal;
    }

    Unit::Camera & Unit::Camera::operator=(const Unit::Camera & o)
    {
        if(&o != this)
        {
            x::reality::camera::operator=(o);

            __unit = o.__unit;
            __view = o.__view;
        }
        return *this;
    }

    Unit::Camera & Unit::Camera::operator=(Unit::Camera && o) noexcept
    {
        if(&o != this)
        {
            x::reality::camera::operator=(x::move(o));

            __unit = o.__unit;
            __view = o.__view;

            o.__unit = nullptr;
            o.__view = Unit::Camera::Normal;
        }
        return *this;
    }

    void Unit::Camera::view(x::uint32 v)
    {
        __view = v;
        update();
    }

    void Unit::Camera::start()
    {
        update();
    }

    void Unit::Camera::update()
    {
        if(__view == Unit::Camera::Normal)
        {
            const x::reality::vector & direction = __unit->direction();

            x::reality::matrix model = x::reality::matrix::identity();
            x::reality::vector center = x::reality::vector({0.0f, 0.0f, 100.0f, 1.0f});
            x::reality::vector location = x::reality::vector({0.0f, 0.0f, -100.0f, 1.0f});
            x::reality::vector up = x::reality::vector({0.0f, 1.0f, 0.0f});

            model = x::reality::matrix::rotate(model, direction.z(), {0.0f, 0.0f, -1.0f});
            model = x::reality::matrix::rotate(model, direction.y(), {0.0f, -1.0f, 0.0f});
            model = x::reality::matrix::rotate(model, direction.x(), {-1.0f, 0.0f, 0.0f});

            __center = center;
            __location = location;
            __up = up;

            __center = model * center + __unit->position();
            __location = model * location + __unit->position();
            __up = x::reality::vector::normalize(model * up);

            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }
        else if(__view & Unit::Camera::In)
        {
            const x::reality::vector & direction = __unit->direction();

            x::reality::matrix model = x::reality::matrix::identity();
            x::reality::vector center = x::reality::vector({0.0f, 0.0f, 100.0f, 1.0f});
            x::reality::vector location = x::reality::vector({0.0f, 0.0f, -100.0f, 1.0f});
            x::reality::vector up = x::reality::vector({0.0f, 1.0f, 0.0f});
            x::reality::vector front = x::reality::vector({0.0f, 0.0f, 1.0f});

            model = x::reality::matrix::rotate(model, direction.z(), {0.0f, 0.0f, -1.0f});
            model = x::reality::matrix::rotate(model, direction.y(), {0.0f, -1.0f, 0.0f});
            model = x::reality::matrix::rotate(model, direction.x(), {-1.0f, 0.0f, 0.0f});

            if((__view & 0xFFFF0000U) == Front)
            {
                front = x::reality::vector({0.0f, 0.0f, 1.0f});
            }
            else if((__view & 0xFFFF0000U) == Back)
            {
                front = x::reality::vector({0.0f, 0.0f, -1.0f});
            }
            else if((__view & 0xFFFF0000U) == Left)
            {
                front = x::reality::vector({1.0f, 0.0f, 0.0f});
            }
            else if((__view & 0xFFFF0000U) == Right)
            {
                front = x::reality::vector({-1.0f, 0.0f, 0.0f});
            }
            else if((__view & 0xFFFF0000U) == Top)
            {
                up = x::reality::vector({0.0f, 0.0f, 1.0f});
                front = x::reality::vector({0.0f, 1.0f, 0.0f});
            }
            else if((__view & 0xFFFF0000U) == Bottom)
            {
                up = x::reality::vector({0.0f, 0.0f, -1.0f});
                front = x::reality::vector({0.0f, -1.0f, 0.0f});
            }
            else
            {
                exceptional();
            }

            front = x::reality::vector::normalize(model * front);

            __center = __unit->position();
            __location = front * 100.0f + __unit->position();
            __up = x::reality::vector::normalize(model * up);
            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }
        else if(__view & Unit::Camera::Out)
        {
            const x::reality::vector & direction = __unit->direction();

            x::reality::matrix model = x::reality::matrix::identity();
            x::reality::vector center = x::reality::vector({0.0f, 0.0f, 100.0f, 1.0f});
            x::reality::vector location = x::reality::vector({0.0f, 0.0f, -100.0f, 1.0f});
            x::reality::vector up = x::reality::vector({0.0f, 1.0f, 0.0f});
            x::reality::vector front = x::reality::vector({0.0f, 0.0f, 1.0f});

            if((__view & 0xFFFF0000U) == Front)
            {
                front = x::reality::vector({0.0f, 0.0f, -1.0f});
            }
            else if((__view & 0xFFFF0000U) == Back)
            {
                front = x::reality::vector({0.0f, 0.0f, 1.0f});
            }
            else if((__view & 0xFFFF0000U) == Left)
            {
                front = x::reality::vector({1.0f, 0.0f, 0.0f});
            }
            else if((__view & 0xFFFF0000U) == Right)
            {
                front = x::reality::vector({-1.0f, 0.0f, 0.0f});
            }
            else if((__view & 0xFFFF0000U) == Top)
            {
                up = x::reality::vector({0.0f, 0.0f, 1.0f});
                front = x::reality::vector({0.0f, 1.0f, 0.0f});
            }
            else if((__view & 0xFFFF0000U) == Bottom)
            {
                up = x::reality::vector({0.0f, 0.0f, -1.0f});
                front = x::reality::vector({0.0f, -1.0f, 0.0f});
            }
            else
            {
                exceptional();
            }

            model = x::reality::matrix::rotate(model, direction.z(), {0.0f, 0.0f, -1.0f});
            model = x::reality::matrix::rotate(model, direction.y(), {0.0f, -1.0f, 0.0f});
            model = x::reality::matrix::rotate(model, direction.x(), {-1.0f, 0.0f, 0.0f});

            front = x::reality::vector::normalize(model * front);
            __center = front * 250.0f + __unit->position();
            __location = front * 150.0f + __unit->position();
            __up = x::reality::vector::normalize(model * up);

            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }
        else
        {
            exceptional();
        }
    }
}
