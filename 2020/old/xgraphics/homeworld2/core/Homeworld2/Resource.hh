#ifndef   __HOMEWORLD2__RESOURCE__HH__
#define   __HOMEWORLD2__RESOURCE__HH__

#include <x/json.hh>
#include <x/graphics/application.hh>

#include <Homeworld2/Graphics/ReferenceFile.hh>

#include <x/console.hh>

namespace Homeworld2
{
    class Resource
    {
    protected:  static Homeworld2::Resource * __singleton;
    public:     static Homeworld2::Resource & get();
    public:     virtual void load(x::graphics::application & application);
    protected:  virtual Homeworld2::Graphics::Reference * unit(const x::string & root, const x::string & type, const x::string & name);
    protected:  virtual x::graphics::program program(const x::string & root, const x::string & name);
    public:     virtual Homeworld2::Graphics::Objects::Root * build(const x::string & source);
    public:     Homeworld2::Resource & operator=(const Homeworld2::Resource & o) = delete;
    public:     Homeworld2::Resource & operator=(Homeworld2::Resource && o) noexcept = delete;
    public:     Resource();
    public:     Resource(const Homeworld2::Resource & o) = delete;
    public:     Resource(Homeworld2::Resource && o) noexcept = delete;
    public:     virtual ~Resource();
    };
}

#endif // __HOMEWORLD2__RESOURCE__HH__
