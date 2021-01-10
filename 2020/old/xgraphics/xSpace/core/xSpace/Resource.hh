#ifndef   __X_SPACE__RESOURCE__HH__
#define   __X_SPACE__RESOURCE__HH__

#include <Homeworld2/Resource.hh>

#include <xSpace/Demo/Scene.hh>

namespace xSpace
{
    class Resource
    {
    protected:  static xSpace::Resource * __singleton;
    public:     static xSpace::Resource & get();
    protected:  Homeworld2::Resource & __homeworld2;
    public:     virtual void load(x::graphics::application & application);
    public:     virtual xSpace::Demo::Scene * demo();
    public:     Resource(Homeworld2::Resource & homeworld2);
    public:     virtual ~Resource();
    public:     Resource() = delete;
    public:     Resource(const xSpace::Resource & o) = delete;
    public:     Resource(xSpace::Resource && o) noexcept = delete;
    public:     xSpace::Resource & operator=(const xSpace::Resource & o) = delete;
    public:     xSpace::Resource & operator=(xSpace::Resource && o) noexcept = delete;
    };
}

#endif // __X_SPACE__RESOURCE__HH__
