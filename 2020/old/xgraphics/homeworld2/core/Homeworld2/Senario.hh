#ifndef   __HOMEWORLD2__SENARIO__HH__
#define   __HOMEWORLD2__SENARIO__HH__

#include <x/string.hh>
#include <x/json.hh>
#include <x/console.hh>

#include <Homeworld2/Resource.hh>
#include <Homeworld2/Senarios/Unit.hh>

namespace Homeworld2
{
    class Senario
    {
    public:     static Senario * open(const x::string & path, Homeworld2::Resource & resource);
    protected:  x::string __name;
    protected:  x::array<Homeworld2::Senarios::Unit> __units;
    public:     Senario & operator=(const Senario & o) = delete;
    public:     Senario & operator=(Senario && o) noexcept = delete;
    protected:  Senario();
    public:     Senario(const Senario & o) = delete;
    public:     Senario(Senario && o) noexcept = delete;
    public:     virtual ~Senario();
    };
}

#endif // __HOMEWORLD2__SENARIO__HH__
