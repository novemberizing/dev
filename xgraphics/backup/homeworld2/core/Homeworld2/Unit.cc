#include "Unit.hh"

#include <x/graphics/application.hh>

namespace Homeworld2
{
    Unit::Unit(x::real energy, Graphics::Object * graphics)
    :   x::reality::object(),
        x::graphics::object(),
        x::physics::object(energy),
        __graphics(graphics),
        __camera()
    {
        __camera.unit(this);
    }

    Unit::Unit(x::real energy, const x::reality::vector & direction, Graphics::Object * graphics)
    :   x::reality::object(),
        x::graphics::object(),
        x::physics::object(energy, x::reality::vector::radian(direction)),
        __graphics(graphics),
        __camera()
    {
        __camera.unit(this);
    }

    Unit::Unit(const x::string & name, const x::reality::vector & position, x::real energy, Graphics::Object * graphics)
    :   x::reality::object(name, position),
        x::graphics::object(),
        x::physics::object(energy),
        __graphics(graphics),
        __camera()
    {
        __camera.unit(this);
    }

    Unit::Unit(const x::string & name, const x::reality::vector & position, x::real energy, const x::reality::vector & direction, Graphics::Object * graphics)
    :   x::reality::object(name, position),
        x::graphics::object(),
        x::physics::object(energy, x::reality::vector::radian(direction)),
        __graphics(graphics),
        __camera()
    {
        __camera.unit(this);
    }

    Unit::Unit(const x::string & name, x::real energy, Graphics::Object * graphics)
    :   x::reality::object(name),
        x::graphics::object(),
        x::physics::object(energy),
        __graphics(graphics),
        __camera()
    {
        __camera.unit(this);
    }

    Unit::~Unit()
    {
        __graphics = nullptr;
    }

    void Unit::render(const x::reality::matrix & model)
    {
        __model = x::reality::matrix::translate(model, __position);
        __model = x::reality::matrix::rotate(__model, __direction.current());

        __graphics->render(__model);
    }

    void Unit::start()
    {
        __camera.start();

    }

    void Unit::update()
    {
        x::graphics::application & application = x::graphics::application::get();

        __force.update();
        __direction.update();

        __acceleration = x::physics::force::acceleration(__force.current(), 1, __velocity);
        __velocity = __velocity + (__acceleration * application.fps() / 1000.0f);

        // x::console::out << "velocity => " << __velocity << x::endl << x::flush;

        x::reality::vector direction = __direction.current();
        x::reality::matrix model = x::reality::matrix::identity();
        model = x::reality::matrix::rotate(model, direction.z(), {0.0f, 0.0f, -1.0f});
        model = x::reality::matrix::rotate(model, direction.y(), {0.0f, -1.0f, 0.0f});
        model = x::reality::matrix::rotate(model, direction.x(), {-1.0f, 0.0f, 0.0f});

        x::reality::vector move = model * x::reality::vector({0.0f, 0.0f, __velocity});

        __position = __position + move;

        __camera.update();

    }
}
