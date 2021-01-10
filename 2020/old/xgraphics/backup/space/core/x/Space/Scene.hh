#ifndef   __X_SPACE__SCENE__HH__
#define   __X_SPACE__SCENE__HH__

#include <x/graphics/surface.hh>

namespace xSpace
{
    class Scene : public x::graphics::surface
    {
    public:     virtual void keyboard(x::byte key, x::int32 x, x::int32 y);
    public:     virtual void special(x::int32 key, x::int32 x, x::int32 y);
    public:     xSpace::Scene & operator=(const xSpace::Scene & o) = delete;
    public:     xSpace::Scene & operator=(xSpace::Scene && o) noexcept = delete;
    public:     Scene();
    public:     Scene(const xSpace::Scene & o) = delete;
    public:     Scene(xSpace::Scene && o) noexcept = delete;
    public:     ~Scene() override;
    };
}

#endif // __X_SPACE__SCENE__HH__
