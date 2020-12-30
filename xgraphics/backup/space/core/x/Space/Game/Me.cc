#include "Me.hh"

namespace xSpace
{
    namespace Game
    {
        Me::Me()
        :   __main(nullptr),
            __selected(nullptr),
            __group(),
            __selection(0)
        {
            __group.resize(10, nullptr);
            select(__selection);
        }

        Me::~Me()
        {
        }

        void Me::main(xSpace::Object * o)
        {
            __main = o;
            if(__selection == 0)
            {
                select(__selection);
            }
        }

        xSpace::Object * Me::select(x::uint64 n)
        {
            __selection = n;

            if(__selection > 1)
            {
                __selection = 0;
            }

            if(__selection == 0)
            {
                // xSpace::Game::Camera::World::get();
                // xSpace::Game::Camera::Object & camera = xSpace::Game::Camera::Object::get();
                // MAIN UNIT SELECT
                // const x::reality::camera &
                xSpace::Object::Camera & camera = xSpace::Object::Camera::get();
                camera.set(__main);
                __selected = __main;
                x::reality::camera::current(camera);
                x::console::out << "current camera is object" << x::endl << x::flush;

                return __main;
            }
            else if(__selection == 1)
            {
                // WORLD SELECT
                x::reality::camera::current(x::reality::camera::world());
            }
            else
            {
                exceptional();
            }
            return nullptr;
        }
    }
}
