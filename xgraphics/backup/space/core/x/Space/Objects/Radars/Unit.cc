#include "Unit.hh"

namespace xSpace
{
    namespace Objects
    {
        namespace Radars
        {
            x::reality::color Unit::Color::Red = {1.0f, 0.0f, 0.0f, 1.0f};
            x::reality::color Unit::Color::Green = {0.0f, 1.0f, 0.0f, 1.0f};
            x::reality::color Unit::Color::Blue = {0.0f, 0.0f, 1.0f, 1.0f};
            x::reality::color Unit::Color::Grayscale = {0.8f,0.8f,0.8f,1.0f};

            Unit::Unit(xSpace::Object * unit)
            :   x::graphics::object(),
                __unit(unit),
                __reference(nullptr),
                __program(nullptr),
                __texture(nullptr),
                __x(0.0f),
                __y(0.0f),
                __width(7.0f),
                __height(7.0f),
                __model(x::reality::matrix::identity)
            {
                x::graphics::application & application = x::graphics::application::get();

                __reference = application.reference("rectangle");
                __program = application.program("space radar-unit");
            }

            Unit::~Unit()
            {
            }

            void Unit::start(const x::reality::matrix & model, const x::reality::camera & camera, x::real width, x::real height)
            {
                x::graphics::application & application = x::graphics::application::get();

                // 상대적인 위치를 구해야 한다.

                __model = model;

                const x::reality::vector & position = __unit->position();

                x::real x = (position.x()/65000.0f * width);
                x::real y = (position.z()/65000.0f * height);

                __model = x::reality::matrix::translate(__model, {x, y, 0.0f });
                __model = x::reality::matrix::scale(__model, {__width, __height, 1.0f });
            }

            void Unit::update(const x::reality::matrix & model, const x::reality::camera & camera, x::real width, x::real height)
            {
                x::graphics::application & application = x::graphics::application::get();

                // 상대적인 위치를 구해야 한다.

                __model = model;

                const x::reality::vector & position = __unit->position();

                x::real x = (position.x()/65000.0f * width);
                x::real y = (position.z()/65000.0f * height);

                __model = x::reality::matrix::translate(__model, {x, y, 0.0f });
                __model = x::reality::matrix::scale(__model, {__width, __height, 1.0f });
            }

            void Unit::render(const x::reality::vector & eye)
            {
                x::graphics::application & application = x::graphics::application::get();

                application.bind(*__program, *this);
                application.render(*__reference);
            }

            x::boolean Unit::bind(const x::string & name, x::uint32 id)
            {
                x::graphics::application & application = x::graphics::application::get();
                if(name == "model")
                {
                    application.bind(id, __model);
                    return true;
                }
                else if(name == "_color")
                {
                    if(__unit->relationship() == "enemy")
                    {
                        application.bind(id, Unit::Color::Red);
                    }
                    else if(__unit->relationship() == "me")
                    {
                        application.bind(id, Unit::Color::Green);
                    }
                    else if(__unit->relationship() == "alliance")
                    {
                        application.bind(id, Unit::Color::Blue);
                    }
                    else
                    {
                        application.bind(id, Unit::Color::Grayscale);
                    }

                    return true;
                }
                return false;
            }

            x::boolean Unit::mousemove(x::int32 x, x::int32 y, x::real width, x::real height)
            {
                const x::reality::vector & position = __unit->position();

                x::real _x = ((position.x()/65000.0f * width) + width)/2;
                x::real _y = ((-position.z()/65000.0f * height) + height)/2;
                if(_x <= x && x < _x + __width)
                {
                    if(_y <= y && y < _y + __height)
                    {
                        // x::console::out << "mouse over object => " << __unit->name() << x::endl;
                        return true;
                    }
                }
                return false;
            }

            x::boolean Unit::mouse(x::int32 button, x::int32 state, x::int32 x, x::int32 y, x::real width, x::real height)
            {
                const x::reality::vector & position = __unit->position();

                x::real _x = ((position.x()/65000.0f * width) + width)/2;
                x::real _y = ((-position.z()/65000.0f * height) + height)/2;
                if(_x <= x && x < _x + __width)
                {
                    if(_y <= y && y < _y + __height)
                    {
                        __unit->selected(true);
                        x::console::out << "mouse down object => " << __unit->name() << x::endl;
                        return true;
                    }
                }
                return false;
            }
        }
    }
}
