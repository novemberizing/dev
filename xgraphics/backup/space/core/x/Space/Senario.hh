#ifndef   __X_SPACE__SENARIO__HH__
#define   __X_SPACE__SENARIO__HH__

#include <x/json.hh>

#include <x/Space/Senarios/Unit.hh>

namespace xSpace
{
    class Senario
    {
    public:     static xSpace::Senario * build(const x::string & path);
    protected:  x::string __name;
    public:     x::array<xSpace::Senarios::Unit> units;
    public:     xSpace::Senario & operator=(const xSpace::Senario & o);
    public:     xSpace::Senario & operator=(const xSpace::Senario && o) noexcept;
    public:     Senario(const x::string & name);
    public:     Senario();
    public:     Senario(const xSpace::Senario & o);
    public:     Senario(xSpace::Senario && o) noexcept;
    public:     virtual ~Senario();
    };
}

#endif // __X_SPACE__SENARIO__HH__
