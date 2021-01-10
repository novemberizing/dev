#ifndef   __HOMEWORLD2__RESOURCE__HH__
#define   __HOMEWORLD2__RESOURCE__HH__

#include <x/console.hh>
#include <x/file.hh>
#include <x/json.hh>
#include <x/graphics/shader.hh>

#include <Homeworld2/Reference.hh>


namespace Homeworld2
{
    class Resource
    {
    protected:  static Resource * __singleton;
    public:     static Resource & init(const x::string & path);
    public:     static Resource & get();
    protected:  x::string __path;
    protected:  x::map<x::string, Homeworld2::Reference *> __references;
    protected:  x::graphics::shader shader(const x::string & name, const x::file & f);
    public:     virtual void load();
    public:     Resource & operator=(const Resource & o) = delete;
    public:     Resource & operator=(Resource && o) noexcept = delete;
    protected:  Resource(const x::string & path);
    public:     Resource() = delete;
    public:     Resource(const Resource & o) = delete;
    public:     Resource(Resource && o) noexcept = delete;
    public:     virtual ~Resource();
    };
}

#endif // __HOMEWORLD2__RESOURCE__HH__
