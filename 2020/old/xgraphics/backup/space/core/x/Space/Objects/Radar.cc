#include "Radar.hh"


namespace xSpace
{
    namespace Objects
    {
        Radar::Radar(const x::string & name)
        :   x::graphics::object(),
            __name(),
            __x(1024 - 200 - 30),
            __y(768 - 200 - 30),
            __width(200),
            __height(200),
            __reference(nullptr),
            __program(nullptr),
            __texture(nullptr),
            __units()
        {
            x::graphics::application & application = x::graphics::application::get();

            __reference = application.reference("rectangle");
            __program = application.program("space radar");
            // __texture = nullptr;
        }

        Radar::~Radar()
        {
        }

        void Radar::start(const x::reality::matrix & model, const x::reality::camera & camera)
        {
            x::graphics::application & application = x::graphics::application::get();

            __model = model;
            __model = x::reality::matrix::scale(__model, {1.0f/application.width(), 1.0f/application.height(), 1.0f });
            __model = x::reality::matrix::translate(__model, {__x * 2.0f - application.width() + __width, -(__y * 2.0f) + application.height() - __height, 0.0f});

            __units.each([this, &camera](x::var<xSpace::Objects::Radars::Unit *>::type & unit){
                unit->start(__model, camera, __width, __height);
            });

            __model = x::reality::matrix::scale(__model, {__width, __height, 1.0f });
        }

        void Radar::update(const x::reality::matrix & model, const x::reality::camera & camera)
        {
            x::graphics::application & application = x::graphics::application::get();

            __model = model;
            __model = x::reality::matrix::scale(__model, {1.0f/application.width(), 1.0f/application.height(), 1.0f });
            __model = x::reality::matrix::translate(__model, {__x * 2.0f - application.width() + __width, -(__y * 2.0f) + application.height() - __height, 0.0f});

            __units.each([this, &camera](x::var<xSpace::Objects::Radars::Unit *>::type & unit){
                unit->update(__model, camera, __width, __height);
            });

            __model = x::reality::matrix::scale(__model, {__width, __height, 1.0f });
        }

        void Radar::render(const x::reality::vector & eye)
        {
            x::graphics::application & application = x::graphics::application::get();

            __units.each([&eye](x::var<xSpace::Objects::Radars::Unit *>::type & unit){
                unit->render(eye);
            });

            application.bind(*__program, *this);
            application.render(*__reference);
        }

        x::boolean Radar::bind(const x::string & name, x::uint32 id)
        {
            x::graphics::application & application = x::graphics::application::get();
            if(name == "model")
            {
                application.bind(id, __model);
                return true;
            }
            return false;
        }

        x::boolean Radar::mousemove(x::int32 x, x::int32 y)
        {
            if(__x <= x && x <= __x + __width)
            {
                if(__y <= y && y <= __y + __height)
                {
                    x::console::out << "radar" << x::endl << x::flush;
                    x = x - __x;
                    y = y - __y;
                    __units.until([x, y, this](x::var<xSpace::Objects::Radars::Unit *>::type & unit){
                        return unit->mousemove(x, y, __width, __height);
                    });
                    return true;
                }
            }
            return false;
        }

        x::boolean Radar::mouse(x::int32 button, x::int32 state, x::int32 x, x::int32 y)
        {
            if(__x <= x && x <= __x + __width)
            {
                if(__y <= y && y <= __y + __height)
                {
                    x::console::out << "radar" << x::endl << x::flush;
                    x = x - __x;
                    y = y - __y;
                    __units.until([button, state, x, y, this](x::var<xSpace::Objects::Radars::Unit *>::type & unit){
                        return unit->mouse(button, state, x, y, __width, __height);
                    });
                    return true;
                }
            }
            return false;
        }
    }
}
