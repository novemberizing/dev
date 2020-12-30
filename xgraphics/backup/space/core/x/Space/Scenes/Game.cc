#include "Game.hh"
#include "../Objects/Radar.hh"
#include "../Objects/Radars/Unit.hh"

namespace xSpace
{
    namespace Scenes
    {
        Game::Game()
        :   xSpace::Scene(),
            __senario(),
            __front("front"),
            __game("game"),
            __radar(nullptr),
            __me()
        {
            layers.append(&__game);
            layers.append(&__front);
        }

        Game::~Game()
        {
            __senario = nullptr;
        }

        void Game::load(xSpace::Senario * senario, xSpace::Resource & resource)
        {
            // TODO; CHECK UP GAME IS END ????
            __senario = senario;

            __radar = new xSpace::Objects::Radar("radar");

            for(x::uint64 i = 0; i < __senario->units.size(); i++)
            {
                xSpace::Object * unit = resource.unit(__senario->units[i]);
                __game.add(unit);
                __radar->add(new xSpace::Objects::Radars::Unit(unit));
                if(unit->relationship() == "me")
                {
                    // TODO: MULTIPLE MY UNIT
                    __me.main(unit);
                }
            }

            __front.add(__radar);
        }

        void Game::keyboard(x::byte key, x::int32 x, x::int32 y)
        {
            switch(key)
            {
            case '\t': __selected = __me.select(__me.selection() + 1); break;
            case 'a':  if(__selected){ __selected->force(__selected->force() + 1.0f); } break;
            case 'z':  if(__selected){ __selected->force(__selected->force() - 1.0f); } break;
            default:   x::console::out << "keyboard => " << key << x::endl << x::flush; break;
            }
        }

        void Game::special(x::int32 key, x::int32 x, x::int32 y)
        {
            x::console::out << "special => " << key << x::endl << x::flush;
        }
    }
}
