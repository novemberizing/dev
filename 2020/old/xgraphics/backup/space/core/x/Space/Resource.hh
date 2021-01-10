#ifndef   __X_SPACE__RESOURCE__HH__
#define   __X_SPACE__RESOURCE__HH__

#include <x/graphics/application.hh>
#include <x/file.hh>

#include <x/Space/Object.hh>
#include <x/Space/Senario.hh>
#include <x/Space/Senarios/Unit.hh>

#include <Homeworld2/Resource.hh>

namespace xSpace
{
    class Resource
    {
    protected:  static xSpace::Resource * __singleton;
    public:     static xSpace::Resource & init(x::graphics::application & application);
    public:     static xSpace::Resource & get();
    protected:  x::string __root;
    protected:  Homeworld2::Resource & __homeworld2;
    protected:  x::map<x::string, xSpace::Senario *> __senarios;
    protected:  virtual x::graphics::program program(const x::string & root, const x::string & name);
    public:     virtual xSpace::Object * unit(xSpace::Senarios::Unit & o);
    public:     virtual void load(x::graphics::application & application);
    public:     virtual xSpace::Senario * senario(const x::string & name);
    public:     xSpace::Resource & operator=(const xSpace::Resource & o) = delete;
    public:     xSpace::Resource & operator=(xSpace::Resource && o) noexcept = delete;
    protected:  Resource(const x::string & root, Homeworld2::Resource & homeworld2);
    public:     Resource() = delete;
    public:     Resource(const xSpace::Resource & o) = delete;
    public:     Resource(xSpace::Resource && o) noexcept = delete;
    public:     virtual ~Resource();
    };
}

#endif // __X_SPACE__RESOURCE__HH__
