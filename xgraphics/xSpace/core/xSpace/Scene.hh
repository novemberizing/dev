#ifndef   __X_SPACE__SCENE__HH__
#define   __X_SPACE__SCENE__HH__

#include <x/graphics/surface.hh>
#include <xSpace/Object.hh>

namespace xSpace
{
    class Scene : public x::graphics::surface
    {
    protected:  x::string __name;
    protected:  x::array<xSpace::Object *> __objects;
    public:     void add(x::graphics::layer * layer) override;
    public:     virtual void add(xSpace::Object * object);
    public:     inline const x::string & name() const { return __name; }
    public:     Scene(const x::string & name);
    public:     Scene();
    public:     ~Scene() override;
    public:     xSpace::Scene & operator=(const xSpace::Scene & o) = delete;
    public:     xSpace::Scene & operator=(xSpace::Scene && o) noexcept = delete;
    public:     Scene(const xSpace::Scene & o) = delete;
    public:     Scene(xSpace::Scene && o) noexcept = delete;
    };
}

#endif // __X_SPACE__SCENE__HH__
