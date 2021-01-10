#ifndef   __HOMEWORLD2__UNIT__HH__
#define   __HOMEWORLD2__UNIT__HH__

#include <x/graphics/object.hh>
#include <x/physics/object.hh>

#include <Homeworld2/Graphics/Object.hh>

namespace Homeworld2
{
    class Unit : public x::graphics::object,
                 public x::physics::object
    {
    public:     class Camera : public x::reality::camera
                {
                public:     static const x::uint32 Front  = 0x00000000U;
                public:     static const x::uint32 Back   = 0x00010000U;
                public:     static const x::uint32 Left   = 0x00020000U;
                public:     static const x::uint32 Right  = 0x00030000U;
                public:     static const x::uint32 Top    = 0x00040000U;
                public:     static const x::uint32 Bottom = 0x00050000U;
                public:     static const x::uint32 Normal = 0x00000000U;
                public:     static const x::uint32 Out    = 0x00000001U;
                public:     static const x::uint32 In     = 0x00000002U;
                protected:  Unit * __unit;
                protected:  x::uint32 __view;
                public:     virtual void start();
                public:     virtual void update();
                public:     virtual void direction(x::uint32 v)
                            {
                                v = (v << 16U);
                                if(v > Bottom)
                                {
                                    v = Front;
                                }
                                if((__view & 0x0000FFFFU) != Normal)
                                {
                                    __view = ((__view & 0x0000FFFFU) | v);
                                }
                            }
                public:     virtual x::uint32 direction() const { return (0xFFFF0000U & __view) >> 16U; }
                public:     virtual void category(x::uint32 v)
                            {
                                if(v > In)
                                {
                                    v = Normal;
                                }
                                __view = v;
                            }
                public:     virtual x::uint32 category() const { return 0x0000FFFFU & __view; }
                public:     virtual x::uint32 view() const { return __view; }
                public:     virtual void view(x::uint32 v);
                public:     inline void unit(Unit * o){ __unit = o; }
                public:     Unit::Camera & operator=(const Unit::Camera & o);
                public:     Unit::Camera & operator=(Unit::Camera && o) noexcept;
                public:     Camera();
                public:     Camera(const Unit::Camera & o);
                public:     Camera(Unit::Camera && o) noexcept;
                public:     ~Camera() override;
                };
    protected:  Graphics::Object * __graphics;
    public:     Unit::Camera __camera;
    public:     virtual const x::reality::vector & direction() const { return __direction.current(); }
    public:     void direction(const x::reality::vector & direction) override
                {
                    __direction.value(__direction.value() + direction);
                }
    public:     virtual x::reality::camera * camera() { return &__camera; }
    public:     void start() override;
    public:     void update() override;
    public:     void render(const x::reality::matrix & model) override;
    public:     Unit & operator=(const Unit & o) = delete;
    public:     Unit & operator=(Unit && o) noexcept = delete;
    public:     Unit(x::real energy, Graphics::Object * graphics);
    public:     Unit(x::real energy, const x::reality::vector & direction, Graphics::Object * graphics);
    public:     Unit(const x::string & name, x::real energy, Graphics::Object * graphics);
    public:     Unit(const x::string & name, const x::reality::vector & position, x::real energy, Graphics::Object * graphics);
    public:     Unit(const x::string & name, const x::reality::vector & position, x::real energy, const x::reality::vector & direction, Graphics::Object * graphics);
    public:     Unit() = delete;
    public:     Unit(const Unit & o) = delete;
    public:     Unit(Unit && o) noexcept = delete;
    public:     ~Unit() override;
    };
}

#endif // __HOMEWORLD2__UNIT__HH__
